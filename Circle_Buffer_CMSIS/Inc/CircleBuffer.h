#include "stdint.h"

typedef struct
{
    uint8_t *buffer;
    uint16_t tail;
    uint16_t head;
    uint16_t size;
} RING_buffer_t;


void RING_Put(uint8_t symbol, RING_buffer_t* buf);
uint8_t RING_Pop(RING_buffer_t *buf);
void RING_Init(RING_buffer_t *ring, uint8_t *buf, uint16_t size);
