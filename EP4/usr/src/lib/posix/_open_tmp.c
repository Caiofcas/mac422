/*########################################*/
#include <lib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>

PRIVATE map_flag_values(char* str) {
    switch (str[0])
    {
    case 'w':
        if(str[1] == '+')
            return O_RDWR | O_CREAT | O_TRUNC;
        else
            return O_WRONLY | O_CREAT | O_TRUNC;
    case 'r':
        if(str[1] == '+')
            return O_RDWR | O_CREAT;
        else
            return O_RDONLY;
    case 'a':
        if(str[1] == '+')
            return O_RDWR | O_CREAT | O_APPEND;
        else
            return O_APPEND;
    default:
        exit(1);
    }
}

PUBLIC int open_tmp(const char* name, char* mode) {
    va_list argp;
    message m;
    int flags;

    flags = map_flag_values(mode);

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