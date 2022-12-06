#include <stdlib.h>   //Nbr ramdom
#include <semaphore.h> //semaphore
#include <pthread.h>  //Mutex et thread
#include <stdio.h> //EXIT_SUCCESS


pthread_mutex_t mutex;
sem_t empty;
sem_t full;
int* buffer;
int first;
int last;
int buffer_size;
int in;


int init_buffer(){
    buffer_size = 8;
    if(0 != pthread_mutex_init(&mutex, NULL)){
        return -1;
    }
    if (sem_init(&empty, 0 , buffer_size) != 0){
        return -1;
    }
    
    if (sem_init(&full, 0 , 0) !=0){
        return -1;
    }

    buffer = (int*) malloc(sizeof(int)* buffer_size);
    if (buffer==NULL){
        return -1;
    }
    first = 0;
    last = 0;
    in = 0;
    return 0;
}

int destroy_buffer(){
    if (pthread_mutex_destroy(&mutex) !=0 ){
        return -1;
    }
    if (sem_destroy(&full) != 0){
        return -1;
    }
    if (sem_destroy(&empty) != 0){
        return -1;
    }
    free(buffer);
    return 0;
}

int produce(){
    for(int i=0;i<10000;i++);
    return 1;
}

void put(int data){
    if(in == buffer_size){
        printf("Put dans un buffer full \n");
    }
    buffer[last] = data;
    last = (last+1)%buffer_size;
    in = in +1;
}

// Producteur
void *producer(void *param) {
    int * ret = (int*) malloc(sizeof(int));
    *ret = -1;
    int item;
    int done = *((int*)param);
    while(done>0){
        item = produce();
        if(sem_wait(&empty)==-1){ // attente d'une place libre
            pthread_exit(ret);
        }
        if(pthread_mutex_lock(&mutex)!=0){
            pthread_exit(ret);
        }
        // section critique
        
        put(item);
        
        
        if(pthread_mutex_unlock(&mutex)!=0){
            pthread_exit(ret);
        }
        if(sem_post(&full)!=0){ // il y a une place remplie en plus
            pthread_exit(ret);
        }
        done -= 1;

    }
    *ret = 0;
    pthread_exit(ret);
}

int get(){
    if(in == 0){
        printf("Error get sur buffer vide \n");
    }
    int data = buffer[first];
    first = (first+1)%buffer_size;
    in = in -1;
    return data;
}

int consume(int item){
    for(int i=0;i<10000;i++);
    return item;
}

// Consommateur
void *consumer(void *param){
    int * ret = (int*) malloc(sizeof(int));
    *ret = -1;
    int item;
    int done = *((int*)param);
    while(done>0) {
        if(sem_wait(&full)!=0){ // attente d'une place remplie
            pthread_exit(ret);
        }
        if(0!=pthread_mutex_lock(&mutex)){
            pthread_exit(ret);
        }
        // section critique
        
        item=get();
        
        if(0!=pthread_mutex_unlock(&mutex)){
            pthread_exit(ret);
        }
        
        if(sem_post(&empty)){ // il y a une place libre en plus
            pthread_exit(ret);
        }

        consume(item);
        done -=1;
    }
    *ret = 0;
    pthread_exit(ret);
}

int main(int argc, char *argv[]){
    if (argc != 3){
        printf("Illegal number of argument\n");
        return -1;
    }
    if (init_buffer() !=0){
        printf("Error init_buffer\n");
        return -1;
    }
    int nbr_thread = atoi(argv[1]);
    int nbr_producer = nbr_thread/2;
    int nbr_consumer = (nbr_thread/2) + (nbr_thread%2);
    int nbr_cycle = atoi(argv[2]);

    
    pthread_t thread_producer[nbr_producer];
    pthread_t thread_consumer[nbr_consumer];

    int err;


    int * nbr_cycle_producer_ptr = (int*) malloc(sizeof(int));
    int * nbr_cycle_producer_supp_ptr = (int*) malloc(sizeof(int));
    *nbr_cycle_producer_ptr = nbr_cycle/nbr_producer;
    *nbr_cycle_producer_supp_ptr = (nbr_cycle/nbr_producer)+1;
    int nbr_cycle_supp = nbr_cycle%nbr_producer;
    for(int i=0;i<nbr_producer;i++) {
        if (nbr_cycle_supp>0){
            err=pthread_create(&(thread_producer[i]),NULL,&producer,(void *) nbr_cycle_producer_supp_ptr);
        }
        else {
            err=pthread_create(&(thread_producer[i]),NULL,&producer,(void *) nbr_cycle_producer_ptr);
        }
        if(err!=0) {
            printf("Error: producer creation\n");
            return -1;
        }
        nbr_cycle_supp -= 1;
    }

    int * nbr_cycle_consumer_ptr = (int*) malloc(sizeof(int));
    int * nbr_cycle_consumer_supp_ptr = (int*) malloc(sizeof(int));
    *nbr_cycle_consumer_ptr = nbr_cycle/nbr_consumer;
    *nbr_cycle_consumer_supp_ptr = (nbr_cycle/nbr_consumer)+1;
    nbr_cycle_supp = nbr_cycle%nbr_consumer;
    for(int i=0;i<nbr_consumer;i++) {
        if (nbr_cycle_supp>0){
            err=pthread_create(&(thread_consumer[i]),NULL,&consumer,(void*)nbr_cycle_consumer_supp_ptr);
        }
        else{
            err=pthread_create(&(thread_consumer[i]),NULL,&consumer,(void*)nbr_cycle_consumer_ptr);
        }
        if(err!=0) {
            printf("Error: consumer creation\n");
            return -1;
        }
        nbr_cycle_supp -= 1;
    }

    for(int i=0;i<nbr_producer;i++) {
        int *err_ptr;
        if(0 != pthread_join(thread_producer[i],(void **)&err_ptr)){
            printf("Error: producer join\n");
            return -1;
        }
        if(*err_ptr==-1){
            printf("Error in producer thread %i\n",i);
            return -1;
        }
        free(err_ptr);
    }
    for(int i=0;i<nbr_consumer;i++) {
        int *err_ptr;
        if(0 != pthread_join(thread_consumer[i],(void**)&err_ptr)){
            printf("Error: consumer join\n");
            return -1;
        }
        if(*err_ptr==-1){
            printf("Error in consumer thread %i\n",i);
            return -1;
        }
        free(err_ptr);
    }

    free(nbr_cycle_consumer_ptr);
    free(nbr_cycle_consumer_supp_ptr);
    free(nbr_cycle_producer_ptr);
    free(nbr_cycle_producer_supp_ptr);

    if (destroy_buffer() != 0){
        printf("Error destroy_buffer \n");
        return -1;
    }
    return EXIT_SUCCESS;
}