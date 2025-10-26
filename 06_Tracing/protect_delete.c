#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <errno.h>

typedef int (*orig_unlink_f_type)(const char *pathname);
typedef int (*orig_remove_f_type)(const char *pathname);

int unlink(const char *pathname) {
    static orig_unlink_f_type orig_unlink = NULL;

    if (!orig_unlink)
        orig_unlink = (orig_unlink_f_type)dlsym(RTLD_NEXT, "unlink");

    if (strstr(pathname, "PROTECT")) {
        fprintf(stderr, "[protect_delete.so] Prevented deletion of '%s'\n", pathname);
        errno = 0;
        return 0;
    }

    return orig_unlink(pathname);
}

int remove(const char *pathname) {
    static orig_remove_f_type orig_remove = NULL;

    if (!orig_remove)
        orig_remove = (orig_remove_f_type)dlsym(RTLD_NEXT, "remove");

    if (strstr(pathname, "PROTECT")) {
        fprintf(stderr, "[protect_delete.so] Prevented deletion of '%s'\n", pathname);
        errno = 0;
        return 0;
    }

    return orig_remove(pathname);
}
