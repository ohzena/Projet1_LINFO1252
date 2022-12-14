#include "test_and_set.h"
#include "function_tac.c"

my_mutex_t mutex;
my_sem_t empty;
my_sem_t full;
int* buffer;
int first;
int last;
int buffer_size;
int in;


int init_buffer(){
    buffer_size = 8;
    if(0 != my_mutex_init(&mutex)){
        return -1;
    }
    if (my_sem_init(&empty, buffer_size) != 0){
        return -1;
    }
    
    if (my_sem_init(&full,0) !=0){
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
    if (my_mutex_destroy(&mutex) !=0 ){
        return -1;
    }
    if (my_sem_destroy(&full) != 0){
        return -1;
    }
    if (my_sem_destroy(&empty) != 0){
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
        if(my_sem_wait(&empty)==-1){ // attente d'une place libre
            pthread_exit(ret);
        }
        if(my_mutex_lock_tts(&mutex)!=0){
            pthread_exit(ret);
        }
        // section critique
        
        put(item);
        
        
        if(my_mutex_unlock(&mutex)!=0){
            pthread_exit(ret);
        }
        if(my_sem_post(&full)!=0){ // il y a une place remplie en plus
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
        if(my_sem_wait(&full)!=0){ // attente d'une place remplie
            pthread_exit(ret);
        }
        if(0!=my_mutex_lock_tts(&mutex)){
            pthread_exit(ret);
        }
        // section critique
        
        item=get();
        
        if(0!=my_mutex_unlock(&mutex)){
            pthread_exit(ret);
        }
        
        if(my_sem_post(&empty)){ // il y a une place libre en plus
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

    //Initialisation du buffer et des primitives d'attentes active
    if (init_buffer() !=0){
        printf("Error init_buffer\n");
        return -1;
    }

    //R??cup??ration du nombre de thread et nombre de cycle ?? effectuer
    int nbr_thread = atoi(argv[1]);
    int nbr_producer = nbr_thread/2;
    int nbr_consumer = (nbr_thread/2) + (nbr_thread%2);
    int nbr_cycle = atoi(argv[2]);

    
    pthread_t thread_producer[nbr_producer];
    pthread_t thread_consumer[nbr_consumer];

    int err;

    //Cr??ation des producteurs en s'assurant que le nombre de production ??
    //effectuer est correctement r??parti entre les threads.
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

    //Cr??ation des consommateurs en s'assurant que le nombre de consommation ??
    //effectuer est correctement r??parti entre les threads.
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

    //Attend que tout les producteurs effectuent leurs jobs.
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
    //Attend que tout les consommateurs effectuent leurs jobs.
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

    //Destruction du buffer
    if (destroy_buffer() != 0){
        printf("Error destroy_buffer \n");
        return -1;
    }
    return EXIT_SUCCESS;
}