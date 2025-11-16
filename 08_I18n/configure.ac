AC_PREREQ([2.69])
AC_INIT([guesser], [1.0])
AM_INIT_AUTOMAKE([foreign])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_REQUIRE_VERSION(0.21)
AC_CONFIG_SRCDIR([src/guesser.c])
AC_CONFIG_HEADERS([config.h])
ALL_LINGUAS="ru"

AC_PROG_CC

AC_CHECK_HEADERS([libintl.h locale.h stdlib.h])
AC_CHECK_FUNCS([setlocale])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    po/Makefile.in
])

AC_OUTPUT
