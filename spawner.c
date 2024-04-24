#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[]) {

    const char s[2] = " ";

    char *command = strtok(argv[1], s);
    char *args[argc];

    int i = 0;
    args[i++] = command;

    while ((args[i++] = strtok(0, s)) != 0){ // replace '0's with NULL
        printf("s =  %s \n", args[i]);
        args[i++] = strtok(0, s);
    }

    
    for (int j = 0; j < 2; j++){
        printf("s =  %s \n", args[j]);
    }
    
    /*
    execvp(command, args);
    perror("execvp");
    exit(1)
    */
    return 0;

}