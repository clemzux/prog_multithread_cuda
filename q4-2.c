#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>


pthread_mutex_t mut;
pthread_cond_t cond;
int var = 1;


void* attente(void* arg){

    pthread_mutex_lock(&mut);
	
	if(var == 1){
	    pthread_cond_wait(&cond, &mut);
		printf("je suis le thread : %d\n", (int)pthread_self());
	}
	
	printf("fin thread\n");
	
	pthread_mutex_unlock(&mut);
	
	pthread_exit(NULL);
}

int main(){

	pthread_t id1, id2, id3, id4;

	pthread_mutex_init(&mut, NULL);
	pthread_cond_init(&cond, NULL);
	
	pthread_create(&id1, NULL, attente, NULL);
	pthread_create(&id2, NULL, attente, NULL);
	pthread_create(&id3, NULL, attente, NULL);
	pthread_create(&id4, NULL, attente, NULL);
	
	sleep(3);
	
	pthread_cond_broadcast(&cond);
	
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	pthread_join(id3, NULL);
	pthread_join(id4, NULL);
	
	printf("fin main\n");
	
	pthread_exit(NULL);
}
























