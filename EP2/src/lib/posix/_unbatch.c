#include <lib.h>
#include <unistd.h>
#include<stdio.h>

PUBLIC int unbatch(int pid)
{
    message m;
    m.m1_i1 = pid;
    return(_syscall(MM,UNBATCH,&m));
}