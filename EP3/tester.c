#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
    malloc(100000);
    sleep(40);
    return 0;
}