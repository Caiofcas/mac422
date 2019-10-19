/* ######################################################## */

/* The kernel call implemented in this file:
 *   m_type:    SYS_BATCH
 *
 * The parameters for this kernel call are:
 *    m1_i1:    PR_ENDPT        process number to add to BATCH_Q
 */

#include "../system.h"
#include <minix/type.h>
#include <sys/resource.h>

/*===========================================================================*
 *                                do_sysbatch                                *
 *===========================================================================*/
PUBLIC int do_sysbatch(message *m_ptr)
{
/* Add process to BATCH_Q*/
  int proc_n;
  register struct proc *rp;
  
  proc_n = m_ptr->m1_i1;  
  if (iskerneln(proc_n)) return(EPERM);
  rp = proc_addr(proc_n);
  
  lock_dequeue(rp);
  rp->p_priority = BATCH_Q;
  if (! rp->p_rts_flags){   lock_enqueue(rp);} 

  return(OK);
}

/* ######################################################## */