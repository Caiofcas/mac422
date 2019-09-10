#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define TRUE 1

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
    char *PATH;
    int COMMANDCODE;
    int EXECSTATUS;

    while (TRUE) {
        printf("shell> ");
        
        /* TODO: verify if 'enter' doesnt duplicate shell string */
        scanf("%[^\n]",input);
        scanf("%c",&temp);
        command = get_input(input); /* 0: nome do programa, 1: path*/
        
        if(strcmp(command[0],"protegepracaramba") == 0)
            COMMANDCODE = 0;
        else if(strcmp(command[0],"liberageral") == 0)
            COMMANDCODE = 1;
        else if(strcmp(command[0],"rode") == 0)
            COMMANDCODE = 2;
        else if(strcmp(command[0],"rodeveja") == 0)
            COMMANDCODE = 3;
            
        child_pid = fork();

        if (child_pid < 0) {
            perror("Forking child has failed");
            exit(1);
        } else if (child_pid == 0) {
            if (COMMANDCODE == 0) exit(chmod(command[1],0000));
            else if (COMMANDCODE == 1) exit(chmod(command[1],0777));
            else if (COMMANDCODE == 2) {
                EXECSTATUS = execve(command[1], command, NULL);
                exit(EXECSTATUS);
            }
            else if (COMMANDCODE == 3) {
                EXECSTATUS = execve(command[1], command, NULL); /* TODO: insert path in printf */
                printf("programa xx retornou com codigo %d", EXECSTATUS);
                exit(EXECSTATUS);
            }
        } else if (COMMANDCODE == 3) {
            waitpid(child_pid, &stat_loc, WUNTRACED);
        }

        free(command);
    }

    return 0;
}