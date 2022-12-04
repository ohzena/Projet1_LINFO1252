#include <stdlib.h>   //Nbr ramdom
#include <pthread.h>  //Mutex et thread
#include <stdio.h> //EXIT_SUCCESS
#include <string.h>
#include <errno.h>
#include <unistd.h> //sleep
#include <ctype.h>
#include <semaphore.h>
#include "test_and_set.h"

int test_and_set(my_mutex_t mutex){
    int y;
    asm(
            "movl $1, %%eax;"
            "xchgl %%eax, (%1);"
            "movl %%eax, %0;"
            :"=&r"(y) /* y is output operand, note the  
                & constraint modifier. */
            :"r"(mutex.val)   /* ptr to val is input operand */
            :"%eax"); /* %eax is clobbered register */
    return y;
}

int my_mutex_init(my_mutex_t *mutex_ptr){
    mutex_ptr->val = (int*)malloc(sizeof(int));
    if (mutex_ptr->val == NULL){
        return -1;
    }
    *(mutex_ptr->val) = 0;
    return 0;
}

int my_mutex_destroy(my_mutex_t *mutex_ptr){
    free(mutex_ptr->val);
    return 0;
}

int my_mutex_lock(my_mutex_t *mutex_ptr){
    while(test_and_set(*mutex_ptr)){
    }
    return 0;
}

int my_mutex_unlock(my_mutex_t *mutex_ptr){
    asm (
        "movl $0, %%eax;"
        "xchgl %%eax, (%0);"
        :
        :"r"(mutex_ptr->val)   /* ptr to val is input operand */
        :"%eax"); /* %eax is clobbered register */
    return 0;
}

int increment(int i) {
  return i+1;
}


