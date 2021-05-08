/* saru/ucharbuf.c */
#include "../inc/ucharbuf.h"

/**
 * function: Saru_create_UCharBuf2d,
 * returns: a heap-allocated Saru_UCharBuf2d pointer with its buffer initialized to all zeros
 * notes: must be destroyed by Saru_destroy_UCharBuf2d
 */
Saru_UCharBuf2d *
Saru_create_UCharBuf2d(unsigned int width, unsigned int height) 
{
    Saru_UCharBuf2d *ub = malloc( sizeof(Saru_UCharBuf2d) );
    if (!ub)
        return NULL;

    ub->buf = malloc( width * height );
    if (!ub->buf)
        return NULL;

    memset( ub->buf, 0, width * height );
    ub->width = width;
    ub->height = height;
    ub->col = ub->row = 0;
    ub->size = width * height;
    return ub;
}

/**
 * function: Saru_create_UCharBuf2d_from_uchar,
 * returns: a heap-allocated Saru_UCharBuf2d pointer with its buffer set to the passed-in buf param
 * notes: must be destroyed by destroy_UCharBuffer,
 *        buf must not be NULL
 */
Saru_UCharBuffer *
create_UCharBuffer_from_uchar(unsigned char *buf, unsigned int width, unsigned int height) 
{
    Saru_UCharBuf2d *ub = malloc( sizeof(Saru_UCharBuf2d) );
    if (!ub || !buf)
        return NULL;

    ub->buf = buf;
    ub->width = width;
    ub->height = height;
    ub->col = ub->row = 0;
    ub->size = width * height;
    return ub;
}

void 
Saru_destroy_UCharBuf2d(Saru_UCharBuf2d *ub) 
{
  if (ub->buf) {
    free(ub->buf);
    if (ub) 
      free(ub);
  }
}

unsigned int
Saru_sum_UCharBuf2d(Saru_UCharBuf2d *ub) 
{
    unsigned int sum = 0;
    for (unsigned int i = 0; i < ub->size; i++)
        sum += ub->buf[i];
    return sum;
}

void 
Saru_print_UCharBuf2d(Saru_UCharBuf2d *ub) 
{
    if (!ub->buf) return;
    for (unsigned int i = 0; i < ub->size; i++)
        printf("%u ", ub->buf[i]);
}

