#include <stdio.h>
#include <stdlib.h>

int main(){
    char *str;
    str = malloc(40);
    write_memmap(str);
    printf("%p\n",str);
    printf("%s\n",str);
    return 0;
}