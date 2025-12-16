lib_LTLIBRARIES = libslot.la
AM_CFLAGS=-D'LOCALE_PATH="$(localedir)"'

libslot_la_SOURCES = \
    slot_lib.c \
    slot_lib.h

libslot_la_LDFLAGS = -version-info 1:0:0
libslot_la_LIBADD = $(INTLLIBS)
libslot_la_CPPFLAGS = -I$(top_srcdir)/src -DLOCALEDIR=\"$(localedir)\"

bin_PROGRAMS = slot_machine
slot_machine_SOURCES = slot_machine.c
slot_machine_LDADD = libslot.la $(INTLLIBS)
slot_machine_CPPFLAGS = -I$(top_srcdir)/src
