#include <lib.h>
#include <unistd.h>

PUBLIC int batch(int pid)
{
    message m;
    m.m1_i1 = pid;
    return(_syscall(MM,BATCH,&m));
}