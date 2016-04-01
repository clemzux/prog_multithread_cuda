#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <errno.h>
#include <pthread.h>

int cpt = 0;

pthread_mutex_t mut;
pthread_cond_t cond;

int var = 1;

struct timeval tv;
struct timespec ts;


void* increm1(void* arg){

	int i = 0;

	for ( i = 0; i < 4; i++){
	
	    sleep(1);
	
		pthread_mutex_lock(&mut);
		
		cpt++;
		printf("compteur : %d\n", cpt);
		
		if (cpt == 3){
			//pthread_mutex_unlock(&mut);
			pthread_cond_signal(&cond);
		}
			
		pthread_mutex_unlock(&mut);
	}
	
	pthread_exit(NULL);
}


void* increm2(void* arg){

	int j = 0;
	
	for ( j = 0; j < 4; j++){
	
	    sleep(1);
	
		pthread_mutex_lock(&mut);
		
		cpt++;
		printf("compteur : %d\n", cpt);
		
		if (cpt == 3)
			pthread_cond_signal(&cond);
		
		pthread_mutex_unlock(&mut);
	}
	
	pthread_exit(NULL);
}


void* attente(void* arg){

	sleep(0.5);

	pthread_mutex_lock(&mut);
	
	if(var == 1){
	    pthread_cond_timedwait(&cond, &mut, &ts);
    	printf("On a atteint 3\n");
    }
	
	pthread_mutex_unlock(&mut);
	
	pthread_exit(NULL);
}


int main(){

	gettimeofday(&tv, NULL);
	ts.tv_sec = tv.tv_sec + 4;
	ts.tv_nsec = 3;

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
























