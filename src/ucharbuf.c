/* saru/ucharbuf.c */
// #include "../inc/saru-buf.h"
#include "saru-buf.h"

/**
 * function: saru_create_ucb2d,
 * returns: a heap-allocated saru_ucharbuf2d pointer with its buffer initialized to all zeros
 * notes: must be destroyed by saru_destroy_ucb2d
 */
struct saru_ucharbuf2d *
saru_create_ucharbuf2d(size_t width, size_t height)
{
    struct saru_ucharbuf2d *ub = malloc( sizeof(struct saru_ucharbuf2d) );
    if (!ub)
        return NULL;

    ub->buf = malloc( width * height );
    if (!ub->buf)
        return NULL;

    memset( ub->buf, 0, width * height );
    ub->width = width;
    ub->height = height;
    ub->col = ub->row = 0;
    ub->len = width * height;
    return ub;
}

/**
 * function: saru_create_ucb2d_from_uchar,
 * returns: a heap-allocated struct saru_ucharbuf2d pointer with its buffer set to the passed-in buf param
 * notes: must be destroyed by saru_destroy_ucharbuf2d,
 *        buf must not be NULL
 */
struct saru_ucharbuf2d *
saru_create_ucharbuf2d_from_uchar(unsigned char *buf, size_t width, size_t height) 
{
    struct saru_ucharbuf2d *ub = malloc( sizeof(struct saru_ucharbuf2d) );
    if (!ub || !buf)
        return NULL;

    ub->buf = buf;
    ub->width = width;
    ub->height = height;
    ub->col = ub->row = 0;
    ub->len = width * height;
    return ub;
}

void 
saru_destroy_ucharbuf2d(struct saru_ucharbuf2d *ub) 
{
  if (ub->buf) {
    free(ub->buf);
    if (ub) 
      free(ub);
  }
}

/**
 * function: saru_sum_ucharbuf2d,
 * returns: the summation of the elements in the ucharbuf,
 *          if the buf is NULL, it returns 0
 */
size_t
saru_sum_ucharbuf2d(struct saru_ucharbuf2d *ub) 
{
    if (!ub)
        return 0;

    size_t sum = 0;
    for (size_t i = 0; i < ub->len; i++)
        sum += ub->buf[i];
    return sum;
}

void 
saru_print_ucharbuf2d(struct saru_ucharbuf2d *ub) 
{
    if (!ub->buf) return;
    for (size_t i = 0; i < ub->len; i++)
        printf("%u ", ub->buf[i]);
}

