/**  
 * 
 * 	The exectue files are what you should be looking at. 
 *  Although I could add the function here, I felt like it makes more sence for the execute file to store the funtion.
 * 
 *  Only because the file name is 'executeX.c' and the pipeProcess function is just sifting through what is executed whilst  
 * this file is to take inputs and send them elsewhere.
 * 
 *  Blame my Algorithm Design & Data Structures class.
 * 
 **/

#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<signal.h>
#include	"smsh.h"

#define	DFL_PROMPT	"> "

int main()
{
	char	*cmdline, *prompt, **arglist;
	int	result;
	void	setup();

	prompt = DFL_PROMPT ;
	setup();

	while ( (cmdline = next_cmd(prompt, stdin)) != NULL ){
		if ( (arglist = splitline(cmdline)) != NULL  ){
			result = pipeProcess(arglist);
			freelist(arglist);
		}
		free(cmdline);
	}
	return 0;
}

void setup()
/*
 * you know what it does :)
 */
{
	signal(SIGINT,  SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void fatal(char *s1, char *s2, int n)
{
	fprintf(stderr,"Error: %s,%s\n", s1, s2);
	exit(n);
}
