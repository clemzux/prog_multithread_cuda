#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

void* salut(void* arg){

	pthread_exit(NULL);
}

int main(){

	int n;
	pthread_t id;
	
	for (n = 0; n<10000; n++)
		pthread_create(&id, NULL, salut, NULL);
	
	return 0;
}

