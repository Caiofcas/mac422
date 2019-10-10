#include <lib.h>
#include <unistd.h>

PUBLIC int batch(void)
{
    message m;
    return(_syscall(MM,BATCH,&m));
}