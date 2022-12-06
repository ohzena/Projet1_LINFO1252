#include "test_and_set.h"
#include "function_tac.c"

my_sem_t sem;

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