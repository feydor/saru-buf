/* saru/ucharbuf.c */
#include "saru-bytebuf.h"
#include <stdio.h>  /* for printf */
#include <stdlib.h> /* for malloc */
#include <string.h> /* for memset */

/**
 * returns: a heap-allocated saru_bytemat pointer with its buffer initialized
 * to all zeros notes: must be destroyed by saru_destroy_usbm2d
 */
struct saru_bytemat *
sbm_create(size_t wid, size_t hgt)
{
    struct saru_bytemat *sbm = malloc(sizeof(struct saru_bytemat));
    if (!sbm)
        return NULL;

    sbm->buf = malloc(wid * hgt);
    if (!sbm->buf)
        return NULL;

    memset(sbm->buf, 0, wid * hgt);
    sbm->wid = wid;
    sbm->hgt = hgt;
    sbm->col = sbm->row = 0;
    sbm->len = wid * hgt;
    return sbm;
}

/**
 * returns: a heap-allocated struct saru_bytemat pointer with its buffer set
 * to the passed-in buf param 
 * notes: must be destroyed by sdm_destroy, which frees the passed in buf
 */
struct saru_bytemat *
sbm_wrap(unsigned char *buf, size_t wid, size_t hgt)
{
    struct saru_bytemat *sbm = malloc(sizeof(struct saru_bytemat));
    if (sbm) {
        sbm->buf = buf;
        sbm->wid = wid;
        sbm->hgt = hgt;
        sbm->col = sbm->row = 0;
        sbm->len = wid * hgt;
    }
    return sbm;
}

/**
 * returns the byte in thje ith place, if it is inbounds
 * otherwise it returns BYTE_MAX
 */
byte 
sbm_geti(struct saru_bytemat *sbm, size_t i)
{
    if (i < sbm->len)
        return sbm->buf[i];
    return BYTE_MAX;
}

/**
 * returns the byte at row x and height y, if they are within bounds
 * otherwise it returns BYTE_MAX
 */
byte 
sbm_getxy(struct saru_bytemat *sbm, size_t x, size_t y)
{
    if (x < sbm->wid && y < sbm->hgt)
        return sbm->buf[y * sbm->wid + y];
    return BYTE_MAX;
}

/**
 * sums two mxn matrices (x and y) and populates out with the result
 */
void
sbm_sum(struct saru_bytemat *x, struct saru_bytemat *y, struct saru_bytemat *out) {
    if (x->wid == y->wid && x->hgt == y->hgt &&
        out->wid == x->wid && out->hgt == x->hgt)
        for (size_t i = 0; i < x->len; i++)
            out->buf[i] = x->buf[i] + y->buf[i];
}

/**
 * returns the grand sum of the elements in the matrix
 */
size_t
sbm_gsum(struct saru_bytemat *sbm)
{
    size_t sum = 0;
    for (size_t i = 0; i < sbm->len; i++)
        sum += sbm->buf[i];
    return sum;
}

void
sbm_fill(struct saru_bytemat *sbm, byte c)
{
    memset(sbm->buf, c, sbm->len);
}

size_t
sbm_size(struct saru_bytemat *sbm)
{
    return sbm->len;
}

/**
 * returns 1 if for every element in x there is a corresponding element
 * in y, otherwise 0
 */
int 
sbm_injective(struct saru_bytemat *x, struct saru_bytemat *y)
{
   return (x->wid <= y->wid && x->hgt <= y->hgt);
}

/**
 * returns 1 if for every element in submatrix x
 * there is a corresponding element in submatrix y
 * otherwise 0,
 * submatrices are accessed using the row and col members
 */
int 
sbm_subinjective(struct saru_bytemat *x, struct saru_bytemat *y)
{
   return x->col + y->wid <= x->wid && x->row + y->hgt <= x->hgt;
}

/**
 * iterates through x
 * each iteration, the row and col members are updated before caling func
 */
void
sbm_foreach(struct saru_bytemat *x, void (*func)(struct saru_bytemat *))
{
    for (x->row = 0; x->row < x->hgt; x->row++)
        for (x->col = 0; x->col < x->wid; x->col++)
            func(x);
}

void
sbm_print(struct saru_bytemat *sbm)
{
    for (size_t i = 0; i < sbm->len; i++)
        printf("%u ", sbm->buf[i]);
    printf("\n");
}

void
sbm_destroy(struct saru_bytemat *sbm)
{
    free(sbm->buf);
    free(sbm);
}
