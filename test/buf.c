/* test/buf.c */
#include "saru-buf.h"
#include <stdio.h>
#include <stdlib.h> /* for malloc */
#include <unity.h>

/* test prototypes */
void setUp(void);
void tearDown(void);
void test_saru_bufinit(void);
void test_saru_bufput_get(void);

int
main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_saru_bufinit);
    RUN_TEST(test_saru_bufput_get);
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
test_saru_bufinit(void)
{
    /* test initial values */
    struct saru_buf ints; // will contain 100 ints
    struct saru_buf *ip = &ints;
    saru_initbuf(ip, 100, sizeof(int));
    // ints = saru_createbuf(100);

    TEST_ASSERT_EACH_EQUAL_INT(0, (int *)ip->buf, ip->len);
    TEST_ASSERT_EQUAL(100, ip->len);


    /* with saru_foreach macro*/
    /*
    saru_foreach(void *elem,, ints) {
        TEST_ASSERT_EQUAL(0, *(int *)elem);
    }
    */

    saru_destroybuf(ip);
}

void
test_saru_bufput_get(void)
{
    struct saru_buf str;
    saru_initbuf(&str, 25, sizeof(char));

    char c = 'z';
    saru_bufput(&str, (void *) &c, 0);
    TEST_ASSERT_EQUAL_CHAR('z', *(char *) saru_bufget(&str, 0));
    
    saru_destroybuf(&str);
}
