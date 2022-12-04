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

int my_sem_init(my_sem_t *sem_ptr,int init_val){
    //Allocation and initiallisation the space for the value in the semaphore
    sem_ptr->val_ptr = (int*)malloc(sizeof(int));
    if(sem_ptr->val_ptr == NULL){
        return -1;
    }
    *(sem_ptr->val_ptr)=init_val;

    //Allocation and initiallisation the space for mutex
    sem_ptr->mutex_ptr = (my_mutex_t*)malloc(sizeof(my_mutex_t));
    if(sem_ptr->mutex_ptr == NULL){
        return -1;
    }
    if(-1==my_mutex_init(sem_ptr->mutex_ptr)){
        return -1;
    }
    return 0;
}

int my_sem_wait(my_sem_t *sem_ptr){
    int go = 1;
    while(go){
        //Use the mutex to past the thread to ready state 
        //and decrease the value (if value of semaphore > 0) 
        //without concurrent modification.
        my_mutex_lock_tts(sem_ptr->mutex_ptr);
        if(*(sem_ptr->val_ptr)>0){
            go = 0;
            *(sem_ptr->val_ptr) -= 1;
        }
        my_mutex_unlock(sem_ptr->mutex_ptr);
    }
    return 0;
}

int my_sem_post(my_sem_t *sem_ptr){
    my_mutex_lock_tts(sem_ptr->mutex_ptr);
    *(sem_ptr->val_ptr) += 1;
    my_mutex_unlock(sem_ptr->mutex_ptr);
    return 0;
}

int my_sem_destroy(my_sem_t *sem_ptr){
    my_mutex_destroy(sem_ptr->mutex_ptr);
    free(sem_ptr->mutex_ptr);
    free(sem_ptr->val_ptr);
    return 0;
}


