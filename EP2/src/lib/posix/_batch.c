#include <lib.h>
#include <unistd.h>

PUBLIC int batch(int pid)
{
    message m;
    printf("Funcao int batch(int pid) chamada com argumento : %d\n",pid);
    m.m1_i1 = pid;
    return(_syscall(MM,BATCH,&m));
}