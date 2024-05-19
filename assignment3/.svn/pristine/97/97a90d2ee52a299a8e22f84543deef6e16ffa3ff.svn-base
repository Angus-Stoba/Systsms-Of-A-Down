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
#include        <fcntl.h>


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

        // Part 2
        int inputRedirect = 0;
        int outputRedirect = 0;
        char *inputFile = NULL;
        char *outputFile = NULL;
        
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
                                return pipeProcess(postCommand);         // temp fix for multi-pipes ( it messes with the prompt design )
                        }

                        close(pipefd[0]);
                        close(pipefd[1]);
                        waitpid(prePipe, NULL, 0);
                        waitpid(postPipe, NULL, 0); 

                        return 0;

                }
                else if (strcmp(argv[i], "<") == 0) { // when a redirect is found       || Part 2 ||    
                        inputRedirect = 1;
                        inputFile = argv[i + 1];
                        argv[i] = NULL;
                }
                else if (strcmp(argv[i], ">") == 0) {
                        outputRedirect = 1;
                        outputFile = argv[i + 1];
                        argv[i] = NULL;
                }
        i++;
    }       
    if (inputRedirect || outputRedirect) { // if either redirect occurs
                if ((prePipe = fork()) == -1) { // create a fork
                        perror("fork");
                        return -1;
                }   
                if (prePipe == 0) { // child 
                        if (inputRedirect) { // if "<" occured
                                int redicectInTo = open(inputFile, O_RDONLY);
                                if (redicectInTo < 0) {
                                        perror("open");
                                        exit(1);
                                }
                                dup2(redicectInTo, STDIN_FILENO);
                                close(redicectInTo);
                        }       
                        if (outputRedirect) { // if ">" occured
                                int redirectOutTo = open(outputFile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                                if (redirectOutTo < 0) {
                                        perror("open");
                                        exit(1);
                                }
                                dup2(redirectOutTo, STDOUT_FILENO);
                                close(redirectOutTo);
                        }       
                        execvp(argv[0], argv);
                        perror("execvp");
                        exit(1);
                }
                else { // parent
                        waitpid(prePipe, NULL, 0);
                        return 0;
                }
        
                i++;

        }               
        
        return execute(argv); 
}
        