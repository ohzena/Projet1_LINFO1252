#ifndef HEADER_FILE_TAS
#define HEADER_FILE_TAS

#include <stdlib.h>   //Nbr ramdom
#include <pthread.h>  //Mutex et thread
#include <stdio.h> //EXIT_SUCCESS
#include <string.h>
#include <errno.h>
#include <unistd.h> //sleep
#include <ctype.h>
#include <semaphore.h>

typedef struct my_mutex{
    int *val;
} my_mutex_t;

//test-and-set implemantation
int test_and_set(my_mutex_t mutex);

int my_mutex_init(my_mutex_t *mutex_ptr);

int my_mutex_destroy(my_mutex_t *mutex_ptr);

int my_mutex_lock(my_mutex_t *mutex_ptr);

int my_mutex_unlock(my_mutex_t *mutex_ptr);

int increment(int i);

//test-and-test-set implemantation
int my_mutex_lock_tts(my_mutex_t* mutex_ptr); 


//semophore implementation 

typedef struct my_sem{
    my_mutex_t * mutex_ptr;
    int *val_ptr;
} my_sem_t;

int my_sem_init(my_sem_t *sem_ptr,int init_val);
int my_sem_wait(my_sem_t *sem_ptr);
int my_sem_post(my_sem_t *sem_ptr);
int my_sem_destroy(my_sem_t *sem_ptr);

#endif
