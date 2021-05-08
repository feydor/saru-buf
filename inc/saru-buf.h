/* saru/ucharbuf.h */
#ifndef SARU_UCHARBUF_H
#define SARU_UCHARBUF_H

#include <stdlib.h> /* for malloc */
#include <stddef.h> /* for NULL */
#include <string.h> /* for memset */
#include <stdio.h> /* for printf */

/**
 * structure: saru_ucharbuf,
 * definition: a buffer of len unsigned bytes
 * notes: takes advantage of the fact that char is always 1 byte
 */
struct saru_ucharbuf {
    unsigned char *buf;
    size_t   len;
};

/**
 * structure: saru_ucharbuf2d,
 * definition: a two-dimension buffer of size unsigned bytes
 */
struct saru_ucharbuf2d {
    unsigned char *buf;
    size_t   len;
    size_t   width;
    size_t   height;
    size_t   col;
    size_t   row;
};

/* interface */
struct saru_ucharbuf2d * 
saru_create_ucharbuf2d(size_t width,size_t height);

struct saru_ucharbuf2d * 
saru_create_ucharbuf2d_from_uchar(unsigned char *buf, size_t width, size_t height); 

void 
saru_destroy_ucharbuf2d(struct saru_ucharbuf2d *ub); 

size_t 
saru_sum_ucharbuf2d(struct saru_ucharbuf2d *ub); 

void 
saru_print_ucharbuf2d(struct saru_ucharbuf2d *ub);

/* macros */
#define saru_foreach(item, array, size) \
    for(size_t keep = 1,\
               count = 0;\
               keep && count != size; \
               keep = !keep, count++) \
        for(item = (array) + count; keep; keep = !keep)

#endif
