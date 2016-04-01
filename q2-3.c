#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

void* salut(void* arg){

	sleep(2);
	
	pthread_exit(pthread_self());
}

int main(){

	pthread_t id;
	void* idd = 0;
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	pthread_create(&id, &attr, salut, NULL);
	pthread_detach(id);
	pthread_join(id, &idd);
	
	printf("pere : id du thread fils : %d\n", (int)idd);
	
	pthread_exit(NULL);
}

