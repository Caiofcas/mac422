/* ######################################################## */
#include "syslib.h"
#include "stdio.h"

/*===========================================================================*
 *                                sys_unbatch                                *
 *===========================================================================*/
PUBLIC int sys_unbatch(int proc)
{
  message m;
  printf("sys_unbatch called : %d\n",proc);
  
  m.m1_i1 = proc;
  return(_taskcall(SYSTASK, SYS_UNBATCH, &m));
}
/* ######################################################## */