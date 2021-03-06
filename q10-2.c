#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>


sem_t sem;
int semVal;
pthread_mutex_t mut;
pthread_cond_t condC;
pthread_cond_t condA;

	
void utiliserPont(int type){
    
    if (type == 1){
		sem_wait(&sem);
		sem_getvalue(&sem, &semVal);
	}
    else{
		int i = 0;
		
		for(i=0; i<3; i++){
			sem_wait(&sem);
			sem_getvalue(&sem, &semVal);
		}
	}
}

void libererPont(int type){

    if (type == 1){
		sem_post(&sem);
		sem_getvalue(&sem, &semVal);
	}
    else{
		int i = 0;
		
		for(i=0; i<3; i++){
			sem_post(&sem);
			sem_getvalue(&sem, &semVal);
		}
    }
}


void* voiture(void* arg){

    printf("Voiture %d en attente d'un coté du pont !\n", (int)pthread_self());
    sleep(1);
    
    pthread_mutex_lock(&mut);
    
    if (semVal != 0){
    	pthread_cond_wait(&condA, &mut);
    	pthread_mutex_unlock(&mut);
		utiliserPont(1);
    	printf("Voiture %d utilise le pont !\n", (int)pthread_self());
    	sleep(3);
    	libererPont(1);
    }
    
    if (semVal == 3)
		pthread_cond_broadcast(&condC);
		
	
		
	printf("Voiture %d a fini d'utiliser le pont !\n\n", (int)pthread_self());
	sleep(1);
	
	pthread_exit(NULL);
}


void* camion(void* arg){

    printf("Camion %d en attente d'un coté du pont !\n", (int)pthread_self());
    sleep(1);
    
    pthread_mutex_lock(&mut);
    
    if(semVal != 0){
    
		pthread_cond_wait(&condC, &mut);
		utiliserPont(2);
		printf("Camion %d utilise le pont !\n", (int)pthread_self());
		sleep(3);
		libererPont(2);
		//pthread_cond_init(&condC, NULL);
	}
	
	pthread_mutex_unlock(&mut);
	
	if (semVal == 3)
		pthread_cond_broadcast(&condA);
    
    printf("Camion %d a fini d'utiliser le pont !\n\n", (int)pthread_self());
    sleep(1);
	
	pthread_exit(NULL);
}


int main(){

	pthread_t v1, v2, v3, v4;
	pthread_t c1, c2, c3, c4;

	sem_init(&sem, 0, 3);
	sem_getvalue(&sem, &semVal);
	pthread_mutex_init(&mut, NULL);
	pthread_cond_init(&condC, NULL);
	pthread_cond_init(&condA, NULL);
	
	pthread_create(&v1, NULL, voiture, NULL);
	pthread_create(&v2, NULL, voiture, NULL);
	pthread_create(&v3, NULL, voiture, NULL);
	pthread_create(&v4, NULL, voiture, NULL);
	
	pthread_create(&c1, NULL, camion, NULL);
	pthread_create(&c2, NULL, camion, NULL);
	pthread_create(&c3, NULL, camion, NULL);
	pthread_create(&c4, NULL, camion, NULL);
	
	sleep(3);
	
	pthread_cond_broadcast(&condC);
	
	pthread_join(v1, NULL);
	pthread_join(v2, NULL);
	pthread_join(v3, NULL);
	pthread_join(v4, NULL);
	
	pthread_join(c1, NULL);
	pthread_join(c2, NULL);
	pthread_join(c3, NULL);
	pthread_join(c4, NULL);
	
	printf("fin main\n");
	
	pthread_exit(NULL);
}
























