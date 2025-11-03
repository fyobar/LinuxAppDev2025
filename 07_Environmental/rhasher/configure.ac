AC_INIT([rhasher], [1.0], [])
AM_INIT_AUTOMAKE([foreign -Wall])
AC_CONFIG_SRCDIR([src/rhasher.c])
AC_CONFIG_HEADERS([config.h])

AC_PROG_CC

AC_CHECK_HEADER(
    [rhash.h],
    [],
    [AC_MSG_ERROR([rhash.h not found. Please install librhash-dev.])])
    
AC_CHECK_LIB(
    [rhash],
    [rhash_library_init],
    [RHASH_LIBS="-lrhash"],
    [AC_MSG_ERROR([librhash not found or unusable.])])
    
AC_SUBST([RHASH_LIBS])


AC_ARG_ENABLE(
    [readline],
    AS_HELP_STRING([--enable-readline], [Enable GNU readline support]),
    [enable_readline=$enableval],
    [enable_readline=no])

if test "x$enable_readline" = "xyes"; then
    AC_CHECK_LIB(
        [readline],
        [readline],
        [AC_DEFINE([READLINE_ENABLED], [1], [Use GNU readline])
         READLINE_LIBS="-lreadline"],
        [AC_MSG_WARN([readline library not found; building without readline])
         AC_DEFINE([READLINE_ENABLED], [0], [Do not use readline])
         READLINE_LIBS=""])
else
    AC_DEFINE([READLINE_ENABLED], [0], [Do not use readline])
    READLINE_LIBS=""
fi

AC_SUBST([READLINE_LIBS])


AC_CONFIG_FILES([
    Makefile
    src/Makefile
])

AC_OUTPUT
