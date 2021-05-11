/* saru/buf.h */
#ifndef SARU_BUF_H
#define SARU_BUF_H

#include <stddef.h> /* for size_t */

/**
 * structure: saru_buf,
 * definition: a generic buffer of len elements
 * NOTE: buf must be last so that offsetof(saru_buf, buf)
 *       can take into account any padding that is used before it
 */
struct saru_buf {
    void  **buf;
    size_t len;
};

/* interface */
struct saru_buf *sb_create(size_t len);
void sb_destroy(struct saru_buf *sb);
void sb_fill(struct saru_buf *sb, int c);
size_t sb_len(struct saru_buf *sb);
void sb_put(struct saru_buf *sb, void *elem, size_t i);
void *sb_get(struct saru_buf *sb, size_t i);
void sb_print(struct saru_buf *sb, void (*print)(void *));

#define SB_CREATE(sbm, len) \
    struct saru_buf *sbm; \
    sbm = sb_create(len);

#define SB_FOREACH(item, sb) \
    for(int keep = 1, \
            count = 0,\
            size = sb->len * sizeof(void *); \
        keep && count != size; \
        keep = !keep, count++) \
      for(item = (sb->buf) + count; keep; keep = !keep)

#endif
