AC_PREREQ([2.69])
AC_INIT([guesser], [1.0])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_REQUIRE_VERSION(0.21)
AC_CONFIG_SRCDIR([src/guesser.c])
AC_CONFIG_HEADERS([config.h])
ALL_LINGUAS="ru"

AC_PROG_CC

AC_CHECK_HEADERS([libintl.h locale.h stdlib.h])
AC_CHECK_FUNCS([setlocale])

AC_ARG_ENABLE([doxygen],
    AS_HELP_STRING([--enable-doxygen], [enable building documentation using Doxygen]),
    [enable_doxygen=$enableval],
    [enable_doxygen=no])

AM_CONDITIONAL([BUILD_DOXYGEN], [test "x$enable_doxygen" = "xyes"])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    po/Makefile
    man/Makefile
    Doxyfile
])

AC_OUTPUT
