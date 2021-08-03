#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "circbuf.h"
#include "matchbuf.h"

void test_1(){
    char c;
    const char str[] = "123456789ABCDEF";

    circbuf_t* buf = circbuf_init(11, sizeof(char));

    for(int i = 0; i < 10; i++){
        circbuf_push(buf, (const void*)(str+i));
    }

    assert(!circbuf_overflow(buf));
    assert(!circbuf_empty(buf));

    printf("pop: ");
    for(int i = 0; i < 10; i++){
        circbuf_pop(buf, (void*)&c);
        printf("%c", c);
    }
    printf("\n");

    assert(!circbuf_overflow(buf));
    assert(circbuf_empty(buf));

    for(int i = 0; i < 16; i++){
        circbuf_push(buf, (const void*)(str+i));
    }

    assert(!circbuf_overflow(buf));
    assert(!circbuf_empty(buf));

    printf("pop: ");
    for(int i = 0; i < 16; i++){
        circbuf_pop(buf, (void*)&c);
        printf("%c", c);
    }
    printf("\n");

    assert(!circbuf_overflow(buf));
    assert(circbuf_empty(buf));
}

void test_2(){
    typedef struct dummy_t {
        int8_t a;
        uint32_t b;
    } dummy_t;

    dummy_t dummy;

    circbuf_t* buf = circbuf_init(5, sizeof(dummy_t));

    dummy_t arr[] = {{-42, 1}, {-41, 2}, {-40, 3}, {-39, 4}, {-38, 5}};

    for(int i = 0; i < 5; i++){
        circbuf_push(buf, (const void*)(arr+i));
    }

    assert(!circbuf_overflow(buf));
    assert(!circbuf_empty(buf));

    printf("pop:\n");
    for(int i = 0; i < 5; i++){
        circbuf_pop(buf, (void*)&dummy);
        printf("a = %d; b = %d\n", dummy.a, dummy.b);
    }
    printf("\n");

    assert(!circbuf_overflow(buf));
    assert(circbuf_empty(buf));
}

void test_3_callback(const uint8_t* buffer, const size_t size){
    printf("RX(%d): %.*s\n", size, size, buffer);
}

void test_3(){
    const char* msg = "23nd9f~23;24~a;en~abc**!AT:2%#~67;92~!!!330ad";
    
    matchbuf_t match;
    matchbuf_init(&match, "~**;**~", &test_3_callback);
    
    for(int i = 0; i < strlen(msg); i++){
        matchbuf_accept(&match, msg, i);
    }
}

int main(){
    int8_t rc = 0;

    // test_1();
    // test_2();
    test_3();

    return rc;
}
