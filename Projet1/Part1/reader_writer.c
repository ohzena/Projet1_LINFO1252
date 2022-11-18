#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

int reading = 2560;
int writing = 640;

int write, read;
int writecount, readcount;

pthread_mutex_t mutex_readcount;
pthread_mutex_t mutex_writecount;

sem_t wsem; 
sem_t resm; 

void rw_datab(void){
    while(rand() > RAND_MAX/10000){
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
    return NULL
}

void *reader(void *read){
    for(int i=0; i<reading; i++){
        pthread_mutex_lock(&z);
        sem_wait(&resm);
        pthread_mutex_lock(&mutex_readcount);
        readcount++;
        if (readcount==1){ 
            // arrivée du premier reader
            sem_wait(&wsem);
        }
        pthread_mutex_unlock(&mutex_readcount);
        sem_post(&rsem);
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
    write = 1;
    read = 1;

    if(argc != 3) {return EXIT_FAILURE;}

    
//    int arg_read = sscanf(argv[1], "%d", &read);
//    int arg_write = sscanf(argv[2], "%d", &write);
//   writercount = write;
//    readercount = read;
//    if(write == 0){
//        for (int i = 0; i < reading;i++){rw_datab();}
//        for(int i = 0; i < writing;i++){rw_datab();}
//        return 0;
//    }



    //Initialisation mutex
    if(pthread_mutex_init(&mutex_readcount, NULL) !=0){printf("Erreur creation du reader mutex");}
    if(pthread_mutex_init(&mutex_writecount, NULL) !=0){printf("Erreur creation du writer mutex");}
    //Initialisation des semaphores
    if(sem_init(&wsem, 0, 1)!=0){printf("Erreur creation du reader semaphore");}
    if(sem_init(&rsem, 0, 1) !=0){printf("Erreur creation du writer semaphore");}


    //creation des threads threadreaders et threadwriters
    pthread_t threadreaders[read], threadwriters[write];

    for(int i = 0; i < read; i++){
        if((pthread_create(&threadreaders[i], NULL, (void*)reader, NULL) != 0)) {
            printf("Erreur creation du threadreaders");
        }
    }

    for(int i = 0; i < write; i++){
        if((pthread_create(&threadwriters[i], NULL, (void*)writer, NULL) != 0)) {
            printf("Erreur creation du threadwriters");
        }
    }

    for(int i = 0; i < read; i++){
        if((pthread_join(threadreaders[i], NULL) != 0)) {
            printf("Erreur pthread_join threadreaders");
        }
    }

    for(int i = 0; i < write; i++){
        if((pthread_join(threadwriters[i], NULL) != 0)) {
            printf("Erreur pthread_join threadwriters");
        }
    }


    //destroy mutex
    if(pthread_mutex_destroy(&mutex_writecount)!= 0){printf("Desctrucion du mutex writer")};
    if(pthread_mutex_destroy(&mutex_readcount)!= 0){printf("Desctrucion dumutex reader")};
    //destroy semaphore
    if(sem_destroy(&wsem!= 0){printf("Desctrucion du writing semaphore")};
    if(sem_destroy(&rsem)!= 0){printf("Desctrucion du reading semaphore")};

    return(EXIT_SUCCESS);
} 


















