#include "slow_functions.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

//  ========================== JUST FOR CONTEXT ==========================
/*
    Any 'NULL' description found in a '.h' does NOT work for me, 
    so I paste the statement used to describe NULL from the stddef.h file
*/
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
// =======================================================================

void run_slowfunc10(){
    // Function to run 10 slow_function1 functions simultaneously
    pthread_t slow1; // Used for thread type

    for (int i = 0; i < 10; i++){
        pthread_create(&slow1, NULL, &slow_function1, NULL); 
    }
}

int main()
{
    // Main must run 10 "slow_function1" functions between the beginning and end of "slow_function2"

    pthread_t slow2; // Used for thread type
    pthread_create(&slow2, NULL, &slow_function2, NULL); // runs "slow_function2" in background
    run_slowfunc10(); // calls 10 "slow_function1"s

    pthread_join(slow2, NULL); // Used to end main, when the thread of 'slow2' type is completed

    return 0;
}
