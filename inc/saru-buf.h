/* saru/buf.h */
#ifndef SARU_BUF_H
#define SARU_BUF_H

#include <stddef.h> /* for size_t */

/**
 * structure: saru_buf,
 * definition: a generic buffer of len elements
 */
struct saru_buf {
    void **buf;
    size_t len;
};

/* interface */
struct saru_buf *saru_createbuf(size_t len);
void saru_bufinit(struct saru_buf *sb, size_t len, size_t typesize);
void saru_destroybuf(struct saru_buf *sb);
size_t saru_bufsize(struct saru_buf *sb);
void *saru_bufget(struct saru_buf *sb, size_t i);
void saru_printbuf(struct saru_buf *sb, void (*print)(void *));

#define saru_foreach(item, sb)                                                 \
    for (int keep = 1, count = 0, size = sb->len * sizeof(void *);             \
         keep && count != size; keep = !keep, count++)                         \
	for (item = (sb->buf) + count; keep; keep = !keep)
#endif
