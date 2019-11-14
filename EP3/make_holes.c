#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void make_child(){
    void* p;
    int child_pid = fork();
    if (child_pid < 0) {
        perror("Forking child has failed");
        exit(1);
    }

    if(child_pid) {
        p = malloc(2000);
        sleep(10);
        exit(0);
    }
    
    return;
}

int main(int argc, char** argv){
    
    int n_holes = 10,i;
    if(argc > 1) n_holes = atoi(argv[1]);

    for (i = 0; i< n_holes; i++)
        make_child();
    return 0;
}