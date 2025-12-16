check_PROGRAMS = test_slot
test_slot_SOURCES = test_main.c test_suite.c

test_slot_CPPFLAGS = \
    -I$(top_builddir)/src \
    -I$(top_srcdir)/src 
 
test_slot_LDADD = ../src/libslot.la \
                   -lcheck -lm -lpthread

TESTS = test_slot
