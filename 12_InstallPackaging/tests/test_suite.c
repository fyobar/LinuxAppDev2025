#include <check.h>
#include "slot_lib.h"


START_TEST(test_spin_reel_range)
{
    for (int i = 0; i < 100; i++) {
        int val = spin_reel();
        ck_assert_int_ge(val, 0);
        ck_assert_int_lt(val, NUM_ITEMS);
    }
}
END_TEST

Suite* slot_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("SlotMachine");

    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_spin_reel_range);
    suite_add_tcase(s, tc_core);

    return s;
}
