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
sbm_geti(const struct saru_bytemat *sbm, size_t i)
{
    if (i < sbm->len)
        return sbm->buf[i];
    return BYTE_MAX;
}

/**
 * returns the byte at col x and row y, if they are within bounds
 * otherwise it returns BYTE_MAX
 */
byte 
sbm_getxy(const struct saru_bytemat *sbm, size_t x, size_t y)
{
    if (x < sbm->wid && y < sbm->hgt)
        return sbm->buf[y * sbm->wid + x];
    return BYTE_MAX;
}

/**
 * puts the byte b into col x and row y, if they are within bounds
 */
void 
sbm_putxy(struct saru_bytemat *sbm, byte b, size_t x, size_t y)
{
    if (x < sbm->wid && y < sbm->hgt)
        sbm->buf[y * sbm->wid + x] = b;
}

/**
 * sums two mxn matrices (x and y) and returns a new saru_bytemat pointer
 * containing the results
 * NOTE: the returned pointer must be freed with sbm_destroy
 */
struct saru_bytemat *
sbm_sum(const struct saru_bytemat *x, const struct saru_bytemat *y) {
    if (x->wid == y->wid && x->hgt == y->hgt) {
        struct saru_bytemat *res;
        res = sbm_create(x->wid, x->hgt);
        for (size_t i = 0; i < x->len; i++)
            res->buf[i] = x->buf[i] + y->buf[i];
        return res;
    }
    return NULL;
}

/**
 * returns the grand sum of the elements in the matrix
 */
size_t
sbm_gsum(const struct saru_bytemat *sbm)
{
    size_t sum = 0;
    for (size_t i = 0; i < sbm->len; i++)
        sum += sbm->buf[i];
    return sum;
}

/**
 * fills the matrix with c
 */
void
sbm_fill(struct saru_bytemat *sbm, byte c)
{
    memset(sbm->buf, c, sbm->len);
}

size_t
sbm_size(const struct saru_bytemat *sbm)
{
    return sbm->len;
}

/**
 * returns 1 if for every element in t there is a corresponding element
 * in f, otherwise 0
 */
int 
sbm_injective(const struct saru_bytemat *t, const struct saru_bytemat *f)
{
   return t->wid <= f->wid && t->hgt <= f->hgt;
}

/**
 * returns 1 if for every element in submatrix t
 * there is a corresponding element in submatrix f
 * ie f > t
 * otherwise 0,
 * submatrices are accessed using the row and col members
 */
int 
sbm_subinjective(const struct saru_bytemat *t, const struct saru_bytemat *f)
{
    return t->wid + f->col <= f->wid &&
           t->hgt + f->row <= f->hgt;
}

/**
 * returns the maximum value in the matrix
 * and sets the optional row and col parameters to its coordinates
 */
size_t
sbm_max(const struct saru_bytemat *x, size_t *col, size_t *row)
{
    size_t maxrow = 0, maxcol = 0;
    size_t tmax = 0;
    for (size_t row = 0; row < x->hgt; row++)
        for (size_t col = 0; col < x->wid; col++) {
            const byte b = sbm_getxy(x, col, row);
            if (b > tmax) {
                tmax = b;
                maxrow = row;
                maxcol = col;
            }
        }

    if (col)
        *col = maxcol;
    if (row)
        *row = maxrow;
    return tmax;
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
sbm_print(const struct saru_bytemat *sbm)
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
