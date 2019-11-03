#include <stdio.h>
#include <stdlib.h>

int main(){
    char *name;
    name = "Mensagem de Teste";

    printf("1 : %p %s\n",name,name);
    write_memmap(name);
    printf("3 : %p %s\n",name,name);
    return 0;
}