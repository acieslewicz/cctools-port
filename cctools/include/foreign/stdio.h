/*
 * Cygwin defines __STRICT_ANSI__ with -std=c++0x which
 * disables needed functions and -std=gnu++0x doesn't work
 * work due to weird errors in libstdc++.
 */

#ifdef __CYGWIN__
#pragma push_macro("__STRICT_ANSI__")
#undef __STRICT_ANSI__
#endif /* __CYGWIN__ */

#include_next <stdio.h>

#ifndef O_BINARY
#define O_BINARY 0 /* Non Windows */
#endif

#ifdef __CYGWIN__
#pragma pop_macro("__STRICT_ANSI__")
#endif /* __CYGWIN__ */
