SUBDIRS = include src tests
AUTOMAKE_OPTIONS = foreign subdir-objects parallel-tests
TESTS_ENVIRONMENT = CK_VERBOSITY=$(CK_VERBOSITY)
AM_CFLAGS = -g -O0 -fprofile-arcs -ftest-coverage
AM_LDFLAGS = -fprofile-arcs -ftest-coverage


maintainer-clean-local:
	rm -rf configure config.* autom4te.cache \
	Makefile Makefile.in aclocal.m4 ltmain.sh m4 \
	compile install-sh missing depcomp stamp-h1 *~ \
	test-driver libtool \
	src/Makefile src/Makefile.in src/.deps src/.libs src/*.lo src/*.la \
	include/Makefile include/Makefile.in \
	tests/Makefile tests/Makefile.in tests/.deps src/.libs tests/run_tests* /tests/*.log tests/test-suite.log

