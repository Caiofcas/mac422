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
  int proc_nr;
  register struct proc *rp;

  /* Extract the message parameters and do sanity checking. */
  if(!isokendpt(m_ptr->PR_ENDPT, &proc_nr)) return EINVAL;
  if (iskerneln(proc_nr)) return(EPERM);

  rp = proc_addr(proc_nr);

  if(rp->p_priority == BATCH_Q){
    lock_dequeue(rp);
    rp->p_max_priority = rp->p_priority = BATCH_Q -1;
    if (! rp->p_rts_flags) lock_enqueue(rp);
    return(OK);
  }
  /*Process was not in BATCH_Q*/
  return(EINVAL);
}
/* ######################################################## */