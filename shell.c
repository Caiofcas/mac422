#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

char **get_input(char *input) {
    /*Receives a string INPUT, which contains the user input, 
    parses it and returns the COMMAND array, which contains 
    the command in the first position, NULL in the last used 
    position, and the arguments passed in the middle positions.
    
    Ex: input = "ls -l -a"
    
    returns: command = ["ls","-l","-a",NULL, ...]*/
    
    char **command = malloc(8 * sizeof(char *));
    char *separator = " ";
    char *parsed;
    int index = 0;

    parsed = strtok(input, separator);
    while (parsed != NULL) {
        command[index] = parsed;
        index++;

        parsed = strtok(NULL, separator);
    }

    command[index] = NULL;
    return command;
}

int main() {
    char **command;
    char input[30];
    char temp;
    pid_t child_pid;
    int stat_loc;

    while (1) {
        /*Reads user input*/
        printf("shell> ");
     
        scanf("%[^\n]",input);
        scanf("%c",&temp);
        /*Parses it*/
        command = get_input(input);

        /*Calls fork*/
        child_pid = fork();

        /*Error handling*/
        if(child_pid < 0){
            perror("fork failed");
            exit(1);
        } else if (child_pid == 0) {
            /*If child, call execvp on input*/
            /* Never returns if the call is successful */ 

            /*Verifca se é um dos nossos comandos*/
            if(strcmp(command[0],"protegepracaramba") == 0)
                chmod(command[1],0000);
            
            else if(strcmp(command[0],"liberageral") == 0)
                chmod(command[1],0777);

            else if(strcmp(command[0],"rode") == 0)
                printf("rode chamado\n");

            else if(strcmp(command[0],"rodeveja") == 0)
                printf("rodeveja chamado\n");

            /*Se não for reconhecido, tenta executar*/
            else if(execvp(command[0], command) < 0) {
                perror(command[0]);
                exit(1);
            }
        } else {
            /*If parent, wait for end of child process*/
            waitpid(child_pid, &stat_loc, WUNTRACED);
        }

        free(command);
    }

    return 0;
}