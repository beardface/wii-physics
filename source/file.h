#ifndef __FILE_H
#define __FILE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <fat.h>
#include <sys/dir.h>
#include <unistd.h>

#include "ringbuffer.h"

typedef enum
{
	STREAM_NONE,
	STREAM_ROOT,
	STREAM_SD,
	STREAM_DVD,
	STREAM_USB,
	STREAM_SAMBA,
	STREAM_HTTP,
	STREAM_ICY,
	STREAM_MAX
} StreamType;

typedef enum
{
	FILE_NONE = 0,
	FILE_NORMAL = 1,
	FILE_DIRECTORY = 2,
	FILE_SOURCE = 3
} FileType;

class File
{
	public:
		File();
		~File();
		
		int open(const char *url, const char *mode);
		int read(const void *buffer, uint32_t size, uint32_t count);
		int write(const void *buffer, uint32_t size, uint32_t count);
		void close();
		
		int seek(int32_t offset, int origin);
		uint32_t tell();
		
		int findNextFile(char *file, FileType &f);
		int findNextString(char *string, int len);
		
		void getCurrentUrl(char *url);
		void enumerateInterfaces();
		
		void readAhead();
		
		bool isValidURL(char *url);
	private:
		int openfat(const char *url, const char *mode);
		int readInternal(const void *buffer, uint32_t amount);
		
		StreamType fType;
		char currentUrl[MAXPATHLEN];
		
		FILE *fp;
		DIR_ITER *dir;
		
		RingBuffer rBuf;
		
		static int instance;
		static bool failed[STREAM_MAX];
		
		bool listedBack;
		int rootPos;
		
		char last_char;
};

#ifdef __cplusplus
}
#endif

#endif


