#include "test_and_set.h"

my_mutex_t* lock;
int NTHREADS;
long global=0;

int my_mutex_lock_tts(my_mutex_t* mutex_ptr){
    while (test_and_set(*mutex_ptr)) {
        while (*(mutex_ptr-> val) != 0) {
        }
    }
    return 0;
}

void* func_tts(void * param){
    for (int i = 0; i < 6400/NTHREADS; i++){
        my_mutex_lock_tts(lock);
        //critical section
        for (int i = 0; i < 10000; i++);
        global=increment(global);
        my_mutex_unlock(lock);
    }
    return(NULL);
}

int main (int argc, char *argv[])  {
    int NTHREADS;
    long global=0;
    my_mutex_t lock;

    if(argc != 2){
        printf("Illegal argument number\n");
        return EXIT_FAILURE;
    }
    NTHREADS = atoi(argv[1]);
    pthread_t thread[NTHREADS];
    int err;

    err=my_mutex_init(&lock);
    if(err!=0)
        printf("Error pthread_mutex_init");
        return -1;

    for(int i=0;i<NTHREADS;i++) {
        err=pthread_create(&(thread[i]),NULL,&func_tts,NULL);
        if(err!=0)
        printf("Error pthread_create");
        return -1;
    }

    for(int i=NTHREADS-1;i>=0;i--) {
        err=pthread_join(thread[i],NULL);
        if(err!=0)
        printf("Error pthread_join");
        return -1;
    }

    err=my_mutex_destroy(&lock);
    if(err!=0)
        printf("Error pthread_mutex_destroy");
        return -1;

    printf("global: %ld\n",global);

    return(EXIT_SUCCESS);
}
