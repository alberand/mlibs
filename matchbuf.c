#include "matchbuf.h"

void matchbuf_init(matchbuf_t* matchbuf, const char* pattern, const cb_t cb){
    matchbuf->pattern = pattern;
    matchbuf->cursor = 0;
    matchbuf->cb = cb;
}

bool matchbuf_accept(matchbuf_t* matchbuf, const uint8_t* bytes, const size_t index){
    if(matchbuf == NULL) {return -1;}

    // Any char
    if(matchbuf->pattern[matchbuf->cursor] == '*'){
        matchbuf->cursor++;
        return true;
    }

    // wrong char
    if(matchbuf->pattern[matchbuf->cursor] != bytes[index]){
        matchbuf_reset(matchbuf);
        return false;
    }

    // correct char
    if(matchbuf->pattern[matchbuf->cursor] == bytes[index]){
        if(matchbuf->pattern[++matchbuf->cursor] == '\0'){
            size_t size = sizeof(matchbuf->pattern)/sizeof(matchbuf->pattern[0]) - 1;
            matchbuf->cb((bytes + 1) + (index - size), size);

            matchbuf_reset(matchbuf);
        }

        return true;
    }

    return false;
}

void matchbuf_reset(matchbuf_t* matchbuf){
    matchbuf->cursor = 0;
}
