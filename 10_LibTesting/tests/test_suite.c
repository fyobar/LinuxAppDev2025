#include <check.h>
#include <stdint.h>
#include "growable_buf.h"


// init tests
START_TEST(test_init_and_free)
{
    float *buf = NULL;

    ck_assert_uint_eq(buf_capacity(buf), 0);
    ck_assert_uint_eq(buf_size(buf), 0);

    buf_push(buf, 1.3f);
    ck_assert_uint_eq(buf_size(buf), 1);
    ck_assert_float_eq(buf[0], 1.3f);

    buf_clear(buf);
    ck_assert_uint_eq(buf_size(buf), 0);
    ck_assert_ptr_nonnull(buf);

    buf_free(buf);
    ck_assert_ptr_null(buf);

    buf_clear(buf);
    ck_assert_uint_eq(buf_size(buf), 0);
    ck_assert_ptr_null(buf);
}
END_TEST

// push/pop tests
START_TEST(test_push_pop)
{
    long *buf = NULL;

    for (int i = 0; i < 10000; i++)
        buf_push(buf, i);

    ck_assert_uint_eq(buf_size(buf), 10000);

    int match = 0;
    for (int i = 0; i < (int)buf_size(buf); i++)
        match += buf[i] == i;
    ck_assert_int_eq(match, 10000);

    buf_free(buf);

    float *fbuf = NULL;
    buf_push(fbuf, 1.1);
    buf_push(fbuf, 1.2);
    buf_push(fbuf, 1.3);
    buf_push(fbuf, 1.4);

    ck_assert_uint_eq(buf_size(fbuf), 4);
    ck_assert_float_eq(buf_pop(fbuf), 1.4f);
    buf_trunc(fbuf, 3);
    ck_assert_uint_eq(buf_size(fbuf), 3);
    ck_assert_float_eq(buf_pop(fbuf), 1.3f);
    ck_assert_float_eq(buf_pop(fbuf), 1.2f);
    ck_assert_float_eq(buf_pop(fbuf), 1.1f);
    ck_assert_uint_eq(buf_size(fbuf), 0);
    buf_free(fbuf);
}
END_TEST

// grow/trunc tests
START_TEST(test_grow_trunc)
{
    int *buf = NULL;

    buf_grow(buf, 1000);
    ck_assert_uint_eq(buf_capacity(buf), 1000);
    ck_assert_uint_eq(buf_size(buf), 0);

    buf_trunc(buf, 100);
    ck_assert_uint_eq(buf_capacity(buf), 100);

    buf_free(buf);
}
END_TEST


Suite *growbuf_suite(void) {
    Suite *suite;
    TCase *tc_init, *tc_push, *tc_grow;

    suite = suite_create("growbuf");

    tc_init = tcase_create("init");
    tcase_add_test(tc_init, test_init_and_free);
    suite_add_tcase(suite, tc_init);

    tc_push = tcase_create("push/pop");
    tcase_add_test(tc_push, test_push_pop);
    suite_add_tcase(suite, tc_push);

    tc_grow = tcase_create("grow/trunc");
    tcase_add_test(tc_grow, test_grow_trunc);
    suite_add_tcase(suite, tc_grow);

    return suite;
}
