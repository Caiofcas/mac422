#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
    int type = 0;

    if(argc > 1) type = atoi(argv[1]);

    return memalloc(type);
}