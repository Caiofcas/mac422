
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


#include "../../servers/pm/mproc.h"
#include "../../kernel/const.h"
#include "../../kernel/proc.h"

#define  TC_BUFFER  1024        /* Size of termcap(3) buffer    */
#define  TC_STRINGS  200        /* Enough room for cm,cl,so,se  */

char *Tclr_all;

/* Funcao que determina quantas linhas podem ser impressas
   e retorna esse valor em ROWS */
void init(int *rows)
{
	
	char  *term;
	static char   buffer[TC_BUFFER], strings[TC_STRINGS];
	char *s = strings, *v;

	*rows = 0;

	/* Checagem de erros*/
	if(!(term = getenv("TERM"))) {
		fprintf(stderr, "No TERM set\n");
		exit(1);
	}

	if ( tgetent( buffer, term ) != 1 ) {
		fprintf(stderr, "tgetent failed for term %s\n", term);
		exit(1);
	}

	if ( (Tclr_all = tgetstr( "cl", &s )) == NULL )
		Tclr_all = "\f";

	/*Daqui obtemos o numero de linhas*/
	if((v = tgetstr ("li", &s)) != NULL)
		sscanf(v, "%d", rows);

	/*Define o valor padrao como 24 linhas*/
	if(*rows < 1) *rows = 24;
	
	if(!initscr()) {
		fprintf(stderr, "initscr() failed\n");
		exit(1);
	}
	cbreak();
	nl();
}

/* Funcao que recebe um numero de linhas maximo no qual podem ser
   impressos processos e  imprime:
		PID POS_INICIAL POS_FINAL
   para quantos processos forem possiveis.*/
void showmap(int r)
{
	struct winsize winsize;
	static struct mproc mproc[NR_PROCS];
	struct mproc pr;
	int p, lines = 1;

	if(ioctl(STDIN_FILENO, TIOCGWINSZ, &winsize) != 0) {
		perror("TIOCGWINSZ");
		fprintf(stderr, "TIOCGWINSZ failed\n");
		exit(1);
	}

	if(getsysinfo(PM_PROC_NR, SI_PROC_TAB, mproc) < 0) {
		fprintf(stderr, "getsysinfo() for SI_PROC_TAB failed.\n");
		exit(1);
	}

	printf("%s", Tclr_all);

	if(winsize.ws_row > 0) r = winsize.ws_row;

	/*Percorre a tabela de processos e imprime as informacoes para
	cada processo ate o fim da tabela ou acabar o numero de linhas.*/

	printf("PID\tSTART\tEND\n");
	for( p = 0; p < NR_PROCS && lines < r; p++){
		pr = mproc[p];
		printf("%d\t",pr.mp_pid);
	}
}


int main(int argc, char** argv){
    
	int r;

	init(&r);

	showmap(r);

    return 0;
}