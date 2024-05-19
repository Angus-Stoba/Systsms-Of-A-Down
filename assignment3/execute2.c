/* execute.c - code used by small shell to execute commands */

/**
 * 
 *  Part 1:
 *      pipeProcess function:
 *              finds pipes, nullifies them, and collects the commands + arguments accordingly to propaly work like a pipe
 * 
*/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	<sys/wait.h>
#include	<sys/wait.h>

#include        <string.h>


int execute(char *argv[])
/*
 * unchanged from original
 */
{
	int	pid ;
	int	child_info = -1;

	if ( argv[0] == NULL )
		return 0;

	if ( (pid = fork())  == -1 )
		perror("fork");
	else if ( pid == 0 ){
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execvp(argv[0], argv);
		perror("cannot execute command");
		exit(1);
	}
	else {
		if ( wait(&child_info) == -1 )
			perror("wait");
	}
	return child_info;
}
int pipeProcess(char *argv[]) // Finds pipe in command line, and forks according to how many arguments the commands have
{
        // Part 1
        int i = 0;
        int pipefd[2];
        int prePipe, postPipe;
        char **preCommand, **postCommand;
        
        while (argv[i] != NULL) {
                if (strcmp(argv[i], "|") == 0) { // when a pipe is found                || Part 1 ||
                
                        argv[i] = NULL;
                        preCommand = argv;
                        postCommand = &argv[i + 1];    

                        if (pipe(pipefd) == -1) {
                                perror("pipe");
                                return -1;
                        }       

                        if ((prePipe = fork()) == -1) {         // fork error
                                perror("fork");
                                return -1;
                        }
                        else if (prePipe == 0) {                // fork child
                                close(pipefd[0]);
                                dup2(pipefd[1], STDOUT_FILENO);
                                close(pipefd[1]);
                                execvp(preCommand[0], preCommand);
                                perror("execvp");
                                exit(1);
                        }       
                        if ((postPipe = fork()) == -1) {        // fork error
                                perror("fork");
                                return -1;
                        }
                        else if (postPipe == 0) {               // fork child
                                close(pipefd[1]);
                                dup2(pipefd[0], STDIN_FILENO);
                                close(pipefd[0]);
                                execvp(postCommand[0], postCommand);
                                perror("execvp");
                                exit(1);
                        }

                        close(pipefd[0]);
                        close(pipefd[1]);
                        waitpid(prePipe, NULL, 0);
                        waitpid(postPipe, NULL, 0); 

                        return 0;

                }
        
                i++;

        }     

        return execute(argv); 
 
}
