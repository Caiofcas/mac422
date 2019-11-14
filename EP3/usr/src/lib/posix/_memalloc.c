#include <lib.h>
#include <unistd.h>
#include <stdio.h>

PUBLIC int memalloc(int type)
{
    message m;
    int this_pid;

    this_uid = getuid();

    m.m1_i1 = type;
    m.m1_i2 = this_uid; /*caller uid*/

    return(_syscall(MM,MEMALLOC,&m));
}