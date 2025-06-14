/*
 * Cygwin defines __STRICT_ANSI__ with -std=c++0x which
 * disables needed functions and -std=gnu++0x doesn't work
 * work due to weird errors in libstdc++.
 */

#ifdef __CYGWIN__
#pragma push_macro("__STRICT_ANSI__")
#undef __STRICT_ANSI__
#endif /* __CYGWIN__ */

#ifdef _WIN32
#define _GNU_SOURCE  // For vasprintf
#endif

#include_next <stdlib.h>

#ifdef __CYGWIN__
#pragma pop_macro("__STRICT_ANSI__")
#endif /* __CYGWIN__ */

#ifdef _WIN32
#include <sys/stat.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif
/*
* Windows realpath implementation
*
* Adapted from: https://github.com/LongDirtyAnimAlf/ld64-msys
* Author: LongDirtyAnimAlf
*/
#ifndef REALPATH_DEFINED
#define REALPATH_DEFINED
static inline char *realpath( const char *__restrict__ name, char *__restrict__ resolved ) {
    char *retname = NULL;

    if( name == NULL ) {
        errno = EINVAL;
        return NULL;
    }
    if (resolved == NULL) {
        retname = (char*)malloc(_MAX_PATH);

        if (retname == NULL) {
            errno = ENOMEM;
            return NULL;
        }
    } else {
        retname = resolved;
    }

    if (_fullpath(retname, name, _MAX_PATH) == NULL) {
        if (resolved == NULL) {
            free(retname);
        }
        errno = ENAMETOOLONG;
        return NULL;
    }

    char *p;
    while ((p = strchr (retname, '\\')) != NULL) {
        *p = '/';
    }  

    return retname;
}
#endif /* REALPATH_DEFINED */

#ifdef __cplusplus
}
#endif

#endif