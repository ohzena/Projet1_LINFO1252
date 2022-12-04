#include "test_and_set.h"

int NTHREADS;
long global=0;
my_mutex_t mutex_global;

int test_and_set(my_mutex_t mutex){
    int y;
    asm (
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

void *func(void * param) {
  int err;
  for(int j=0;j<6400/NTHREADS;j++) {
    err=my_mutex_lock(&mutex_global);
    if(err!=0)
      printf("Error pthread_mutex_lock");
      return -1;
    global=increment(global);
    err=my_mutex_unlock(&mutex_global);
    if(err!=0)
      printf("Error pthread_mutex_unlock");
      return -1;
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
    if(err!=0)
        printf("Error pthread_mutex_init");
        return -1;

    for(int i=0;i<NTHREADS;i++) {
        err=pthread_create(&(thread[i]),NULL,&func,NULL);
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

    err=my_mutex_destroy(&mutex_global);
    if(err!=0)
        printf("Error pthread_mutex_destroy");
        return -1;

    printf("global: %ld\n",global);

    return(EXIT_SUCCESS);
}

