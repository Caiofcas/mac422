#include <lib.h>
#include <unistd.h>

PUBLIC int batch()
{
    message m;
    m.m1_i1 = 45;
    return(_syscall(MM,BATCH,&m));
}