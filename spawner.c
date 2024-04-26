#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>

#if defined (_STDDEF_H) || defined (__need_NULL)
#undef NULL		/* in case <stdio.h> has defined it. */
#ifdef __GNUG__
#define NULL __null
#else   /* G++ */
#ifndef __cplusplus
#define NULL ((void *)0)
#else   /* C++ */
#define NULL 0
#endif  /* C++ */
#endif  /* G++ */
#endif	/* NULL not defined and <stddef.h> or need NULL.  */
#undef	__need_NULL


int main(int argc, char *argv[]) {

    const char s[2] = " ";

    char *command = strtok(argv[1], s);
    char *args[argc];

    int i = 0;
    args[i++] = command;

    while ((args[i++] = strtok(NULL, s)) != NULL){ // replace '0's with NULL
        printf("s =  %s \n", args[i]);
        args[i++] = strtok(0, s);
    }

    
    for (int j = 0; j < 2; j++){
        printf("s =  %s \n", args[j]);
    }
    
    
    execvp(command, args);
    perror("execvp");
    exit(1);
    
    return 0;

}