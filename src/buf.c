/* saru/buf.c */
#include "saru-buf.h"
#include <stddef.h> /* for NULL */
#include <stdio.h>  /* for printf */
#include <stdlib.h> /* for malloc, calloc */
#include <string.h> /* for memset */

/**
 * inits the buffer with space for len pointers
 */
static void
sb_init(struct saru_buf *sb, size_t len)
{
    sb->buf = (void **) malloc(sizeof(void *) * len);
    sb->len = len;
}

struct saru_buf *
sb_create(size_t len)
{
    struct saru_buf *sb = malloc(sizeof(struct saru_buf));
    if (sb)
        sb_init(sb, len);
    return sb;
}

void
sb_destroy(struct saru_buf *sb)
{
    free(sb->buf);
    free(sb);
}

size_t
sb_len(const struct saru_buf *sb)
{
    return sb->len;
}

/**
 * copies n characters from str into the buffer
 */
void
sb_strcpy(struct saru_buf *sb, char *str, size_t n)
{
    sb_memcpy(sb, (void *)str, n, sizeof(char));
}

/**
 * copies n elements of typesize bytes from src into the buffer
 */
void
sb_memcpy(struct saru_buf *sb, void *src, size_t n, size_t typesize)
{
    if (n <= sb->len)
        for (size_t i = 0; i < n; i++) {
            sb->buf[i] = (void *)src;
            src = (void *)((char *)src + typesize);
        }
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
sb_get(const struct saru_buf *sb, size_t i)
{
    if (i < sb->len)
        return sb->buf[i]; 
    return NULL;
}

/**
 * calls the passed in print function on each pointer of the buffer
 */
void
sb_print(const struct saru_buf *sb, void (*print)(void *))
{
    if (!sb || !sb->buf || !print)
        return;

    for (size_t i = 0; i < sb->len; i++)
        print(sb_get(sb, i));
}
