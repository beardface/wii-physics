#include <stdio.h>
#include <string.h>
#include "file.h"

#define READ_AHEAD_AMOUNT	2048
#define MAX_READ_AHEAD		16384

// So multiple files can see the same failure
bool File::failed[STREAM_MAX];
int File::instance = 0;

File::File()
{
	// Start out wih nothing
	fType = STREAM_NONE;
	
	// To ensure reading strings does not error
	last_char = 0;
	
	// Just for safety sake
	fp = NULL;
	dir = NULL;
	
	if(instance == 0)
	{
		// Remember sd failure (better granularity laters)
		for(int i = 0; i < STREAM_MAX; i++)
		{
			failed[i] = false;
		}
		
		// Always failed
		failed[STREAM_NONE] = true;
		
		// Formats not setup yet
		failed[STREAM_DVD] = true;
		failed[STREAM_SAMBA] = true;
		failed[STREAM_HTTP] = true;
		failed[STREAM_ICY] = true;
	}
	
	// Remember count (never subtract because we never want this information above to go away, even if there are no more instances at the moment)
	instance++;
}

File::~File()
{
	// Close any open handles
	close();
}

int File::openfat(const char *fName, const char *mode)
{
	// Check for directory mode
	if(mode[0] == 'd' || mode[0] == 'D')
	{
		// Open as directory
		dir = diropen(fName);
		dirreset(dir);
		
		listedBack = false;
		
		if(!dir)
		{
			// Error!
			return -1;
		}
	}
	else
	{
		// Open as file
		fp = fopen(fName, mode);
		
		if(!fp)
		{
			// Error!
			return -1;
		}
	}
	
	return 0;
}

int File::open(const char *url, const char *mode)
{
	// Set FileType temporarily
	fType = STREAM_NONE;
	
	// Remember filename
	strcpy(currentUrl, url);
	
	// Clear buffer
	rBuf.init();
	
	if(strcmp(url, "/") == 0) // root directory list
	{
		fType = STREAM_ROOT;
		
		if(mode[0] == 'd' || mode[0] == 'D')
		{
			// Set the mode up to give back root entries
			rootPos = STREAM_SD;
			
			return 0;
		}
		
		return -1;
	}
	else if(strncmp(url, "fat3:/", 6) == 0) // regular card url
	{	
		fType = STREAM_SD;
		
		if(!openfat(url, mode))
		{
			// Set FileType properly
			failed[STREAM_SD] = false;
			
			// Success!
			return 0;
		}
		
		failed[STREAM_SD] = true;
		return -1;
	}
	else if(strncmp(url, "sd://", 5) == 0) // SD card url
	{
		char fName[MAXPATHLEN];
		
		// Generate proper path to open
		strcpy(fName, "fat3:/");
		strcat(fName, url + 5);
		
		fType = STREAM_SD;
		
		if(!openfat(fName, mode))
		{
			// Set FileType properly
			failed[STREAM_SD] = false;
			
			// Success!
			return 0;
		}
		
		failed[STREAM_SD] = true;
		return -1;
	}
	else if(strncmp(url, "usb://", 6) == 0) // USB drive url
	{
		fType = STREAM_USB;
		
		char fName[MAXPATHLEN];
		
		// Generate proper path to open
		strcpy(fName, "fat4:/");
		strcat(fName, url + 6);
		
		if(!openfat(fName, mode))
		{
			// Set FileType properly
			failed[STREAM_USB] = false;
			
			// Success!
			return 0;
		}
		
		failed[STREAM_USB] = true;
		return -1;
	}
	
	// Default is error
	return -1;
}

void File::readAhead()
{
	// Don't do anything if this medium is failed
	if(fType == STREAM_NONE) { return; }
	if(failed[fType]) { return; }
	if(rBuf.amount() >= MAX_READ_AHEAD) { return; }
	
	// Read a spot ahead
	static uint8_t data[READ_AHEAD_AMOUNT];
	int readAmount = readInternal(data, READ_AHEAD_AMOUNT);
	
	// Add to ring buffer
	if(readAmount > 0)
	{
		rBuf.put(data, readAmount);
	}
}

int File::readInternal(const void *buffer, uint32_t amount)
{
	// Read from current stream
	switch(fType)
	{
		case STREAM_SD:
		case STREAM_USB:
		{
			int ret = fread((void *)buffer, 1, amount, fp);
			
			if(ret >= 0)
			{
				// Ensure no error
				if(ferror(fp))
				{
					// Ensure we close right
					failed[fType] = true;
					
					// Failure
					return -1;
				}
				
				// Fine
				return ret;
			}
			else
			{
				// Set flag
				failed[fType] = true;
				
				// Not fine
				return ret;
			}
			break;
		}
		default:
			// Catch all other cases
			return 0;
	}
}

int File::read(const void *buffer, uint32_t size, uint32_t count)
{
	// Don't do anything if this medium is failed
	if(failed[fType]) { return -1; }
	
	// Know the size
	uint32_t amount = size * count;
	uint32_t offset = 0;
	
	// Copy out of ringbuffer if it exists
	if(rBuf.amount() >= amount)
	{
		// Grab out of ringbuffer
		rBuf.get((void *)buffer, amount);
		
		// Return full amount
		return amount;
	}
	
	if(rBuf.amount() > 0)
	{
		// Remember how much and where to read to
		amount -= rBuf.amount();
		offset += rBuf.amount();
		
		// Grab from the buffer
		rBuf.get((void *)buffer, rBuf.amount());
	}
	
	// Read the rest out of memory
	uint32_t newAmount = readInternal(((uint8_t *)buffer) + offset, amount);
	
	// Return the actual count read
	return (offset + newAmount) / size;
}

int File::write(const void *buffer, uint32_t size, uint32_t count)
{
	// Don't do anything if this medium is failed
	if(failed[fType]) { return -1; }
	
	// Return to where we were before
	int backAmount = -rBuf.amount();
	
	// Ensure buffer is flushed
	rBuf.init();
	
	// Write to current stream
	switch(fType)
	{
		case STREAM_SD:
		case STREAM_USB:
		{
			// Move back then write
			fseek(fp, backAmount, SEEK_CUR);
			
			int ret = fwrite((void *)buffer, size, count, fp);
			
			if(ret == (int)count)
			{
				// Fine
				return ret;
			}
			else
			{
				// Set flag
				failed[fType] = true;
				
				// Not fine
				return ret;
			}
			break;
		}
		default:
			// Catch all other cases
			return 0;
	}
}

void File::close()
{
	// Erase filename
	currentUrl[0] = 0;
	
	// Don't do anything if this medium is failed
	if(failed[fType]) { return; }
	
	// Close any open handles
	switch(fType)
	{
		case STREAM_SD:
		case STREAM_USB:
			// Close file
			if(fp) { fclose(fp); }
			if(dir) { dirclose(dir); }
			
			// Ensure we don't close again
			fp = NULL;
			dir = NULL;
			
			break;
		default:
			break;
	}
	
	// Set file type to none
	fType = STREAM_NONE;
}

int File::seek(int32_t offset, int origin)
{
	// Don't do anything if this medium is failed
	if(failed[fType]) { return -1; }
	
	// Return to where we were before
	int backAmount = -rBuf.amount();
	
	// Ensure buffer is flushed
	rBuf.init();
	
	// Seek current stream
	switch(fType)
	{
		case STREAM_SD:
		case STREAM_USB:
		{
			// Move back then seek
			fseek(fp, backAmount, SEEK_CUR);
			int ret = fseek(fp, offset, origin);
			
			if(ret == 0)
			{
				// Fine
				return ret;
			}
			else
			{
				// Set flag
				failed[fType] = true;
				
				// Not fine
				return ret;
			}
			break;
		}
		default:
			// Catch all other cases
			return 0;
	}
}

uint32_t File::tell()
{
	// Don't do anything if this medium is failed
	if(failed[fType]) { return 0; }
	
	// Seek current stream
	switch(fType)
	{
		case STREAM_SD:
		case STREAM_USB:
			return ftell(fp) - rBuf.amount();
		default:
			// Catch all other cases
			return 0;
	}
}

int File::findNextFile(char *file, FileType &f)
{	
	// Don't do anything if this medium is failed
	if(failed[fType]) 
	{ 
		if(listedBack) { return 0; }
		
		f = FILE_DIRECTORY;
		strcpy(file, "..");
		listedBack = true;
		
		return 1;
	}
	
	switch(fType)
	{
		case STREAM_SD:
		case STREAM_USB:
		{		
			struct stat st;
			
			// Grab next directory entry
			int result = dirnext(dir,file,&st);
			
			if(!result)
			{
				// Normal
				if(st.st_mode & S_IFDIR)
				{
					if(strcmp(file, "..") == 0)
					{
						// Remember that we listed this
						listedBack = true;
					}
					
					// Directory
					f = FILE_DIRECTORY;
				}
				else
				{
					// Regular file
					f = FILE_NORMAL;
				}
				
				// Return normal
				return 1;
			}
			else
			{
				// Send back '..' entry if needed
				if(!listedBack)
				{
					f = FILE_DIRECTORY;
					strcpy(file, "..");
					listedBack = true;
					
					return 1;
				}
				
				// End, set null
				f = FILE_NONE;
				file[0] = 0;
				
				// Return end
				return 0;
			}
			
			break;
		}
		case STREAM_ROOT:
		{
			// If failed, don't list
			while(rootPos < STREAM_MAX)
			{
				if(!failed[rootPos]) {	break; }
				
				rootPos++;
			}
			
			switch(rootPos)
			{
				case STREAM_SD:
					strcpy(file, "sd://");
					break;
				case STREAM_USB:
					strcpy(file, "usb://");
					break;
				case STREAM_MAX:
					// No more files
					file[0] = 0;
					f = FILE_NONE;
					return 0;
			}
			
			// All directories
			f = FILE_DIRECTORY;
			
			// Remember next entry
			rootPos++;
			
			return 1;
		}
		default:
			// End, set null
			f = FILE_NONE;
			file[0] = 0;
			
			return 0;
	}
}

int File::findNextString(char *str, int len)
{
	int outpos = 0;
	
	while(true)
	{
		// Grab next character
		char c;		
		
		if(read(&c, 1, 1) <= 0)
		{
			if(outpos == 0)
			{
				// No data left
				str[0] = 0;
				return -1;
			}
			
			// End of file, end of string
			str[outpos] = 0;
			return outpos;
		}
		
		switch(c)
		{
			case '\n':
				if(last_char == '\r')
				{
					// Ignore, windows ending
					last_char = 0;
					
					break;
				}
				
				// Fallthrough
			case '\r':
				// End of string!
				last_char = c;
				
				// Ensure properly null terminated
				str[outpos] = 0;				
				return outpos;
			default:
				// Just store
				str[outpos++] = c;
				
				break;
		}
		
		if(outpos >= len)
		{
			// Too long
			str[outpos] = 0;
			return outpos;
		}
	}
	
	return 0;
}

void File::getCurrentUrl(char *url)
{
	// Copy stored url
	strcpy(url, currentUrl);
}

void File::enumerateInterfaces(void)
{
	// Try to list root dir on any device we don't know exists yet, to see if it fails
	open("sd:///", "d");
	close();
	
	open("usb:///", "d");
	close();
}

bool File::isValidURL(char *url)
{
	if(!url) { return false; }
	
	char tmp[9];
	
	strncpy(tmp, url, 8);
	tmp[8] = 0;
	
	strlwr(tmp);
	
	if(strncmp(tmp,"http://", 7) == 0)
	{
		return true;
	}
	
	if(strncmp(tmp,"https://", 8) == 0)
	{
		return true;
	}
	
	if(strncmp(tmp,"sd://", 5) == 0)
	{
		return true;
	}
	
	if(strncmp(tmp,"usb://", 6) == 0)
	{
		return true;
	}
	
	return false;		
}
