AC_INIT([slot-machine], [1.0])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_SRCDIR([src/slot_machine.c])
AC_CONFIG_HEADERS([config.h])

AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_REQUIRE_VERSION(0.21)

AC_PROG_CC
LT_INIT

AC_CHECK_HEADERS([locale.h libintl.h wchar.h])
AC_CHECK_FUNCS([setlocale])

PKG_CHECK_MODULES([CHECK], [check >= 0.15.0], [], [AC_MSG_ERROR([Check library not found])])
AC_SUBST(CHECK_CFLAGS)
AC_SUBST(CHECK_LIBS)

AC_ARG_ENABLE([docs],
  AS_HELP_STRING(
    [--enable-docs@<:@=yes|no|auto@:>@],
    [Generate Doxygen documentation (default: auto)]
  ),
  [enable_docs=$enableval],
  [enable_docs=auto]
)

AC_CHECK_PROG([DOXYGEN], [doxygen], [doxygen], [no])

AS_IF(
  [test "$enable_docs" = auto],
  [test "$DOXYGEN" != no && enable_docs=yes || enable_docs=no]
)

AS_IF(
  [test "$enable_docs" = yes && test "$DOXYGEN" = no],
  [AC_MSG_WARN([Doxygen not found; documentation will not be generated])]
)

AM_CONDITIONAL([ENABLE_DOCS], [test "$enable_docs" = yes])

AC_SUBST([DOXYGEN])
AC_SUBST([LIBINTL])


AC_CONFIG_FILES([ 
  Makefile
  src/Makefile
  po/Makefile
  tests/Makefile
  man/Makefile
  docs/Makefile
  docs/Doxyfile
  docs/mainpage.dox
])

AC_OUTPUT
