TESTS = run_tests
check_PROGRAMS = run_tests

run_tests_SOURCES = test_main.c test_suite.c test_suite.h
run_tests_CPPFLAGS = -I$(top_srcdir)/include $(CHECK_CFLAGS)
run_tests_LDADD = $(top_builddir)/src/libgrowbuf.la $(CHECK_LIBS)
