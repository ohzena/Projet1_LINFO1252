#include "test_and_set.h"

my_sem_t sem;

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

void *post(void * param) {
    for(int i=0; i<2; i++){
        printf("Benita dort\n");
        sleep(3);
        printf("Benita se reveille\n");
        my_sem_post(&sem);
    }
    return 0;
}

int main (int argc, char *argv[])  {
    int err;
    my_sem_init(&sem,1);
    printf("Val: %i\n",*(sem.val_ptr));
    my_sem_wait(&sem);
    printf("Val: %i\n",*(sem.val_ptr));
    pthread_t thread;
    err=pthread_create(&(thread),NULL,&post,NULL);
    if(err!=0){
        printf("Error pthread_create\n");
        return -1;
    }
    printf("SImon regarde Benita\n");
    my_sem_wait(&sem);
    printf("SImon regarde le cours\n");
    my_sem_wait(&sem);
    err=pthread_join(thread,NULL);
    if(err!=0){
        printf("Error pthread_join\n");
        return -1;
    }
    my_sem_destroy(&sem);
    printf("Le cours est fini\n");
    return 0;
}