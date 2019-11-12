#include <stdio.h>
#include <stdlib.h>

void init(int *rows)
{
	char  *term;
	static char   buffer[TC_BUFFER], strings[TC_STRINGS];
	char *s = strings, *v;

	*rows = 0;

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

	if((v = tgetstr ("li", &s)) != NULL)
		sscanf(v, "%d", rows);
	if(*rows < 1) *rows = 24;
	if(!initscr()) {
		fprintf(stderr, "initscr() failed\n");
		exit(1);
	}
	cbreak();
	nl();
}

int main(int argc, char** argv){
    FILE* fp;
    
    fp = fopen(argv[1],"w+");
    if(fp == NULL){
        printf("Arquivo não foi aberto\n");
        return 1;
    }

    printf("1 : %p \n",fp);
    write_memmap(fp);
    printf("3 : %p\n",fp);
    return 0;
}