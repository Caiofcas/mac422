/* ######################################################## */
#include "syslib.h"
#include "stdio.h"

/*===========================================================================*
 *                                sys_batch                                  *
 *===========================================================================*/
PUBLIC int sys_batch(int proc_n)
{
  message m;
  m.m1_i1 = proc_n;
  return(_taskcall(SYSTASK, SYS_BATCH, &m));
}
/* ######################################################## */