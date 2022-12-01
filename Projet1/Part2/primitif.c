#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


/***************************
 * test and set implem
 * *************************/
int test_and_set(volatile int*, int);
int lock_ts(int *);
void unlock_ts(volatile int*);
int init_test_and_set(int**);


/***************************
 * test and set implem
 * *************************/
int lock_tts(volatile int *);


typedef struct primitive_sem{
    int val;
    int* lock;
}prim_sem;

//Initialize the sem structure and his lock
int prim_sem_init(prim_sem** s, int start_val){
    *s = malloc(sizeof(struct primitive_sem));
    if (*s == NULL)
    {
        return -1;
    }
    (**s).lock = malloc(sizeof(int));
    *((**s).lock) = 0;
    (*s)->val = start_val;
    return 0;
}

//free the sem struct
int prim_sem_destroy(prim_sem* sem){
    free(sem->lock);
    free(sem);
    return 0;
}

//takes sem structure as an argument
//puts the threads in spinlock if the val is not >0 and decrements the val of sem once out of the spinlock
int prim_sem_wait(prim_sem* sem){
    bool cond = false;
    
    while (!cond){
        lock_tts(sem->lock);
        
        if (sem->val > 0)
        {
            int val = *(sem->lock);
            //printf("before name: %s val: %d and lock: %d\n", name, sem->val, *(sem->lock));
            //printf("%d\n", val);
            sem->val = sem-> val-1;
            //printf("after name: %s val: %d and lock: %d\n", name, sem->val, *(sem->lock));
            cond = true;
            unlock_ts(sem->lock);
        }else{
            unlock_ts(sem->lock);
        }
    }
    return 0;
}

//takes sem structure as an argument
//increments the val of sem
int prim_sem_post(prim_sem* sem){
    lock_tts(sem->lock);
    sem->val = sem->val+1;
    unlock_ts(sem->lock);
    return 0;
}

//prints the sem struct values
void print_sem(prim_sem* sem){
    printf("sem: adress %p",sem);
    printf("  val:%d",sem->val);
    printf("lock: adres:%p  val:%d\n",sem->lock,*(sem->lock));
    fflush(stdout);
}