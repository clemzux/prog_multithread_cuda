#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>


pthread_mutex_t mut;
pthread_cond_t cond;

int nb;


void* lectureNb(void* arg){

	printf("Entrez un nombre a convertir :\n");
	scanf("%d\n", &scanf);
	
	pthread_exit(NULL);
}


int main(){

	pthread_t t1, t2, t3, t4, t5, t6, t7, t8;

	pthread_mutex_init(&mut, NULL);
	pthread_cond_init(&condC, NULL);
	
	pthread_create(&t1, NULL, voiture, NULL);
	pthread_create(&t2, NULL, voiture, NULL);
	pthread_create(&t3, NULL, voiture, NULL);
	pthread_create(&t4, NULL, voiture, NULL);
	pthread_create(&t5, NULL, camion, NULL);
	pthread_create(&t6, NULL, camion, NULL);
	pthread_create(&t7, NULL, camion, NULL);
	pthread_create(&t8, NULL, camion, NULL);
	
	sleep(3);
	
	pthread_cond_broadcast(&condC);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	pthread_join(t5, NULL);
	pthread_join(t6, NULL);
	pthread_join(t7, NULL);
	pthread_join(t8, NULL);
	
	printf("fin main\n");
	
	pthread_exit(NULL);
}
























