#ifndef __CIRCBUF_H__
#define __CIRCBUF_H__

#include <stdint.h>
#include <stdbool.h>

#define PV_OFFS(pvBuf, elem_size, index) ((uint8_t*)(pvBuf) + ((elem_size)*(index)))

typedef struct circbuf_t {
    void* buffer;
    size_t elem_size;
    size_t capacity;
    uint8_t start;
    uint8_t len;
} circbuf_t;

circbuf_t* circbuf_init(const size_t size, const size_t elem_size);
void circbuf_free(circbuf_t* circbuf);
int8_t circbuf_push(circbuf_t* circbuf, const void* byte);
void circbuf_pop(circbuf_t* circbuf, void* outptr);
bool circbuf_overflow(const circbuf_t* circbuf);
bool circbuf_empty(const circbuf_t* circbuf);
void circbuf_clear(circbuf_t* circbuf);

#endif // __CIRCBUF_H__
