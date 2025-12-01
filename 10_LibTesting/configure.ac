AC_PREREQ([2.69])
AC_INIT([growable-buf], [1.0.0], [https://github.com/skeeto/growable-buf])
AM_INIT_AUTOMAKE([foreign subdir-objects])

LT_INIT([disable-static])
AC_PROG_CC

PKG_CHECK_MODULES([CHECK], [check >= 0.15.0], [], [AC_MSG_ERROR([Check library not found])])
AC_SUBST(CHECK_CFLAGS)
AC_SUBST(CHECK_LIBS)

AC_CONFIG_SRCDIR([src/growable_buf.c])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_FILES([
    Makefile
    include/Makefile
    src/Makefile
    tests/Makefile
])

AC_OUTPUT
