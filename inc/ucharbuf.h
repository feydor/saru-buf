/* saru/ucharbuf.h */
#ifndef SARU_UCHARBUF_H
#define SARU_UCHARBUF_H

/**
 * structure: Saru_UCharBuf,
 * definition: a buffer of len unsigned bytes
 * notes: takes advantage of the fact that char is always 1 byte
 */
typedef struct {
    unsigned char *buf;
    unsigned int len;
} Saru_UCharBuf;

/**
 * structure: Saru_UCharBuf2d,
 * definition: a two-dimension buffer of size unsigned bytes
 */
typedef struct {
    Saru_UCharBuf base;
    unsigned int   width;
    unsigned int   height;
    unsigned int   col;
    unsigned int   row;
} Saru_UCharBuf2d;

/* interface */
Saru_UCharBuf2d *Saru_create_UCharBuf2d(unsigned int width, 
        unsigned int height);
Saru_UCharBuf2d *Saru_create_UCharBuf2d_from_uchar(unsigned char *buf,
        unsigned int width, unsigned int height);
void Saru_destroy_UCharBuf2d(Saru_UCharBuf2d *b);
unsigned int Saru_sum_UCharBuf2d(Saru_UCharBuf2d *ub) 
void Saru_print_UCharBuf2d(Saru_UCharBuf2d *b);

#endif
