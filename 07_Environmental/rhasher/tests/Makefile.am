

TESTS = tests/rhasher.test
EXTRA_DIST = $(TESTS)

# Optional: alias `make test` to `make check`
.PHONY: test
test: check

AM_TESTS_ENVIRONMENT = \
  PATH=$(abs_top_builddir)/src:$$PATH; \
  export PATH;
