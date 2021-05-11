/* test/buf.c */
#include "saru-buf.h"
#include <stdio.h> /* for printf */
#include <stdlib.h> /* for malloc */
#include <string.h> /* for memset */
#include <unity.h>

/* test prototypes */
void setUp(void);
void tearDown(void);
void test_sb_bufinit(void);
void test_sb_bufput_get(void);

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_sb_bufinit);
    RUN_TEST(test_sb_bufput_get);
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
test_sb_bufinit(void)
{
    /* test initial values */
    struct saru_buf ints; // will contain 100 ints
    sb_init(&ints, 100);

    sb_fill(&ints, 0);

    TEST_ASSERT_EQUAL(100, ints.len);
    for (size_t i = 0; i < ints.len; i++)
        TEST_ASSERT_EQUAL(0, *(int *) sb_get(&ints, i)); 

    sb_destroy(&ints);
}

void
test_sb_bufput_get(void)
{
    struct saru_buf str;
    sb_init(&str, 25);

    char c = 'z';
    sb_put(&str, (void *) &c, 2);
    TEST_ASSERT_EQUAL_CHAR('z', *(char *) sb_get(&str, 2));
    
    sb_destroy(&str);
}

