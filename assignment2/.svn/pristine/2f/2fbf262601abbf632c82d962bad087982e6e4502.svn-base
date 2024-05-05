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
    
    int argc = 0; // active tally of the number of args in the line
    char* token = strtok(line, " \n"); // initialising first token

    if (token == NULL) { return 0; } // if stdin is empty

    strcpy(command, token); // initialising the first token as command
    arguments[argc++] = command; // making the first arg the command
    
    while ((token = strtok(NULL, " \n")) != NULL && argc < MaxArguments) { // while loop to add subsequent arguments from the command
        arguments[argc++] = token;
    }

    arguments[argc] = NULL; // Adding NULL as the final argument for later use

    return 1; // Command parsed successfully
}

int main() {
    // initialisers
    char line[MaxCharacters];
    char command[MaxCharacters];
    char* arguments[MaxArguments + 1]; // +1 for NULL terminator
    int num_commands = 0; // active tally of total commands

    while (fgets(line, sizeof(line), stdin) != NULL && num_commands < MaxLines) { // while the input contains some element
        if (parse_command(line, command, arguments)) { // if the function runs correctly
            
            pid_t pid = fork(); // fork to create child progresses

            if (pid == 0) { // Child process
                execvp(command, arguments); // runs command + arguments
            } else { // Parent process
                int status;
                waitpid(pid, &status, 0); // wait for child to end
            }

            num_commands++; // increase tally
        }
    }

    return 0;
}