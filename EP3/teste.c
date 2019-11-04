#include <stdio.h>
#include <stdlib.h>

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