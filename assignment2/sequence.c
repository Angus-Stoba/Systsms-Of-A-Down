#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Global values set by instructions
#define MaxCharacters 256
#define MaxArguments 10
#define MaxLines 100

int string_line(char* line, char* command, char** arguments) { // used to convert each line into a string that can be used in execvp()
    // initialisers for position and starting token
    int argc = 0;
    char* token = strtok(line, " \n");

    if (token == NULL) { return 0; } // if stdin is empty

    // initialising command via token and setting first value in arguments to command
    strcpy(command, token); 
    arguments[argc++] = command; 
    
    while ((token = strtok(NULL, " \n")) != NULL && argc < MaxArguments) { // while loop to add subsequent arguments from the command
        arguments[argc++] = token;
    }

    arguments[argc] = NULL; // Adding NULL as the final argument for later use

    return 1;
}

int main() {
    // initialisers
    char line[MaxCharacters];
    char command[MaxCharacters];
    char* arguments[MaxArguments + 1]; // +1 for NULL terminator
    int num_commands = 0;

    while (fgets(line, sizeof(line), stdin) != NULL && num_commands < MaxLines) { // while the input contains some element
        if (string_line(line, command, arguments)) { // if the function runs correctly
            
            pid_t pid = fork(); // fork to create child progresses

            if (pid == -1) { // error
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if (pid == 0) { // Child process
                execvp(command, arguments);
            } else { // Parent process
                int status;
                waitpid(pid, &status, 0);
            }

            num_commands++; // increase tally
        }
    }

    return 0;
}