#include <stdlib.h>   //Nbr ramdom
#include <pthread.h>  //Mutex et thread
#include <stdio.h> //EXIT_SUCCESS

typedef struct my_mutex{
    int *val;
} my_mutex_t;

int my_mutex_init(my_mutex_t *mutex_ptr){
    mutex_ptr->val = (int*)malloc(sizeof(int));
    if (mutex_ptr->val == NULL){
        return -1;
    }
    *(mutex_ptr->val) = 0;
    return 0;
}

int my_mutex_lock(my_mutex_t *mutex_ptr){
    int y=1;
    while(y!=0){
        asm (
            "movl $1, %%eax;"
            "xchgl %%eax, (%1);"
            "movl %%eax, %0;"
            :"=&r"(y) /* y is output operand, note the  
                & constraint modifier. */
            :"r"(mutex_ptr->val)   /* ptr to val is input operand */
            :"%eax"); /* %eax is clobbered register */
        if(y!=0){
        }
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