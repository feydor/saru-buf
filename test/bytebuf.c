/* test/bytebuf.c */
#include <stdlib.h> /* for malloc */
#include <unity.h>

#include "saru-bytebuf.h"

/* test prototypes */
void setUp(void);
void tearDown(void);
void test_sbm_create(void);
void test_sbm_wrap(void);
void test_sbm_getxy(void);
void test_sbm_sum(void);
void test_sbm_gsum(void);
void test_sbm_foreach_macro(void);
void test_sbm_bijection(void);
void test_sbm_subbijection(void);
void test_sbm_foreach(void);

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_sbm_create);
    RUN_TEST(test_sbm_wrap);
    RUN_TEST(test_sbm_getxy);
    RUN_TEST(test_sbm_sum);
    RUN_TEST(test_sbm_gsum);
    RUN_TEST(test_sbm_foreach_macro);
    RUN_TEST(test_sbm_bijection);
    RUN_TEST(test_sbm_subbijection);
    RUN_TEST(test_sbm_foreach);
}

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test_sbm_create(void)
{
    struct saru_bytemat *sbm;
    size_t wid, hgt;
    wid = 3;
    hgt = 4;
    sbm = sbm_create(wid, hgt);
    
    TEST_ASSERT_EQUAL(wid * hgt, sbm->len);
    TEST_ASSERT_EQUAL(wid, sbm->wid);
    TEST_ASSERT_EQUAL(hgt, sbm->hgt);
    
    for (size_t i = 0; i < sbm->len; i++)
        TEST_ASSERT_EQUAL(0, sbm->buf[0]);

    sbm_destroy(sbm);
}

void test_sbm_wrap(void)
{
    size_t wid, hgt;
    wid = 3;
    hgt = 1;
    byte *bytes = malloc(wid);
    bytes[0] = 255;
    bytes[1] = 0;
    bytes[2] = 100;
    
    struct saru_bytemat *sbm;
    sbm = sbm_wrap(bytes, wid, hgt);
    TEST_ASSERT_EQUAL(255, sbm->buf[0]);
    TEST_ASSERT_EQUAL(0, sbm->buf[1]);
    TEST_ASSERT_EQUAL(100, sbm->buf[2]);
    TEST_ASSERT_EQUAL_PTR(bytes, sbm->buf);
    
    sbm_destroy(sbm);
}

void test_sbm_getxy(void)
{
    struct saru_bytemat *sbm;
    sbm = sbm_create(100, 100);
    
    sbm_fill(sbm, 128);

    for (size_t row = 0; row < sbm->hgt; row++)
        for (size_t col = 0; col < sbm->wid; col++)
            TEST_ASSERT_EQUAL(128, sbm_getxy(sbm, col, row));

    sbm_destroy(sbm);
}

void test_sbm_sum(void)
{
   struct saru_bytemat *x;     
   struct saru_bytemat *y;     
   struct saru_bytemat *res;     

   size_t wid, hgt;
   wid = 1000, hgt = 1000;
   x = sbm_create(wid, hgt);
   y = sbm_create(wid, hgt);
   res = sbm_create(wid, hgt);

   sbm_fill(x, 1);
   sbm_fill(y, 2);

   sbm_sum(x, y, res);

    for (size_t i = 0; i < res->len; i++)
        TEST_ASSERT_EQUAL(3, res->buf[0]);

    sbm_destroy(x);
    sbm_destroy(y);
    sbm_destroy(res);
}

void test_sbm_gsum(void)
{
    struct saru_bytemat *x;
    x = sbm_create(2, 2);
    sbm_fill(x, 1);

    TEST_ASSERT_EQUAL(4, sbm_gsum(x));
    sbm_destroy(x);

    /* cause 'overflow' */
    struct saru_bytemat *y;
    y = sbm_create(2, 2);
    sbm_fill(x, 255);

    TEST_ASSERT_EQUAL(1020, sbm_gsum(y));
    sbm_destroy(y);
}

void test_sbm_foreach_macro(void)
{
    struct saru_bytemat *x;
    x = sbm_create(10, 10);
    sbm_fill(x, 255);

    SBM_FOREACH(byte *b, x) {
        /* pointer to elem b available here */
        TEST_ASSERT_EQUAL(255, *b);
    }
    sbm_destroy(x);
}

void test_sbm_bijection(void)
{
    SBM_CREATE(a, 5, 5);
    SBM_CREATE(b, 5, 5);

    TEST_ASSERT_EQUAL(1, sbm_bijection(a, b));
    sbm_destroy(a);
    sbm_destroy(b);

    /* x is wider than y */
    SBM_CREATE(c, 6, 5);
    SBM_CREATE(d, 5, 5);
    
    TEST_ASSERT_EQUAL(0, sbm_bijection(c, d));
    sbm_destroy(c);
    sbm_destroy(d);

    /* x is taller than y */
    SBM_CREATE(e, 5, 6);
    SBM_CREATE(f, 5, 5);
    TEST_ASSERT_EQUAL(0, sbm_bijection(e, f));
    sbm_destroy(e);
    sbm_destroy(f);

    /* y is wider than x */
    SBM_CREATE(g, 5, 5);
    SBM_CREATE(h, 6, 5);
    TEST_ASSERT_EQUAL(1, sbm_bijection(g, h));
    sbm_destroy(g);
    sbm_destroy(h);
    
    /* y is taller than x */
    SBM_CREATE(i, 5, 5);
    SBM_CREATE(j, 5, 6);
    TEST_ASSERT_EQUAL(1, sbm_bijection(i, j));
    sbm_destroy(i);
    sbm_destroy(j);
}

void test_sbm_subbijection(void)
{
    SBM_CREATE(x, 5, 3);
    SBM_CREATE(y, 3, 3);

    /* there are 3 ways to 'fit' y in x
     * ie there are 3 sub-bijections in x
     */
    size_t hits = 0;
    for (x->row = 0; x->row < x->hgt; x->row++)
        for (x->col = 0; x->col < x->wid; x->col++) {
            if (sbm_subbijection(x, y))
                hits++;
        }

    TEST_ASSERT_EQUAL(3, hits);
    sbm_destroy(x);
    sbm_destroy(y);
}

static void iszero(struct saru_bytemat *sbm)
{
   TEST_ASSERT_EQUAL(0, sbm_getxy(sbm, sbm->col, sbm->row)); 
}

void test_sbm_foreach(void)
{
    SBM_CREATE(x, 12, 6);

    sbm_foreach(x, iszero);
    sbm_destroy(x);
}
