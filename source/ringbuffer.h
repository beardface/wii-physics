#ifndef __RINGBUFFER_H
#define __RINGBUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#define BUFFER_SIZE (131072)

#include <stdint.h>

class RingBuffer
{
	public:
		RingBuffer();
		~RingBuffer();
		
		void init();
		void put(void *data, uint32_t size);
		void get(void *data, uint32_t size);
		uint32_t amount();
	private:
		uint32_t read;
		uint32_t write;
		uint8_t *ringData;
};

#ifdef __cplusplus
}
#endif

#endif


