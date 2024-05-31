#include "slow_functions.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    void * test;
	slow_function1(slow_function1(slow_function1(slow_function1(slow_function1(slow_function1(slow_function1(slow_function1(slow_function1(slow_function1(slow_function2(test)))))))))));
}
