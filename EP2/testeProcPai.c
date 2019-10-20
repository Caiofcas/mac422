/* Testa se batch e unbatch estão corretamente verificando se o 
   processo que as chamou é o pai do processo alvo. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


pid_t efork(){
    pid_t child_pid;

    child_pid = fork();
    if (child_pid < 0) {
        perror("Forking child has failed");
        exit(1);
    }
    return child_pid;
}

void testa_batch(pid_t alvo){
    pid_t child_pid;

    child_pid = fork();

    if(child_pid == 0) { /*child*/
        printf("Processo nao pai chamou batch\nRetornou: %d\n",batch(alvo));
        return;
    } else { /*parent*/
        printf("Processo pai chamou batch\nRetornou: %d\n",batch(alvo));
        return;
    }

}

int main(int argc, char* argv[]){
    
    pid_t alvo_pid;

    alvo_pid = efork();
    
    if(alvo_pid == 0) { /*child*/
        exit(execve("alvo.out",NULL,NULL));
    } else { /*parent*/
        testa_batch(alvo_pid);
    }

    return 0;
}