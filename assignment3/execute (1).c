/* execute.c - code used by small shell to execute commands */

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<sys/wait.h>
#include	<sys/wait.h>
#include <string.h>

char *pipe_char = "|";

int execute(char *argv[])
{
printf ("Argv1 '%s' \n",argv[1]);

if (strcmp(argv[1],pipe_char) == 0)
{
   printf ("d1");
   execute_pipe(argv);
}
else
{
   printf ("d2");
   execute_nonpipe(argv);
}
}

int execute_nonpipe(char *argv[])
/*
 * purpose: run a program passing it arguments
 * returns: status returned via wait, or -1 on error
 *  errors: -1 on fork() or wait() errors

 */
{
	int	pid ;
	int	child_info = -1;

	if ( argv[0] == NULL )		/* nothing succeeds	*/
		return 0;
        
        printf("execute_nonpipe\n");

	if ( (pid = fork())  == -1 )
		perror("fork");
	else if ( pid == 0 ){
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		printf("Debug 5\n");
		execvp(argv[0], argv);
		printf("Debug 6\n");
		perror("cannot execute command");
		exit(1);
	}
	else {
		if ( wait(&child_info) == -1 )
			perror("wait");
	}
	return child_info;
}
int execute_pipe(char *argv[])
{
        char * commands1[2];
        commands1[0] = argv[0];
        commands1[1] = NULL;

        char * commands2[2];
        commands2[0] = argv[2];
        commands2[1] = NULL;

        char test_buffer[100];
              int     child_info = -1;
        int my_pipe[2];
        pid_t my_pid;

        // Boring Pipe Failure Stuff
        if (pipe(my_pipe) == -1)
        {
                printf("Error, Pipe Failed\n");
                return 1;
        }

        printf("execute_pipe\n");
        //scanf("%s", input_str);

        my_pid = fork();

        // Fork Fail
        if (my_pid < 0)
        {
                printf("Failed Fork\n");
        }

        // Fork Parent
        else if (my_pid > 0)
        {
                if ( wait(&child_info) == -1 )
                        perror("wait");
                close(my_pipe[1]);
                dup2(my_pipe[0], 0);
                close(my_pipe[0]);
                wait(NULL);
                execvp(commands2[0], commands2);
        }

        // Fork Child
        else
        {
                signal(SIGINT, SIG_DFL);
                signal(SIGQUIT, SIG_DFL);
                close(my_pipe[0]);
                dup2(my_pipe[1], 1);
                close(my_pipe[1]);
                execvp(commands1[0], commands1);
        }

}

