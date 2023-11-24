#include "CircleBuffer.h"





	void RING_Init(RING_buffer_t *ring, uint8_t *buf, uint16_t size)
	{
		ring->size = size;
		ring->buffer = buf;
		RING_Clear(ring);

	}

	void RING_Clear(RING_buffer_t* buf)
	{
		buf->tail = 0;
		buf->head = 0;
	}

	void RING_Put(uint8_t symbol, RING_buffer_t* buf)
	{
		buf->buffer[buf->head++] = symbol;
		if (buf->head >= buf->size) buf->head = 0;
	}


	uint8_t RING_Pop(RING_buffer_t *buf)
	{

		uint8_t retval = buf->buffer[buf->tail++];
		if (buf->tail >= buf->size) buf->tail = 0;
		return retval;
	}
