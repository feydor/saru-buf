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

byte sbm_getxy(const struct saru_bytemat *sbm, size_t x, size_t y);

byte sbm_geti(const struct saru_bytemat *sbm, size_t i);

void sbm_putxy(struct saru_bytemat *sbm, byte b, size_t x, size_t y);

void sbm_sum(const struct saru_bytemat *x, const struct saru_bytemat *y, 
                                           struct saru_bytemat *out);

size_t sbm_gsum(const struct saru_bytemat *sbm);

void sbm_fill(struct saru_bytemat *sbm, byte c);

size_t sbm_size(const struct saru_bytemat *sbm);

int sbm_injective(const struct saru_bytemat *x, const struct saru_bytemat *y);

int sbm_subinjective(const struct saru_bytemat *x, const struct saru_bytemat *y);

size_t sbm_max(struct saru_bytemat *x);

void sbm_foreach(struct saru_bytemat *x, void (*func)(struct saru_bytemat *));

void sbm_print(const struct saru_bytemat *sbm);

void sbm_destroy(struct saru_bytemat *sbm);

/* macros */
#define SBM_CREATE(sbm, wid, hgt) \
    struct saru_bytemat *sbm; \
    sbm = sbm_create(wid, hgt);

#define SBM_WRAP(sbm, buf, wid, hgt) \
    struct saru_bytemat *sbm; \
    sbm = sbm_wrap(buf, wid, hgt);

/**
 * taken from: https://stackoverflow.com/questions/400951/does-c-have-a-foreach-loop-construct
 */
#define SBM_FOREACH(item, sb)                                                 \
    for (int keep = 1, count = 0, size = sb->len; keep && count != size;       \
         keep = !keep, count++)                                                \
	for (item = (sb->buf) + count; keep; keep = !keep)

#endif
