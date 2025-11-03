SUBDIRS = src
TESTS = tests/test.sh
EXTRA_DIST = $(TESTS)

.PHONY: test
test: check

maintainer-clean-local:
	rm -rf configure config.* autom4te.cache \
	Makefile Makefile.in aclocal.m4 ltmain.sh test-suite.log \
	compile install-sh missing test-driver depcomp stamp-h1 *~ \
	src/.deps src/.deps src/rhasher src/rhasher.o src/Makefile src/Makefile.in \
	tests/test.sh.log tests/test.sh.trs

