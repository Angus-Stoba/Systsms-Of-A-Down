#include "slow_functions.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

// How nice of me to include a global that tells you how many commands there were :)
int total_commands = 0;


// ####################################################################################
// ## Please write some code in the following two functions

// ================= SEE 'part1.c' FOR WHY THIS IS HERE =================
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
// ======================================================================

pthread_mutex_t lock;
pthread_cond_t condition;

void * writer(void * in_ptr)
{
	char** inputs = (char** )in_ptr; // converts void* type given from main, into a char** type
	pthread_t thread_bw; // thread type for bad_write
	
	for ( int loops = 0; loops < total_commands; loops++){ // for lines in [stdin]
		
		pthread_mutex_lock(&lock); // locks between functions

		while(get_written() != 0){ // when get_written() returns 0, bad_read has finished 
			pthread_cond_wait(&condition, &lock);
		}	

		// creating thread of bad_write, and waiting to finish
		pthread_create(&thread_bw, NULL, bad_write, inputs[loops]);
		pthread_join(thread_bw, NULL);

		// Send signal to reader to start, then unlock mutex
		pthread_cond_signal(&condition);
		pthread_mutex_unlock(&lock);
	};
	
	return NULL;
}

void * reader(void * empty)
{
	pthread_t thread_br; // thread type for bad_read

	for ( int loops = 0; loops < total_commands; loops++){ // for total lines in [stdin]

		pthread_mutex_lock(&lock); // locks between functions
		
		while(get_written() != 1){ // when get_written() returns 1, bad_read has finished 
			pthread_cond_wait(&condition, &lock);
		}

		// creating thread of bad_read, and waiting to finish
		pthread_create(&thread_br, NULL, bad_read, NULL);
		pthread_join(thread_br, NULL);


		// Send signal to writer to start, then unlock mutex
		pthread_cond_signal(&condition);
		pthread_mutex_unlock(&lock);
	};

	return NULL;
}


int main()
{
	// ## SOME SPACE IN CASE YOU NEED TO INITIALISE VARIABLES

	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&condition, NULL);

	// ################################################################################
	// ## DO NOT MODIFY BELOW HERE

	// ## Parse STDIN and read into commands
	char * commands[100];
	char line[256];
    while (fgets(line, 256, stdin))
    {
		commands[total_commands] = (char*)(malloc(strlen(line) * sizeof(char)));
 		strcpy(commands[total_commands], line);
		total_commands = total_commands + 1;
	}

	pthread_t write1;
	pthread_t read1;

	// Creates a thread which executes writer!
	if(pthread_create(&write1, NULL, writer, commands))
	{
		fprintf(stderr, "Error creating write thread\n");
		return 1;
	}

	// Creates a thread which executes reader!
	if(pthread_create(&read1, NULL, reader, NULL))
	{
		fprintf(stderr, "Error creating read thread\n");
		return 1;
	}

	// Ensure Threads Join Well
	if(pthread_join(write1, NULL)) 
	{
		fprintf(stderr, "Error joining write thread\n");
		return 2;
	}

	if(pthread_join(read1, NULL)) 
	{
		fprintf(stderr, "Error joining read thread\n");
		return 2;
	}

	// Did you really call the right functions?
	get_output();

	// I am a responsible memory user!
	int command_i;
	for (command_i = 0; command_i < total_commands; command_i++)
	{
		free(commands[command_i]);
	}
	return 0;
	// ## DO NOT MODIFY ABOVE HERE
	// ################################################################################
}
