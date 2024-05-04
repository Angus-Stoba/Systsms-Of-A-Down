// gcc spawner.c -o spawner | ./spawner "ls -l" // must have quotes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    /*if (argc < 2) {
        fprintf(stderr, "Usage: %s \"command param1 param2 ...\"\n", argv[0]);
        exit(EXIT_FAILURE);
    }*/

    char *command = strtok(argv[1], " "); // Get the command
    char *args[argc]; // Array to hold command and arguments

    // Tokenize the rest of the string to get parameters
    int i = 0;
    args[i++] = command;
    while ((args[i++] = strtok(NULL, " ")) != NULL);

    // Replace the current process with the command
    execvp(command, args);
    //perror("execvp"); // If execvp fails
    //exit(EXIT_FAILURE);

    return 0; // This line will never be reached
}




/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>




int main(int argc, char *argv[]) {

    const char s[2] = "";

    char *command = strtok(argv[1], s);
    char *args[argc];


    int i = 0;
    args[i] = command;

    while (strtok(NULL, s) != NULL){ // replace '0's with NULL
        printf("a =  %s \n", args[i]);
        args[i++] = strtok(NULL, s);
        
    }
    
    printf("?\n");
    
    
    for (int j = 0; j < 2; j++){
        printf("s =  %s \n", args[j]);
    }
    
    
    execvp(command, args);
    perror("execvp");
    exit(1);
    
    return 0;

}*/