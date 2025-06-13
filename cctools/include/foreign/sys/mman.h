#ifndef _SYS_MMAN_H_FOREIGN_
#define _SYS_MMAN_H_FOREIGN_

#ifdef _WIN32
#include "../../../mman/mman-win32.h"
#else
#include_next <sys/mman.h>
#endif

#endif /* _SYS_MMAN_H_FOREIGN_ */