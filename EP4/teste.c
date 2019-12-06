#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
    printf("%d\n",open_tmp("/root/arquivo_temporario_r","r"));
    sleep(4);
    printf("%d\n",open_tmp("/root/arquivo_temporario_r+","r+"));
    sleep(5);
    printf("%d\n",open_tmp("/root/arquivo_temporario_w","w"));
    sleep(2);
    printf("%d\n",open_tmp("/root/arquivo_temporario_w+","w+"));
    sleep(2);
    printf("%d\n",open_tmp("/root/arquivo_temporario_a","a"));
    sleep(2);
    printf("%d\n",open_tmp("/root/arquivo_temporario_a","a+"));
    sleep(20);
    return 0;
}