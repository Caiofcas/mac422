#include <lib.h>
#include <unistd.h>
#include <stdio.h>

PUBLIC int unbatch(int pid)
{
    message m;
    int this_pid;

    this_pid = getpid();

    m.m1_i1 = pid; /*target process*/
    m.m1_i2 = this_pid; /*caller process*/

    return(_syscall(MM,UNBATCH,&m));
}