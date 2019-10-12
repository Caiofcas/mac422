#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*Arquivo feito para testar a mudança de prioridade dos processos */
int main(){
    while(1){
        sleep(20);
        printf("Oi");
    }    
    return 0;
}