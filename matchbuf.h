#ifndef __MATCHBUF_H__
#define __MATCHBUF_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef void (*cb_t)(const uint8_t* buffer, const size_t size);

typedef struct matchbuf_t {
    const char* pattern;
    size_t cursor;
    cb_t cb;
} matchbuf_t;

void matchbuf_init(matchbuf_t* matchbuf, const char* pattern, const cb_t cb);
bool matchbuf_accept(matchbuf_t* matchbuf, const uint8_t* bytes, const size_t index);
void matchbuf_reset(matchbuf_t* matchbuf);

#endif // __MATCHBUF_H__
