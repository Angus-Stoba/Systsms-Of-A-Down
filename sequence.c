#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Global values set by instructions
#define MaxCharacters 256
#define MaxArguments 10
#define MaxLines 100

int parse_command(char *line, char *command, char **arguments) {
    int argc = 0; // active tally of the number of args in the line
    char *token = strtok(line, " \n"); // initialising first token

    if (token == NULL) { // when stdin is empty
        return 0;
    }

    strcpy(command, token); // initialising the first token as command
    arguments[argc++] = command; // making the first arg the command
    
    while ((token = strtok(NULL, " \n")) != NULL && argc < MaxArguments) { //
        arguments[argc++] = token;
    }

    arguments[argc] = NULL; // Null-terminate the argument list

    return 1; // Command parsed successfully
}

int main() {
    char line[MaxCharacters];
    char command[MaxCharacters];
    char *arguments[MaxArguments + 1]; // +1 for NULL terminator
    int num_commands = 0;

    while (fgets(line, sizeof(line), stdin) != NULL && num_commands < MaxLines) {
        if (parse_command(line, command, arguments)) {
            
            pid_t pid = fork();

            if (pid == 0) { // Child process
                execvp(command, arguments);
            } else { // Parent process
                int status;
                waitpid(pid, &status, 0);

                if (WIFEXITED(status)) {
                    printf("Command '%s' exited with status %d\n", command, WEXITSTATUS(status));
                } else {
                    printf("Command '%s' terminated abnormally\n", command);
                }
            }

            num_commands++;
        }
    }

    return 0;
}