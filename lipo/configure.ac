AC_INIT([lipo], [1010.6], [t.poechtrager@gmail.com])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

AC_ARG_PROGRAM

AM_CONDITIONAL([ISDARWIN], [false])

isdarwin=no

if test "x$CFLAGS" = "x"; then
  CFLAGS="-O3"
fi

if test "x$build" = "x$host"; then
  CFLAGS="$CFLAGS -isystem /usr/local/include -isystem /usr/pkg/include"
  LDFLAGS="$LDFLAGS -L/usr/local/lib -L/usr/pkg/lib"
fi

CWARNINGS=""
EXTRAFLAGS=""
WARNINGS=""

case $host_os in
  darwin* )
    isdarwin=yes
    AM_CONDITIONAL([ISDARWIN], [true])
  ;;
  cygwin* )
    echo "Cygwin is no longer supported." 1>&2
    exit 1
  ;;
esac

case $host_cpu in
  powerpc)
    EXTRAFLAGS="$EXTRAFLAGS -D__ppc__"
  ;;
  powerpc64*)
    EXTRAFLAGS="$EXTRAFLAGS -D__ppc__ -D__ppc64__"
  ;;
  arm64*|aarch64)
    EXTRAFLAGS="$EXTRAFLAGS -D__arm64__"
  ;;
  arm*)
    EXTRAFLAGS="$EXTRAFLAGS -D__arm__"
  ;;
esac

if test "x$EXTRAFLAGS" != "x"; then
  CFLAGS="$CFLAGS $EXTRAFLAGS"
fi
c
CFLAGS="$CFLAGS -D__private_extern__="

CPP="$CC -E"

# FIXME 'subdir-objects' breaks dependency tracking
AM_INIT_AUTOMAKE([1.10 no-define no-dist-gzip dist-bzip2 tar-ustar subdir-objects no-dependencies])

AC_CONFIG_MACRO_DIR([m4])
AM_MAINTAINER_MODE

AC_PREREQ([2.57])
AC_REVISION([$Revision: 1.37 $])

AC_CONFIG_SRCDIR([APPLE_LICENSE])
LT_PREREQ([2.2.6])
LT_INIT(disable-static)

AC_PROG_INSTALL
AM_PROG_CC_C_O

AC_CHECK_TOOL([HOST_RANLIB], [ranlib], :)
AC_CHECK_TOOL([HOST_AR], [ar], :)

#for libstuff emulated.c
case $target_cpu in
     powerpc)
        AC_DEFINE(EMULATED_HOST_CPU_TYPE, 18, [Emulated CPU type])
        AC_DEFINE(EMULATED_HOST_CPU_SUBTYPE, 100, [Emulated CPU subtype])
    ;;
     powerpc64*)
        AC_DEFINE(EMULATED_HOST_CPU_TYPE, 16777234, [Emulated CPU type])
        AC_DEFINE(EMULATED_HOST_CPU_SUBTYPE, 0, [Emulated CPU subtype])
       ;;
     i?86)
        AC_DEFINE(EMULATED_HOST_CPU_TYPE, 7, [Emulated CPU type])
        AC_DEFINE(EMULATED_HOST_CPU_SUBTYPE, 10, [Emulated CPU subtype])
    ;;
     x86_64|amd64)
        AC_DEFINE(EMULATED_HOST_CPU_TYPE, 16777223, [Emulated CPU type])
        AC_DEFINE(EMULATED_HOST_CPU_SUBTYPE, 3, [Emulated CPU subtype])
    ;;
     arm64*|aarch64)
        AC_DEFINE(EMULATED_HOST_CPU_TYPE, 16777228, [Emulated CPU type])
        AC_DEFINE(EMULATED_HOST_CPU_SUBTYPE, 0, [Emulated CPU subtype])
    ;;
     arm*)
        AC_DEFINE(EMULATED_HOST_CPU_TYPE, 12, [Emulated CPU type])
        AC_DEFINE(EMULATED_HOST_CPU_SUBTYPE, 0, [Emulated CPU subtype])
    ;;
     *)
    AC_MSG_ERROR([Unsupported target $target_cpu])
    ;;
esac

AC_DEFINE(__STDC_LIMIT_MACROS)
AC_DEFINE(__STDC_CONSTANT_MACROS)

# set PROGRAM PREFIX
if test "$target_alias"; then
  AC_SUBST([PROGRAM_PREFIX], ['${target_alias}-'])
fi

AC_CHECK_LIB([pthread],[pthread_create],[PTHREAD_FLAGS=-pthread])
AC_SUBST(PTHREAD_FLAGS)

AC_CHECK_LIB([uuid],[uuid_generate_random],[
  AC_CHECK_HEADERS([uuid/uuid.h], [UUID_LIB=-luuid])], [])
AC_SUBST(UUID_LIB)

AC_CHECK_FUNCS([strmode utimens utimensat])
AC_CHECK_FUNCS([bcopy bcmp bzero index rindex])

### Check how to access struct stat's tv_nsec field.
AC_MSG_CHECKING(for st_mtimespec.tv_nsec in struct stat)
AC_COMPILE_IFELSE(
  [AC_LANG_PROGRAM(
    [[#include <sys/stat.h>]],
    [[
    struct stat st;
    st.st_mtimespec.tv_nsec = 0;
    ]])],
  [AC_DEFINE(HAVE_STAT_ST_MTIMESPEC, 1, [struct stat has st_mtimespec.tv_nsec])
   AC_MSG_RESULT([yes])],
  [AC_MSG_RESULT([no])])

AC_MSG_CHECKING(for st_mtim.tv_nsec in struct stat)
AC_COMPILE_IFELSE(
  [AC_LANG_PROGRAM(
    [[#include <sys/stat.h>]],
    [[
    struct stat st;
    st.st_mtim.tv_nsec = 0;
    ]])],
  [AC_DEFINE(HAVE_STAT_ST_MTIM, 1, [struct stat has st_mtim.tv_nsec])
   AC_MSG_RESULT([yes])],
  [AC_MSG_RESULT([no])])

### Check for log2 in -lm

AC_CHECK_LIB([m], [log2], [
  MATH_LIB="-lm"
])

AC_SUBST(MATH_LIB)

### Check for reallocf in -lc, -lbsd

AC_CHECK_HEADERS([bsd/stdlib.h], [])

AC_CHECK_LIB([c],[reallocf],[
    REALLOCF_LIB=""
    AC_DEFINE(HAVE_REALLOCF, 1)
  ],[
  AC_CHECK_LIB([bsd],[reallocf],[
    REALLOCF_LIB=-lbsd
    AC_DEFINE(HAVE_REALLOCF, 1)
  ],[])
])

AC_SUBST(REALLOCF_LIB)

### Check for clock_gettime

AC_CHECK_FUNC([clock_gettime],[AC_DEFINE(HAVE_CLOCK_GETTIME, 1)])

### Check for write64

AC_CHECK_FUNC([write64],[AC_DEFINE(HAVE_WRITE64, 1)])

### Check for __gcc_personality_v0 in -lgcc (NetBSD needs this)

AC_CHECK_LIB([gcc], [__gcc_personality_v0], [
  GCC_LIB="-lgcc"
])

AC_SUBST(GCC_LIB)

### Check for supported warning options ###

ORIGCFLAGS=$CFLAGS
CFLAGS="$CFLAGS -Werror -Wno-shift-negative-value"
AC_MSG_CHECKING([whether $CC supports -Wno-shift-negative-value])
AC_COMPILE_IFELSE(
  [AC_LANG_SOURCE([[int dummy;]])],
  [WARNINGS="$WARNINGS -Wno-shift-negative-value"
   AC_MSG_RESULT([yes])],
  [AC_MSG_RESULT([no])]
)
CFLAGS=$ORIGCFLAGS

ORIGCFLAGS=$CFLAGS
CFLAGS="$CFLAGS -Werror -Wno-misleading-indentation"
AC_MSG_CHECKING([whether $CC supports -Wno-misleading-indentation])
AC_COMPILE_IFELSE(
  [AC_LANG_SOURCE([[int dummy;]])],
  [WARNINGS="$WARNINGS -Wno-misleading-indentation"
   AC_MSG_RESULT([yes])],
  [AC_MSG_RESULT([no])]
)
CFLAGS=$ORIGCFLAGS

ORIGCFLAGS=$CFLAGS
CFLAGS="$CFLAGS -Werror -Wno-gnu-folding-constant"
AC_MSG_CHECKING([whether $CC supports -Wno-gnu-folding-constant])
AC_COMPILE_IFELSE(
  [AC_LANG_SOURCE([[int dummy;]])],
  [WARNINGS="$WARNINGS -Wno-gnu-folding-constant"
   AC_MSG_RESULT([yes])],
  [AC_MSG_RESULT([no])]
)
CFLAGS=$ORIGCFLAGS

ORIGCFLAGS=$CFLAGS
CFLAGS="$CFLAGS -Werror -Wno-unused-but-set-variable"
AC_MSG_CHECKING([whether $CC supports -Wno-unused-but-set-variable])
AC_COMPILE_IFELSE(
  [AC_LANG_SOURCE([[int dummy;]])],
  [WARNINGS="$WARNINGS -Wno-unused-but-set-variable"
   AC_MSG_RESULT([yes])],
  [AC_MSG_RESULT([no])]
)
CFLAGS=$ORIGCFLAGS

ORIGCFLAGS=$CFLAGS
CFLAGS="$CFLAGS -Werror -Wno-deprecated-non-prototype"
AC_MSG_CHECKING([whether $CC supports -Wno-deprecated-non-prototype])
AC_COMPILE_IFELSE(
  [AC_LANG_SOURCE([[int dummy;]])],
  [WARNINGS="$WARNINGS -Wno-deprecated-non-prototype"
   AC_MSG_RESULT([yes])],
  [AC_MSG_RESULT([no])]
)
CFLAGS=$ORIGCFLAGS

ORIGCFLAGS=$CFLAGS
CFLAGS="$CFLAGS -Werror -Wno-deprecated-declarations"
AC_MSG_CHECKING([whether $CC supports -Wno-deprecated-declarations])
AC_COMPILE_IFELSE(
  [AC_LANG_SOURCE([[int dummy;]])],
  [WARNINGS="$WARNINGS -Wno-deprecated-declarations"
   AC_MSG_RESULT([yes])],
  [AC_MSG_RESULT([no])]
)
CFLAGS=$ORIGCFLAGS

ORIGCFLAGS=$CFLAGS
CFLAGS="$CFLAGS -Werror -Wno-deprecated"
AC_MSG_CHECKING([whether $CC supports -Wno-deprecated])
AC_COMPILE_IFELSE(
  [AC_LANG_SOURCE([[int dummy;]])],
  [WARNINGS="$WARNINGS -Wno-deprecated"
   AC_MSG_RESULT([yes])],
  [AC_MSG_RESULT([no])]
)
CFLAGS=$ORIGCFLAGS

ORIGCFLAGS=$CFLAGS
CFLAGS="$CFLAGS -Werror -Wno-format"
AC_MSG_CHECKING([whether $CC supports -Wno-format])
AC_COMPILE_IFELSE(
  [AC_LANG_SOURCE([[int dummy;]])],
  [WARNINGS="$WARNINGS -Wno-format"
   AC_MSG_RESULT([yes])],
  [AC_MSG_RESULT([no])]
)
CFLAGS=$ORIGCFLAGS

AC_SUBST([WARNINGS], [$WARNINGS])

if test "x$isdarwin" != "xyes"; then
  LDFLAGS=$ORIGLDFLAGS
fi

### Check endianness ###

AC_C_BIGENDIAN([AC_SUBST([ENDIAN_FLAG],[-D__BIG_ENDIAN__=1])],
      [AC_SUBST([ENDIAN_FLAG],[-D__LITTLE_ENDIAN__=1])])


AC_CONFIG_FILES([Makefile libstuff/Makefile libmacho/Makefile])
AC_CONFIG_FILES([misc/Makefile])


AC_OUTPUT
