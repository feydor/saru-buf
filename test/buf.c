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
void test_sb_memcpy(void);
void test_sb_strcpy(void);

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_sb_create);
    RUN_TEST(test_sb_put_get);
    RUN_TEST(test_sb_memcpy);
    RUN_TEST(test_sb_strcpy);
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
    SB_CREATE(ints, 100);
    TEST_ASSERT_EQUAL(100, ints->len);
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

    sb_destroy(sb);
}

void test_sb_strcpy(void)
{
    char *str = "hello world";
    size_t strlen = 12;
    SB_CREATE(sb, strlen);

    sb_strcpy(sb, str, strlen);
    
    TEST_ASSERT_EQUAL_CHAR('h', *(char *) sb_get(sb, 0));
    TEST_ASSERT_EQUAL_CHAR('\0', *(char *) sb_get(sb, 11));

    sb_destroy(sb);
}

void test_sb_memcpy(void)
{
   int ints[] = {1, 2, 3, 4, 5};
   size_t size = 5;
   SB_CREATE(sb, size);

   /* copy the first four elements from ints into sb */
   sb_memcpy(sb, (void *)ints, 4, sizeof(int));

   TEST_ASSERT_EQUAL(1, *(int *)sb_get(sb, 0));
   TEST_ASSERT_EQUAL(2, *(int *)sb_get(sb, 1));
   TEST_ASSERT_EQUAL(3, *(int *)sb_get(sb, 2));
   TEST_ASSERT_EQUAL(4, *(int *)sb_get(sb, 3));

   sb_destroy(sb);
}
