
#include "test_and_set.h"
#include "function_tac.c"

my_mutex_t lock;
int NTHREADS;
long global=0;

//Fonction appellée par les threads qui un nombre défini de fois la variable global
//en utilisant l'algorithme test-and-test-and-set.
void* func_tts(void * param){
    for (int i = 0; i < 6400/NTHREADS; i++){
        my_mutex_lock_tts(&lock);
        //critical section
        for (int i = 0; i < 10000; i++);
        //Appel de la fonction d'incrémentation
        global=increment(global);
        my_mutex_unlock(&lock);
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

    //Initialisation du mutex
    err=my_mutex_init(&lock);
    if(err!=0) {
        printf("Error pthread_mutex_init");
        return -1;
    }

    //Création des threads
    for(int i=0;i<NTHREADS;i++) {
        err=pthread_create(&(thread[i]),NULL,&func_tts,NULL);
        if(err!=0) {
            printf("Error pthread_create");
            return -1;
        }
    }

    //Attente de la fin des threads
    for(int i=NTHREADS-1;i>=0;i--) {
        err=pthread_join(thread[i],NULL);
        if(err!=0) {
            printf("Error pthread_join");
            return -1;
        }
    }

    //Destruction du mutex
    err=my_mutex_destroy(&lock);
    if(err!=0) {
        printf("Error pthread_mutex_destroy");
        return -1;
    }

    return(EXIT_SUCCESS);
}
