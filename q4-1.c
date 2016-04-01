#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

int cpt = 0;

pthread_mutex_t mut;
pthread_cond_t cond;


void* increm1(void* arg){

	int i = 0;

	for ( i = 0; i < 4; i++){
	
		pthread_mutex_lock(&mut);
		
		cpt++;
		printf("compteur : %d\n", cpt);
		
		if (cpt == 3)
			pthread_cond_signal(&cond);
			
		sleep(3);
			
		pthread_mutex_unlock(&mut);
	}
	
	pthread_exit(NULL);
}


void* increm2(void* arg){

	int j = 0;
	
	for ( j = 0; j < 4; j++){
	
		pthread_mutex_lock(&mut);
		
		cpt++;
		printf("compteur : %d\n", cpt);
		
		if (cpt == 3)
			pthread_cond_signal(&cond);
			
		//sleep(3);
		
		pthread_mutex_unlock(&mut);
	}
	
	pthread_exit(NULL);
}


void* attente(void* arg){

	//pthread_mutex_lock(&mut);
	
	pthread_cond_wait(&cond, &mut);
	printf("On a atteint 3\n");
	
	//pthread_mutex_unlock(&mut);
	
	pthread_exit(NULL);
}


int main(){

	pthread_t id1, id2, id3;

	pthread_mutex_init(&mut, NULL);
	pthread_cond_init(&cond, NULL);
	
	pthread_mutex_lock(&mut);
	
	pthread_create(&id1, NULL, increm1, NULL);
	pthread_create(&id2, NULL, increm2, NULL);
	pthread_create(&id3, NULL, attente, NULL);
	
	pthread_mutex_unlock(&mut);
	
	pthread_exit(NULL);
}
























