/* ######################################################## */

#include <lib.h>
#include <unistd.h>

PUBLIC int write_memmap(void)
{
    message m;
    return(_syscall(MM,WMEMMAP,&m));
}
/* ######################################################## */
