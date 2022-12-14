#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <semaphore.h>
#include <stdlib.h>
#include <ctype.h>

int nbr_reading = 2560;
int nbr_writing = 640;
int reading;
int writing;
int ecrire , lire;
int writecount, readcount;

pthread_mutex_t mutex_readcount;
pthread_mutex_t mutex_writecount;
pthread_mutex_t z;

sem_t wsem; 
sem_t rsem; 


void rw_datab(void){
    for (int i = 0; i < 10000; i++){
        continue;
    }
    return;
}

void *writer(void *write){
    for(int i = 0; i < writing; i++) {
        pthread_mutex_lock(&mutex_writecount);
        //section critique
        writecount++;
        if (writecount == 1){
            sem_wait(&rsem);
        }
        pthread_mutex_unlock(&mutex_writecount);
        sem_wait(&wsem);
        rw_datab();
        sem_post(&wsem);
        pthread_mutex_lock(&mutex_writecount);
        //section critique
        writecount--;
        if (writecount == 0){
            sem_post(&rsem);
        }
        pthread_mutex_unlock(&mutex_writecount);
    }
    return NULL;
}

void *reader(void *read){
    
    for(int i = 0; i < reading; i++){
        pthread_mutex_lock(&z);
        sem_wait(&rsem);
        pthread_mutex_lock(&mutex_readcount);
        readcount++;
        if (readcount==1){ 
            // arrivée du premier reader
            sem_wait(&wsem);
        }
        pthread_mutex_unlock(&mutex_readcount);
        sem_post(&rsem);
        pthread_mutex_unlock(&z);
        rw_datab();
        pthread_mutex_lock(&mutex_readcount);
        readcount--;
        if (readcount==0){ 
            sem_post(&wsem);
        }
        pthread_mutex_unlock(&mutex_readcount);
    }
    return NULL;
}


int main(int argc, char* argv[]) {
    int lire, ecrire;

    if(argc != 2) {printf("Arguments inssufisants"); return EXIT_SUCCESS; }

    int nbr_thread = atoi(argv[1]);
    lire = nbr_thread/2;
    ecrire = (nbr_thread/2);

    pthread_t threadreaders[lire], threadwriters[ecrire];

    //Initialisation mutex
    if(pthread_mutex_init(&mutex_readcount, NULL) !=0){printf("Erreur creation du reader mutex");}
    if(pthread_mutex_init(&mutex_writecount, NULL) !=0){printf("Erreur creation du writer mutex");}
    //Initialisation des semaphores
    if(sem_init(&wsem, 0, 1)!=0){printf("Erreur creation du reader semaphore");}
    if(sem_init(&rsem, 0, 1 !=0)){printf("Erreur creation du writer semaphore");}
   

    //creation des threads threadreaders et threadwriters
    reading = nbr_reading/lire;
    for(int i = 0; i < lire; i++){
        if((pthread_create(&threadreaders[i], NULL, reader, NULL) != 0)) {
            printf("Erreur creation du threadreaders");
        }
    }

    writing = nbr_writing/ecrire;
    for(int i = 0; i < ecrire ; i++){
        if((pthread_create(&threadwriters[i], NULL, writer, NULL) != 0)) {
            printf("Erreur creation du threadwriters");
        }
    }

    for(int i = 0; i < lire; i++){
        if((pthread_join(threadreaders[i], NULL) != 0)) {
            printf("Erreur pthread_join threadreaders");
        }
    }

    for(int i = 0; i < ecrire; i++){
        if((pthread_join(threadwriters[i], NULL) != 0)) {
            printf("Erreur pthread_join threadwriters");
        }
    }


    //destroy mutex
    if(pthread_mutex_destroy(&mutex_writecount)!= 0){printf("Desctrucion du mutex writer");}
    if(pthread_mutex_destroy(&mutex_readcount)!= 0){printf("Desctrucion dumutex reader");}
    //destroy semaphore
    if(sem_destroy(&wsem)!= 0){printf("Desctrucion du writing semaphore");}
    if(sem_destroy(&rsem)!= 0){printf("Desctrucion du reading semaphore");}

    return(EXIT_SUCCESS);
} 
