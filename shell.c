/*
* Artur Magalhaes, 10297734 e Caio Fontes, 10692061
* MAC0422 - Shell
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define TRUE 1
#define RODE "rode"
#define RODEVEJA "rodeveja"
#define LIBERAGERAL "liberageral"
#define PROTEGEPRACARAMBA "protegepracaramba"
#define DISABLED -1

char **parseInput(char *input) {
    /* 
    Receives a string INPUT, which contains the user input, 
    parses it and returns the COMMAND array, which contains 
    the command in the first position, NULL in the last used 
    position, and the arguments passed in the middle positions.
    
    Ex: input = "ls -l -a"
    
    returns: command = ["ls","-l","-a",NULL, ...]
    */
    
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

void rode(char ** cmd) {
    close(STDIN_FILENO);
    exit(execve(cmd[1], cmd, NULL));
}

int main(void) {
    char **command;
    char inputFromCommandLine[30];
    char temp;
    pid_t child_pid;
    int stat_loc;
    int commandCodeFlag;

    while (TRUE) {
        printf("shell> ");
        
        scanf("%[^\n]",inputFromCommandLine);
        scanf("%c",&temp);
        command = parseInput(inputFromCommandLine); /* 0: program name, 1: path*/
        
        commandCodeFlag = DISABLED;

        if(strcmp(command[0], PROTEGEPRACARAMBA) == 0)
            commandCodeFlag = 0;
        else if(strcmp(command[0], LIBERAGERAL) == 0)
            commandCodeFlag = 1;
        else if(strcmp(command[0], RODE) == 0)
            commandCodeFlag = 2;
        else if(strcmp(command[0], RODEVEJA) == 0)
            commandCodeFlag = 3;
            
        if (commandCodeFlag != DISABLED)
            child_pid = fork();

        if (child_pid < 0) {
            perror("Forking child has failed");
            exit(1);
        }
        
        if (child_pid == 0) {
            if      (commandCodeFlag == 0) exit(chmod(command[1], 0000));
            else if (commandCodeFlag == 1) exit(chmod(command[1], 0777));
            else if (commandCodeFlag == 2) rode(command);
            else if (commandCodeFlag == 3) execve(command[1], command, NULL);
        } else {
            if (commandCodeFlag == 3) {
                waitpid(child_pid, &stat_loc, 0);
                printf("\n=> programa '%s' retornou com codigo %d\n", command[1], WEXITSTATUS(stat_loc));
            }
        }

        free(command);
    }

    return 0;
}