/* saru/ucharbuf.c */
#include "saru-ucharbuf.h"
#include <stdio.h>  /* for printf */
#include <stdlib.h> /* for malloc */
#include <string.h> /* for memset */

/**
 * function: saru_create_ucharbuf2d,
 * returns: a heap-allocated saru_ucharbuf2d pointer with its buffer initialized
 * to all zeros notes: must be destroyed by saru_destroy_ucb2d
 */
struct saru_ucharbuf2d *
saru_create_ucharbuf2d(size_t width, size_t height)
{
    struct saru_ucharbuf2d *cb = malloc(sizeof(struct saru_ucharbuf2d));
    if (!cb)
        return NULL;

    cb->buf = malloc(width * height);
    if (!cb->buf)
        return NULL;

    memset(cb->buf, 0, width * height);
    cb->width = width;
    cb->height = height;
    cb->col = cb->row = 0;
    cb->len = width * height;
    return cb;
}

/**
 * function: saru_wrap_ucharbuf2d,
 * returns: a heap-allocated struct saru_ucharbuf2d pointer with its buffer set
 * to the passed-in buf param notes: must be destroyed by
 * saru_destroy_ucharbuf2d, buf must not be NULL
 */
struct saru_ucharbuf2d *
saru_wrap_ucharbuf2d(unsigned char *buf, size_t width, size_t height)
{
    struct saru_ucharbuf2d *cb = malloc(sizeof(struct saru_ucharbuf2d));
    if (cb) {
        cb->buf = buf;
        cb->width = width;
        cb->height = height;
        cb->col = cb->row = 0;
        cb->len = width * height;
    }
    return cb;
}

void
saru_destroy_ucharbuf2d(struct saru_ucharbuf2d *cb)
{
    free(cb->buf);
    free(cb);
}

/**
 * function: saru_sum_ucharbuf2d,
 * returns: the summation of the elements in the ucharbuf,
 *          if the buf is NULL, it returns 0
 */
size_t
saru_sum_ucharbuf2d(struct saru_ucharbuf2d *cb)
{
    size_t sum = 0;
    for (size_t i = 0; i < cb->len; i++)
        sum += cb->buf[i];
    return sum;
}

void
saru_print_ucharbuf2d(struct saru_ucharbuf2d *cb)
{
    for (size_t i = 0; i < cb->len; i++)
        printf("%u ", cb->buf[i]);
    printf("\n");
}
