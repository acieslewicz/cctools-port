#ifndef _FOREIGN_PWD_H_
#define _FOREIGN_PWD_H_

#ifdef _WIN32

struct passwd {
    char *pw_name;
    char *pw_dir;
    char *pw_hsell;
    int pw_uid;
    int pw_gid;
};

// Stub implementation that always returns null. Appears to be used
// some release canditate stuff which isn't really needed
static inline struct passwd *getpwnam(const char *name) {
    (void)name;
    return NULL;
}

#else
#include_next <pwd.h>
#endif

#endif /* _FOREIGN_PWD_H_ */