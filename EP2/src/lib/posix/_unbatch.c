#include <lib.h>
#include <unistd.h>
#include<stdio.h>

PUBLIC int unbatch(int pid)
{
    message m;
    printf("Funcao int unbatch(int pid) chamada com argumento : %d\n",pid);
    m.m1_i1 = pid;
    return(_syscall(MM,UNBATCH,&m));
}