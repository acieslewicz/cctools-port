#ifndef _FOREIGN_SYS_STAT_H_
#define _FOREIGN_SYS_STAT_H_

#include_next <sys/stat.h>

#ifndef S_IFLNK
#define S_IFLNK 0120000
#endif

#ifndef S_IFSOCK
#define S_IFSOCK 0140000
#endif

#ifndef S_ISUID
#define S_ISUID 0004000 
#endif

#ifndef S_ISGID
#define S_ISGID 0002000
#endif

#ifndef S_ISVTX
#define S_ISVTX 0001000
#endif

#endif /* _FOREIGN_SYS_STAT_H_ */