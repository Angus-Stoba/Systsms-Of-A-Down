
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// global values set by instructions
#define MaxCharacters 256
#define MaxArguments 10
#define MaxLines 100

// removed tokens function

int main() {
    char commandArgs[MaxLines][MaxArguments];
    int num_commands = 0;

    // using while loop to breakdown each command and subsequent arguments, then tallying number of commands
    while (fgets(commandArgs[num_commands], MaxCharacters, stdin) != NULL && num_commands < MaxLines) {
        num_commands++;
    }

    int prev_pipe[2]; // Used to hold previous pipe
    int curr_pipe[2]; // Used to hold the current pipe

    int i = 0;

    while (i < num_commands){
        // if curr pipe is invalid
        if (i < (num_commands - 1)) {
            if (pipe(curr_pipe) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        pid_t pid = fork(); // create child / parent

        if (pid == -1) { // if fork errors
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) { // child
            if (i > 0) { // if there is a previous command
                dup2(prev_pipe[0], STDIN_FILENO); // duplicate pipe read to stdin
                close(prev_pipe[0]); // close read
                close(prev_pipe[1]); // close write
            }

            if (i < (num_commands - 1)) { // if there is following commands
                close(curr_pipe[0]); // close read
                dup2(curr_pipe[1], STDOUT_FILENO); // duplicate pipe write to stdout
                close(curr_pipe[1]); // close write
            }
            execlp("sh", "sh", "-c", commandArgs[i], NULL);
            perror("execlp");
            exit(EXIT_FAILURE);
        } else { // parent
            if (i > 0) { 
                // closing prev_pipe
                close(prev_pipe[0]);
                close(prev_pipe[1]); 
            }
            if (i < (num_commands - 1)) { 
                // updating prev pipe for next loop
                prev_pipe[0] = curr_pipe[0];
                prev_pipe[1] = curr_pipe[1];
            }
        }
        i++;
    }

    if (prev_pipe[0] != -1) {
        // closing if any weren't closed
        close(prev_pipe[0]);
        close(prev_pipe[1]); 
    }

    int j = 0;
    while (j < num_commands) {
        wait(NULL); // waiting for all childs that are unresolved
        j++;
    }

    return 0;
}