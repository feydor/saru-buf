/* test/ucharbuf2d.c */
#include <stdlib.h> /* for malloc */
#include <unity.h>

#include "saru-ucharbuf.h"

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
    struct saru_ucharbuf2d *b1;
    b1 = saru_create_ucharbuf2d(3, 4);

    // TEST_ASSERT_EACH_EQUAL_UINT(0, b1->buf, b1->len);
    TEST_ASSERT_EQUAL(12, b1->len);
    TEST_ASSERT_EQUAL(3, b1->width);
    TEST_ASSERT_EQUAL(4, b1->height);

    /* simple iteration */
    unsigned char *bp = b1->buf;
    for (size_t i = 0; i < b1->len; i++)
	TEST_ASSERT_EQUAL(0, *(bp++));

    /* with saru_foreach macro*/
    saru_foreach(unsigned char *c, b1)
    {
	TEST_ASSERT_EQUAL(0, *c);
    }

    /* test initial values from saru_create_ucharbuf2d_from_uchar */
    struct saru_ucharbuf2d *b2;
    unsigned char *uchars = malloc(3);
    uchars[0] = 255;
    uchars[1] = 0;
    uchars[2] = 100;

    b2 = saru_wrap_ucharbuf2d(uchars, 3, 1);
    unsigned char *buf = b2->buf;
    TEST_ASSERT_EQUAL(255, buf[0]);
    TEST_ASSERT_EQUAL(0, buf[1]);
    TEST_ASSERT_EQUAL(100, buf[2]);

    saru_destroy_ucharbuf2d(b1);
    saru_destroy_ucharbuf2d(b2);
}

void
test_2d_iteration(void)
{
    struct saru_ucharbuf2d *ucb;
    ucb = saru_create_ucharbuf2d(6, 5);

    for (ucb->row = 0; ucb->row < ucb->height; ucb->row++)
	for (ucb->col = 0; ucb->col < ucb->width; ucb->col++)
	    TEST_ASSERT_EQUAL(0, ucb->buf[ucb->row * ucb->width + ucb->col]);

    saru_destroy_ucharbuf2d(ucb);
}
