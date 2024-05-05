#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/* ========================= Same as sequence.c's ========================= */
#define MaxCharacters 256
#define MaxArguments 10
#define MaxLines 100

int string_line(char* line, char* command, char** arguments) {
    int argc = 0;
    char* token = strtok(line, " \n");

    if (token == NULL) { return 0; }

    strcpy(command, token); 
    arguments[argc++] = command; 

    while ((token = strtok(NULL, " \n")) != NULL && argc < MaxArguments) {
        arguments[argc++] = token;
    }
    arguments[argc] = NULL;
    return 1;
}
/* ======================================================================== */
// comments refer to what is different in comparrison to sequence.c for selfish reasons (I know what needs changing when something breaks)
int main() {
    char line[MaxCharacters];
    char command[MaxCharacters];
    char* arguments[MaxArguments + 1]; 
    int num_commands = 0;

    int prev_pipe[2] = {-1, -1}; // holds previous pipe

    while (fgets(line, sizeof(line), stdin) != NULL && num_commands < MaxLines) {
        if (string_line(line, command, arguments)) {
            int curr_pipe[2] = {-1, -1};
            
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