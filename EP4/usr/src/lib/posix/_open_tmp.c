/*########################################*/
#include <lib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>


PUBLIC int open_tmp(const char* path, int flags) {
    va_list argp;
    message m;

    va_start(argp, flags);
    if (flags & O_CREAT) {
        m.m1_i1 = strlen(name) + 1;
        m.m1_i2 = flags;
        m.m1_i3 = va_arg(argp, _mnx_Mode_t);
        m.m1_p1 = (char *) name;
    } else {
        _loadname(name, &m);
        m.m3_i2 = flags;
    }
    va_end(argp);
    return(_syscall(FS,OPEN_TMP,&m));
}
/*########################################*/