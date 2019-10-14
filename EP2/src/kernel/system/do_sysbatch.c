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
  int proc_nr;
  register struct proc *rp;

  /* Extract the message parameters and do sanity checking. */
  /*if(!isokendpt(m_ptr->PR_ENDPT, &proc_nr)) return EINVAL;
  if (iskerneln(proc_nr)) return(EPERM);*/
  proc_nr = m_ptr->m1_i1;
  kprintf("Chegou em do_sysbatch com %d\n");
  
  rp = proc_addr(proc_nr);
  lock_dequeue(rp);
  rp->p_max_priority = rp->p_priority = BATCH_Q;
  if (! rp->p_rts_flags) lock_enqueue(rp);

  return(OK);
}

/* ######################################################## */