/* saru/ucharbuf.h */
#ifndef SARU_BYTEBUF_H
#define SARU_BYTEBUF_H

#include <stddef.h> /* for size_t, NULL */

#define byte unsigned char
#define BYTE_MAX 255

/**
 * structure: saru_bytebuf,
 * definition: a buffer of len unsigned bytes
 */
struct saru_bytebuf {
    byte  *buf;
    size_t len;
};

/**
 * structure: saru_bytemat,
 * definition: a two-dimensional buffer of size unsigned bytes
 */
struct saru_bytemat {
    byte  *buf;
    size_t len;
    size_t wid;
    size_t hgt;
    size_t col;
    size_t row;
};

/* interface */
struct saru_bytemat *sbm_create(size_t wid, size_t hgt);
struct saru_bytemat *sbm_wrap(byte *buf, size_t wid,
                                         size_t hgt);
byte sbm_getxy(struct saru_bytemat *sbm, size_t x, size_t y);
void sbm_sum(struct saru_bytemat *x, struct saru_bytemat *y, 
                                     struct saru_bytemat *out);
size_t sbm_gsum(struct saru_bytemat *sbm);
size_t sbm_size(struct saru_bytemat *sbm);
void sbm_print(struct saru_bytemat *sbm);
void sbm_destroy(struct saru_bytemat *sbm);

/* macros */
// #define saru_bufsize(buf) (sizeof(buf) / sizeof(buf[0]))
#define sbm_foreach(item, sb)                                                 \
    for (int keep = 1, count = 0, size = sb->len; keep && count != size;       \
         keep = !keep, count++)                                                \
	for (item = (sb->buf) + count; keep; keep = !keep)

#endif
