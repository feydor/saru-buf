/* test/bytebuf.c */
#include <stdlib.h> /* for malloc */
#include <unity.h>

#include "saru-bytebuf.h"

/* test prototypes */
void setUp(void);
void tearDown(void);
void test_init_functions(void);
void test_2d_iteration(void);

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_init_functions);
    RUN_TEST(test_2d_iteration);
}

void
setUp(void)
{
    // set stuff up here
}

void
tearDown(void)
{
    // clean stuff up here
}

void
test_init_functions(void)
{
    /* test initial values from saru_create_ucharbuf2d */
    struct saru_bytemat *b1;
    b1 = sbm_create(3, 4);

    // TEST_ASSERT_EACH_EQUAL_UINT(0, b1->buf, b1->len);
    TEST_ASSERT_EQUAL(12, b1->len);
    TEST_ASSERT_EQUAL(3, b1->wid);
    TEST_ASSERT_EQUAL(4, b1->hgt);

    /* simple iteration */
    byte *bp = b1->buf;
    for (size_t i = 0; i < b1->len; i++)
        TEST_ASSERT_EQUAL(0, *(bp++));

    /* with saru_foreach macro*/
    sbm_foreach(byte *c, b1) {
        TEST_ASSERT_EQUAL(0, *c);
    }

    /* test initial values from saru_create_ucharbuf2d_from_uchar */
    struct saru_bytemat *b2;
    byte *bytes = malloc(3);
    bytes[0] = 255;
    bytes[1] = 0;
    bytes[2] = 100;

    b2 = sbm_wrap(bytes, 3, 1);
    TEST_ASSERT_EQUAL(255, b2->buf[0]);
    TEST_ASSERT_EQUAL(0, b2->buf[1]);
    TEST_ASSERT_EQUAL(100, b2->buf[2]);

    sbm_destroy(b1);
    sbm_destroy(b2);
}

void
test_2d_iteration(void)
{
    struct saru_bytemat *sbm;
    sbm = sbm_create(6, 5);

    for (sbm->row = 0; sbm->row < sbm->hgt; sbm->row++)
        for (sbm->col = 0; sbm->col < sbm->wid; sbm->col++)
            TEST_ASSERT_EQUAL(0, sbm->buf[sbm->row * sbm->wid + sbm->col]);

    sbm_destroy(sbm);
}

