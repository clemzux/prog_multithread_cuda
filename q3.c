#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

pthread_mutex_t mut;

void* salut(void* arg){

	pthread_mutex_lock(&mut);

	printf("id1 : %d\n", (int)pthread_self());
	
	sleep(3);
	pthread_mutex_unlock(&mut);
	
	pthread_exit(NULL);
}

void* cava(void* arg){

	pthread_mutex_lock(&mut);

	printf("id2 : %d\n", (int)pthread_self());
	
	sleep(3);
	pthread_mutex_unlock(&mut);
	
	pthread_exit(NULL);
}

void* aurevoir(void* arg){

	pthread_mutex_lock(&mut);

	printf("id3 : %d\n", (int)pthread_self());
	
	sleep(3);
	pthread_mutex_unlock(&mut);
	
	pthread_exit(NULL);
}

int main(){

	pthread_t id1, id2, id3;

	pthread_mutex_init(&mut, NULL);
	
	pthread_mutex_lock(&mut);
	
	pthread_create(&id1, NULL, salut, NULL);
	pthread_create(&id2, NULL, cava, NULL);
	pthread_create(&id3, NULL, aurevoir, NULL);
	
	sleep(3);
	
	pthread_mutex_unlock(&mut);
	
	pthread_exit(NULL);
}
























