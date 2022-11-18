#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>
#include <unistd.h>

#define CYCLES 1000000

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
		}
        else{
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
    if(argc != 2) {return EXIT_FAILURE;}

    PHILO = 8;
    if(argc == 2){
        if(atoi(argv[1])>0){
                PHILO = atoi(argv[1]);
        }
    }
    
    int index[PHILO];
    pthread_t philosophe[PHILO];
    baguette = malloc(PHILO * sizeof(pthread_mutex_t));


    if(PHILO == 1) {
        for(int i = 0; i< CYCLES; i++){manger(1);}
        return 1;
    }
    
    for(int i = 0; i < PHILO; i++){
        if(pthread_mutex_init(&(baguette[i]), 1) != 0) {
             printf("Erreur initiation du mutex");
        }
    }
    
    for(int i = 0; i < PHILO; i++){
        index[i] = i;
        if(pthread_create(&(philosophe[i]), NULL, &philosophe, &(index[i])) != 0) {
             printf("Erreur creation du thread");
        }
    }
    
    for(int i = 0; i < PHILO; i++){
        if( pthread_join(philosophe[i], NULL) !=0) {
             printf("Erreur du creation du pthread_join");
        }
    }
    
    for (int i = 0; i < PHILO; i++){
        if( pthread_mutex_destroy(&(baguette[i]), NULL, &philosophe, &(index[i])) != 0) {
             printf("Erreur destruction du pthread_mutex_destroy");
        }
    }
    
    free(baguette);
    free(index);
    
    return 0;
}
    

