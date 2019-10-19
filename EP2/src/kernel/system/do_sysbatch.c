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

  /* Extract the message parameters and do sanity checking. */
  /*if(!isokendpt(m_ptr->PR_ENDPT, &proc_nr)) return EINVAL;*/
  
  proc_n = m_ptr->m1_i1;
  
  if (iskerneln(proc_n)) return(EPERM);

  kprintf("Chegou em do_sysbatch com %d\n",proc_n);
  
  rp = proc_addr(proc_n);
  kprintf("do_sysbatch : endereco do processo : %p\n",rp);
  
  lock_dequeue(rp);
  kprintf("Passou Dequeue\nproc_n: %d\nrp : %p\n",proc_n,rp);
  rp->p_priority = BATCH_Q;
  if (! rp->p_rts_flags){
    lock_enqueue(rp);
    kprintf("Passou Enqueue\nproc_n: %d\nrp : %p\n",proc_n,rp);
  } 

  return(OK);
}

/* ######################################################## */