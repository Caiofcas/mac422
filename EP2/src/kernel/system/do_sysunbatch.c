/* ######################################################## */

/* The kernel call implemented in this file:
 *   m_type:    SYS_UNBATCH
 *
 * The parameters for this kernel call are:
 *    m1_i1:    PR_ENDPT        process number to rm from BATCH_Q
 */

#include "../system.h"
#include <minix/type.h>
#include <sys/resource.h>


/*===========================================================================*
 *                                do_sysunbatch                              *
 *===========================================================================*/
PUBLIC int do_sysunbatch(message *m_ptr)
{
/* Remove process from BATCH_Q*/
  int proc_n;
  register struct proc *rp;

  proc_n = m_ptr->m1_i1;  
  if (iskerneln(proc_n)) return(EPERM);

  rp = proc_addr(proc_n);

  if(rp->p_priority == BATCH_Q){
    lock_dequeue(rp);
    rp->p_max_priority = rp->p_priority = BATCH_Q -1;
    if (! rp->p_rts_flags) lock_enqueue(rp);
    return(OK);
  }

  return(EINVAL);
}
/* ######################################################## */