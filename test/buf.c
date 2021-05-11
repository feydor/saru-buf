/* test/buf.c */
#include "saru-buf.h"
#include <stdio.h> /* for printf */
#include <stdlib.h> /* for malloc */
#include <string.h> /* for memset */
#include <unity.h>

/* test prototypes */
void setUp(void);
void tearDown(void);
void test_sb_create(void);
void test_sb_put_get(void);

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_sb_create);
    RUN_TEST(test_sb_put_get);
}

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test_sb_create(void)
{
    /* test initial values */
    struct saru_buf *ints; // will contain 100 ints
    ints = sb_create(100);

    sb_fill(ints, 0);

    TEST_ASSERT_EQUAL(100, ints->len);
    for (size_t i = 0; i < ints->len; i++)
        TEST_ASSERT_EQUAL(0, *(int *) sb_get(ints, i)); 

    sb_destroy(ints);
}

void test_sb_put_get(void)
{

    char str[] = "hello";
    
    SB_CREATE(sb, 6 * sizeof(char));
    for (size_t i = 0; i < sizeof(str) / sizeof(str[0]); i++)
        sb_put(sb, (void *) &str[i], i);

    TEST_ASSERT_EQUAL_CHAR('h', *(char *) sb_get(sb, 0));
    TEST_ASSERT_EQUAL_CHAR('e', *(char *) sb_get(sb, 1));
    TEST_ASSERT_EQUAL_CHAR('l', *(char *) sb_get(sb, 2));
    TEST_ASSERT_EQUAL_CHAR('l', *(char *) sb_get(sb, 3));
    TEST_ASSERT_EQUAL_CHAR('o', *(char *) sb_get(sb, 4));
    TEST_ASSERT_EQUAL_CHAR('\0', *(char *) sb_get(sb, 5));

    for (size_t i = 0; i < sb->len * sizeof(char); i++)
        printf("%c ", *(char *) sb_get(sb, i));

    sb_destroy(sb);
}
