#include <check.h>
#include "test_suite.h"


int main(void) {
    int failed_number;
    Suite *suite;
    SRunner *runner;

    suite = growbuf_suite();
    runner = srunner_create(suite);

    srunner_run_all(runner, CK_VERBOSE);
    failed_number = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (failed_number == 0) ? 0 : 1;
}
