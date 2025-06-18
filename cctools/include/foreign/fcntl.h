#include_next <fcntl.h>

#ifndef O_FSYNC
#define O_FSYNC O_SYNC /* Cygwin */
#endif

#ifndef O_BINARY
#define O_BINARY 0 /* Non Windows */
#endif

