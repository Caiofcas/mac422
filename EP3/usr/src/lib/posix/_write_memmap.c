/* ######################################################## */

#include <lib.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

PUBLIC int write_memmap(FILE * filename)
{
    message m;
    m.m1_p1 = (char *) filename;
    return(_syscall(MM,WMEMMAP,&m));
}
/* ######################################################## */
