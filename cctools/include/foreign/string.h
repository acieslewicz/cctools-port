#ifndef _STRING_H_FOREIGN_
#define _STRING_H_FOREIGN_

#ifdef _WIN32
#include_next <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef bzero
#define bzero(ptr, size) memset((ptr), 0, (size))
#endif

#ifdef __cplusplus
}
#endif

#else
#include_next <string.h>
#endif

#endif /* _STRING_H_FOREIGN_ */