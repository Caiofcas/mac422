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

void testa_chamadas(pid_t alvo, int opc){
    pid_t child_pid;

    child_pid = fork();

    if(child_pid == 0) { /*child*/
        printf("Processo nao pai chamou batch\nRetornou: %d\n",batch(alvo));
        if(opc){
            sleep(6);
            printf("Processo nao pai chamou unbatch\nRetornou: %d\n",unbatch(alvo)); 
        }
        exit(0);
    } else { /*parent*/
        printf("Processo pai chamou batch\nRetornou: %d\n",batch(alvo));
        if(opc){
            sleep(6);
            printf("Processo pai chamou unbatch\nRetornou: %d\n",unbatch(alvo)); 
        }
        return;
    }

}

int main(int argc, char* argv[]){
    
    int opc = 0;
    pid_t alvo_pid;

    if(argc > 1) opc = atoi(argv[1]);

    alvo_pid = efork();
    
    if(alvo_pid == 0) { /*child*/
        exit(execve("alvo.out",NULL,NULL));
    } else { /*parent*/
        testa_chamadas(alvo_pid,opc);
    }

    return 0;
}