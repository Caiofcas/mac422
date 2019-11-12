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
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

#include <sys/ioc_tty.h>
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


int main(int argc, char** argv){
    static struct mproc mproc[NR_PROCS];
	struct mproc pr;
	int pid,start,end,i,p;

	/*Obtem a tabela de processos*/
	if(getsysinfo(PM_PROC_NR, SI_PROC_TAB, mproc) < 0) {
		fprintf(stderr, "getsysinfo() for SI_PROC_TAB failed.\n");
		exit(1);
	}

	printf("PID\tSTART\tEND\n");

	/*Percorre a tabela de processos e imprime as informacoes para
	cada processo ate o fim da tabela.*/
	for( p = 0; p < NR_PROCS; p++){
		pr = mproc[p];

		/*Verifica se o processo esta sendo usado*/
		if(!(pr.mp_flags & IN_USE)) continue;
		
		/*Recupera informacoes*/
		pid = pr.mp_pid;
		end = start = pr.mp_seg[0].mem_phys;
		for(i =0;i<3;i++) end+= pr.mp_seg[i].mem_len;
		
		printf("%d\t%d\t%d\n",pid,start,end);
	}

	return 0;
}