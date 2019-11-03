/* ######################################################## */

#include <lib.h>
#include <unistd.h>
#include <stdlib.h>

PUBLIC int write_memmap(char* name)
{
    message m;
    m.m1_p1 = name;
    return(_syscall(MM,WMEMMAP,&m));
}
/* ######################################################## */
