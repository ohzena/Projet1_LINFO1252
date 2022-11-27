#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <unistd.h>

#define CYCLES 100000

int PHILO;
pthread_mutex_t *baguette;

void manger(int index){
}

//le thread rentre dans philosophe avec un index	
void* philosophe(void* arg){
    int count = 0;
    int *index = (int *) arg;
    int left = *index;
    int right = (left + 1) % PHILO;
    
    while(count < CYCLES){
        //si gaucher pour eviter les deadlock
	    if(left<right){
            pthread_mutex_lock(&baguette[left]);
            pthread_mutex_lock(&baguette[right]);
		} else{
            pthread_mutex_lock(&baguette[right]);
            pthread_mutex_lock(&baguette[left]);
        }
	    manger(*index);
	    count ++;
        pthread_mutex_unlock(&baguette[left]);
        pthread_mutex_unlock(&baguette[right]);
	}
	return (NULL);
}


int main (int argc, char *argv[]){
    if(argc != 2) {
        printf("Il y a le mauvais nombre d'argument\n");
        return EXIT_FAILURE;
    }

    PHILO = atoi(argv[1]);
    if (PHILO <= 1) return EXIT_SUCCESS;

    int index[PHILO];
    pthread_t phil[PHILO];
    baguette = malloc(PHILO * sizeof(pthread_mutex_t));


    if(PHILO == 1) {
        for(int i = 0; i< CYCLES; i++){manger(1);}
        return 1;
    }
    

    //initiation mutex
    for(int i = 0; i < PHILO; i++){
        if(pthread_mutex_init(&(baguette[i]), NULL) != 0) {
             printf("Erreur initiation du mutex");
        }
    }
    
    //creation du thread
    for(int i = 0; i < PHILO; i++){
        index[i] = i;
        if(pthread_create(&(phil[i]), NULL, &philosophe, &(index[i])) != 0) {
             printf("Erreur creation du thread");
        }
    }
    
    //joindre les thread
    for(int i = 0; i < PHILO; i++){
        if( pthread_join(phil[i], NULL) !=0) {
             printf("Erreur du creation du pthread_join");
        }
    }

    //destruction du mutex
    for (int i = 0; i < PHILO; i++){
        if( pthread_mutex_destroy(&(baguette[i])) != 0) {
             printf("Erreur destruction du pthread_mutex_destroy");
        }
    }
    
    free(baguette);
    return EXIT_SUCCESS;
}
    
