#include <stdio.h>
#include <pwd.h>
#include <curses.h>
#include <timers.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <termcap.h>
#include <termios.h>
#include <time.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

#include <sys/times.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>

#include <minix/ipc.h>
#include <minix/config.h>
#include <minix/type.h>
#include <minix/const.h>

#include "/usr/src/servers/pm/mproc.h"
#include "/usr/src/kernel/proc.h"

/* Funcao que recebe um numero de linhas maximo no qual podem ser
   impressos processos e  imprime:
		PID POS_INICIAL POS_FINAL
   para quantos processos forem possiveis.*/

void print_procs( struct mproc* mproc){
	struct mproc pr;
	int pid,start,end,i,p;

	printf("PID\tSTART\tEND\n");

	/*Percorre a tabela de processos e imprime as informacoes para
	cada processo ate o fim da tabela.*/
	for( p = 0; p < NR_PROCS; p++){
		pr = mproc[p];

		/*Verifica se o processo esta sendo usado*/
		if(!(pr.mp_flags & IN_USE)) continue;
		
		/*Recupera informacoes*/
		pid = pr.mp_pid;
		start = pr.mp_seg[0].mem_phys;
		end = pr.mp_seg[3].mem_phys + pr.mp_seg[3].mem_len;
		
		printf("%d\t%d\t%d\n",pid,start,end);
	}
}

void print_memory(struct pm_mem_info *pmi){
	int h;
	int total_bytes = 0; 
	for(h = 0; h < _NR_HOLES; h++) {
		if(pmi->pmi_holes[h].h_base && pmi->pmi_holes[h].h_len) {
			int bytes;
			bytes = pmi->pmi_holes[h].h_len << CLICK_SHIFT;
			total_bytes += bytes;
		}
	}

	printf("Mem: %dK Free\n",total_bytes/1024);
}


int main(int argc, char** argv){
    static struct mproc mproc[NR_PROCS];
	static struct pm_mem_info pmi;

	int used_memory = 0;

	/*Obtem a tabela de processos*/
	if(getsysinfo(PM_PROC_NR, SI_PROC_TAB, mproc) < 0) {
		fprintf(stderr, "getsysinfo() for SI_PROC_TAB failed.\n");
		exit(1);
	}
	if(getsysinfo(PM_PROC_NR, SI_MEM_ALLOC, &pmi) < 0) {
		fprintf(stderr, "getsysinfo() for SI_MEM_ALLOC failed.\n");
		exit(1);;
	}
	print_procs(mproc);
	print_memory(&pmi);
	return 0;
}