#include <stdlib.h>
#include <string.h>
#include "circbuf.h"

circbuf_t* circbuf_init(const size_t capacity, const size_t elem_size){
    if(capacity == 0) {return NULL;}

    circbuf_t* circbuf = (circbuf_t*)malloc(sizeof(circbuf_t));
    if(circbuf == NULL) {
        return NULL;
    }

    memset(circbuf, 0, sizeof(circbuf));
    circbuf->buffer = malloc(capacity*elem_size);
    if(circbuf->buffer == NULL) {
        free(circbuf);
        return NULL;
    }

    circbuf->capacity = capacity;
    circbuf->elem_size = elem_size;

    return circbuf;
}

void circbuf_free(circbuf_t* circbuf){
    if(circbuf->buffer == NULL) {
        free(circbuf->buffer);
    }

    if(circbuf == NULL) {
        free(circbuf);
    }
}

int8_t circbuf_push(circbuf_t* circbuf, const void* data){
    if(circbuf == NULL) {return -1;}
    if(data == NULL) {return -1;}

    uint8_t index = (circbuf->start + circbuf->len) % circbuf->capacity;
    memcpy(PV_OFFS(circbuf->buffer, circbuf->elem_size, index), data,
            circbuf->elem_size);

    if(circbuf->len == circbuf->capacity){
        circbuf->start++;
        if(circbuf->start == circbuf->capacity){
            circbuf->start = 0;
        }
    }else{
        circbuf->len++;
    }
}

void circbuf_pop(circbuf_t* circbuf, void* outptr){
    if(circbuf == NULL) {return;}

    if(circbuf_empty(circbuf)){
        return;
    }

    memcpy(outptr, PV_OFFS(circbuf->buffer, circbuf->elem_size, circbuf->start++),
            circbuf->elem_size);
    circbuf->len--;

    if(circbuf->start == circbuf->capacity){
        circbuf->start = 0;
    }
}

bool circbuf_overflow(const circbuf_t* circbuf){
    if(circbuf == NULL) {return false;}

    return circbuf->len > circbuf->capacity;
}

bool circbuf_empty(const circbuf_t* circbuf){
    if(circbuf == NULL) {return false;}

    return circbuf->len == 0;
}

void circbuf_clear(circbuf_t* circbuf){
    if(circbuf == NULL) {return;}

    circbuf->len = 0;
}
