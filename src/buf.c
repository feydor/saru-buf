/* saru/buf.c */
#include "saru-buf.h"
#include <stddef.h> /* for NULL */
#include <stdio.h>  /* for printf */
#include <stdlib.h> /* for malloc, calloc */
#include <string.h> /* for memset */

/**
 * initilizes the buffer with space for len pointers
 * ex: saru_initbuf(&sb, 100, sizeof(int))
 *     inits sb to hold 100 ints, all set to 0
 * NOTE: must be freed by saru_destroybuf
 */
void
sb_init(struct saru_buf *sb, size_t len)
{
    sb->buf = (void **) malloc(sizeof(void *) * len);
    sb->len = len;
}

void
sb_destroy(struct saru_buf *sb)
{
    if (sb->buf)
	    free(sb->buf);
}

/**
 * fills the buffer with pointers to ints containing c
 */
void
sb_fill(struct saru_buf *sb, int c)
{
    int arr[sb->len];
    memset(arr, c, sb->len * sizeof(int));
    for (size_t i = 0; i < sb->len; i++)
        sb->buf[i] = (void *)&arr[i];
}

size_t
sb_len(struct saru_buf *sb)
{
    return sb->len;
}

/**
 * puts ptr in the ith spot of sb
 */
void
sb_put(struct saru_buf *sb, void *ptr, size_t i)
{
    if (i < sb->len)
        sb->buf[i] = ptr;
}

/**
 * returns the ith pointer in sb
 */
void *
sb_get(struct saru_buf *sb, size_t i)
{
    if (sb && i < sb->len)
        return sb->buf[i]; 
    return NULL;
}

/**
 * calls the passed in print function on each pointer of the buffer
 */
void
sb_print(struct saru_buf *sb, void (*print)(void *))
{
    if (!sb || !sb->buf || !print)
        return;

    for (size_t i = 0; i < sb->len; i++)
        print(sb_get(sb, i));
}
