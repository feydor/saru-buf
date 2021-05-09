/* saru/buf.c */
#include "saru-buf.h"
#include <stddef.h> /* for NULL */
#include <stdio.h>  /* for printf */
#include <stdlib.h> /* for malloc, calloc */
#include <string.h> /* for memset */

struct saru_buf *
saru_createbuf(size_t len)
{
    struct saru_buf *sb = malloc(sizeof(struct saru_buf));
    if (!sb)
	return NULL;
    sb->buf = (void **)malloc(len * sizeof(void *));
    if (!sb->buf)
	return NULL;
    memset(sb->buf, 0, len * sizeof(void *));
    sb->len = len;
    return sb;
}

/**
 * initilizes the buffer with typesize bytes of len elements
 */
void
saru_bufinit(struct saru_buf *sb, size_t len, size_t typesize)
{
    sb->buf = calloc(len, typesize);
    sb->len = len;
}

void
saru_destroybuf(struct saru_buf *sb)
{
    if (sb->buf)
	free(sb->buf);
}

size_t
saru_bufsize(struct saru_buf *sb)
{
    return sb->len * sizeof(void *);
}

void *
saru_bufget(struct saru_buf *sb, size_t i)
{
    if (sb && i < sb->len)
	return sb->buf[i];
    return NULL;
}

/**
 * calls the passed in print function on each elem of the buffer
 */
void
saru_printbuf(struct saru_buf *sb, void (*print)(void *))
{
    if (!sb || !sb->buf || !print)
	return;

    for (size_t i = 0; i < sb->len; i++)
	print(sb->buf[i]);
}
