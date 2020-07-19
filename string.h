#ifndef STRING_H
#define STRING_H

#include "stddef.h"

static inline void *memcpy(void *dest, const void *src, size_t count) {
    unsigned char *destc = dest;
    unsigned char *deste = destc + count;
    const unsigned char *srcc = src;
    while (destc != deste) {
        *destc++ = *srcc++;
    }
    return dest;
}

static inline void *memmove(void *dest, const void *src, size_t count) {
    unsigned char *destc = dest;
    unsigned char *deste = destc + count;
    const unsigned char *srcc = src;
    if (destc < srcc) {
        while (destc != deste) {
            *destc++ = *srcc++;
        }
    } else {
        srcc += count;
        while (destc != deste) {
            *--deste = *--srcc;
        }
    }
    return dest;
}

static inline void *memset(void *dest, int ch, size_t count) {
    unsigned char *destc = dest;
    unsigned char *deste = destc + count;
    while (destc != deste) {
        *destc++ = ch;
    }
    return dest;
}

#endif
