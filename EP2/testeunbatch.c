#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	int i,j;
	if (argc < 2)
        exit(1);    /* expecting at least 1 integer parameter to test program */
        
    i = atoi(argv[1]);  /* convert argv[1] to an int */
	unbatch(i);
	return 0;
}
