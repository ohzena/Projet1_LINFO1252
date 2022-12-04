#include "test_and_set.h"
#include "function_tac.c"

int NTHREADS;
long global=0;
my_mutex_t mutex_global;

void *func(void * param) {
  int err;
  for(int j=0;j<6400/NTHREADS;j++) {
    err=my_mutex_lock(&mutex_global);
    if(err!=0) {
        printf("Error pthread_mutex_lock");
    }
    global=increment(global);
    err=my_mutex_unlock(&mutex_global);
    if(err!=0) {
        printf("Error pthread_mutex_unlock");
    }
      
  }
  return(NULL);
}

int main (int argc, char *argv[])  {
    if(argc != 2){
        printf("Illegal argument number\n");
        return EXIT_FAILURE;
    }
    NTHREADS = atoi(argv[1]);
    pthread_t thread[NTHREADS];
    int err;

    err=my_mutex_init( &mutex_global);
    if(err!=0) {
        printf("Error pthread_mutex_init");
        return -1;
    }
        

    for(int i=0;i<NTHREADS;i++) {
        err=pthread_create(&(thread[i]),NULL,&func,NULL);
        if(err!=0) {
            printf("Error pthread_create");
            return -1;
        }
    }

    for(int i=NTHREADS-1;i>=0;i--) {
        err=pthread_join(thread[i],NULL);
        if(err!=0) {
            printf("Error pthread_join");
            return -1;
        }
    }

    err=my_mutex_destroy(&mutex_global);
    if(err!=0) {
        printf("Error pthread_mutex_destroy");
        return -1;
    }
        

    return(EXIT_SUCCESS);
}

