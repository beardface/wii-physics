#include <string.h>
#include <malloc.h>
#include "ringbuffer.h"

RingBuffer::RingBuffer()
{
	ringData = (uint8_t *)memalign(32, BUFFER_SIZE);
	
	read = 0;
	write = 0;
}

RingBuffer::~RingBuffer()
{
	if(ringData) { free(ringData); }
}

void RingBuffer::init()
{
	read = 0;
	write = 0;
}

void RingBuffer::put(void *data, uint32_t size)
{
	if(!ringData) { return; }
	
	if(write + size < BUFFER_SIZE)
	{
		// Copy data in
		memcpy(ringData + write, data, size);
		
		// Incriment write pointer
		write += size;
	}
	else
	{
		// Copy first chunk
		int firstChunk = BUFFER_SIZE - write;		
		memcpy(ringData + write, data, firstChunk);
		
		// Copy second chunk
		memcpy(ringData, ((uint8_t *)data) + firstChunk, size - firstChunk);
		
		// Set write pointer
		write = size - firstChunk;
	}
}

void RingBuffer::get(void *data, uint32_t size)
{
	if(!ringData) { return; }
	
	if(read + size < BUFFER_SIZE)
	{
		// Copy data out
		if(data) { memcpy(data, ringData + read, size); }
		
		// Incriment read pointer
		read += size;
	}
	else
	{
		// Copy first chunk
		int firstChunk = BUFFER_SIZE - read;		
		
		if(data) { memcpy(data, ringData + read, firstChunk); }
		
		// Copy second chunk
		if(data) { memcpy(((uint8_t *)data) + firstChunk, ringData, size - firstChunk); }
		
		// Set write pointer
		read = size - firstChunk;
	}
}

uint32_t RingBuffer::amount()
{
	if(!ringData) { return 0; }
	
	if(write < read)
	{
		// Looped around
		return (write + BUFFER_SIZE) - read;
	}
	else
	{
		// Normal
		return write - read;
	}
}
