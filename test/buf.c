/* test/buf.c */
#include "saru-buf.h"
#include <stdio.h>
#include <stdlib.h> /* for malloc */
#include <unity.h>

/* test prototypes */
void setUp(void);
void tearDown(void);
void test_init_functions(void);
// void test_iteration(void);

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_init_functions);
    // RUN_TEST(test_iteration);
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
    /* test initial values */
    struct saru_buf ints; // will contain 100 ints
    saru_bufinit(&ints, 100, sizeof(int));
    struct saru_buf *ip = &ints;
    // ints = saru_createbuf(100);

    // TEST_ASSERT_EACH_EQUAL_INT(0, (int *)ip->buf, ip->len);
    TEST_ASSERT_EQUAL(100, ip->len);

    printf("%d\n", *((int *)saru_bufget(ip, 0)));

    /* simple iteration */
    // for (size_t i = 0; i < ints.len ; i++)
    // TEST_ASSERT_EQUAL(0, *(int *)&saru_bufget(&ints, i));
    // printf("%d ", *(int *)saru_bufget(&ints, i));

    /* with saru_foreach macro*/
    /*
    saru_foreach(void *elem,, ints) {
        TEST_ASSERT_EQUAL(0, *(int *)elem);
    }
    */

    saru_destroybuf(ip);
}
