#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROTEGE 0
#define LIBERA 1
#define RODE 2
#define RODEVEJA 3

char **get_input(char *input) {
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
    int cmd;

    while (1) {
        /*reads user input*/
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
            /* Never returns if the call is successful */
            /*If child, call execvp on input*/
            if(execvp(command[0], command) < 0) {
                perror(command[0]);
                exit(1);
            }
        } else {
            /*If parent wait for end of child process*/
            waitpid(child_pid, &stat_loc, WUNTRACED);
        }

        free(command);
    }

    return 0;
}