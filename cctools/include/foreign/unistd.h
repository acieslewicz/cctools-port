#include_next <unistd.h>

#ifndef L_SET
#define L_SET SEEK_SET /* Cygwin */
#endif

#ifdef _WIN32
#include <io.h>
#include <errno.h>
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif
/*
* Windows readlink implementation
*
* Taken from: https://github.com/LongDirtyAnimAlf/ld64-msys
* Author: LongDirtyAnimAlf
*/
#ifndef READLINK_DEFINED
#define READLINK_DEFINED
static inline int readlink (const char *path, char *buf, size_t bufsize)
{
  struct _stat statbuf;
  /* In general we should use lstat() here, not stat().  But on platforms
     without symbolic links lstat() - if it exists - would be equivalent to
     stat(), therefore we can use stat().  This saves us a configure check.  */
  if (_stat (path, &statbuf) >= 0)
    errno = EINVAL;
  return -1;
}
#endif /* READLINK_DEFINED */

/*
* Windows pread implementation
*
* Taken from: https://github.com/LongDirtyAnimAlf/ld64-msys
* Author: LongDirtyAnimAlf
*/
#ifndef PREAD_DEFINED
#define PREAD_DEFINED
static inline ssize_t pread(int fd, void *buf, size_t count, long long offset)
{
	OVERLAPPED o;
	HANDLE fh = (HANDLE)_get_osfhandle(fd);
	DWORD bytes;
	BOOL ret;

	if (fh == INVALID_HANDLE_VALUE) {
		errno = EBADF;
		return -1;
	}

  memset(&o, 0, sizeof(o));
  o.Offset = (DWORD) offset;
  o.OffsetHigh = (DWORD)(offset>>32);

	ret = ReadFile(fh, buf, (DWORD)count, &bytes, &o);
	if (!ret) {
    int err = (int)GetLastError();
    if (err == ERROR_HANDLE_EOF)
      return 0;
    else
      // throw makeOsException(GetLastError(), "pread");
	    errno = EIO;
	    return -1;
	}
    else
  	  return (ssize_t)bytes;
}
#endif /* PREAD_DEFINED */

#ifdef __cplusplus
}
#endif

#endif /* _WIN32 */
