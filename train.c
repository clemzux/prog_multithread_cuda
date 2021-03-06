
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>


/* Les villes */
#define A 0
#define B 1
#define C 2
#define D 3


/* var globales */
pthread_mutex_t AB, BC, BD;


/* Code des threads */
void* train_de_A_vers_C(void* arg);
void* train_de_D_vers_A(void* arg);
void attendre(double max);


/* Moniteur : gestion du chemin de fer  */
void utiliser_le_segment(int vd, int va)
{

    if(vd == 0 && va == 1)
        pthread_mutex_lock(&AB);
    if(vd == 1 && va == 2)
        pthread_mutex_lock(&BC);
    if(vd == 1 && va == 3)
        pthread_mutex_lock(&BD);
}


void liberer_le_segment(int vd, int va)
{

    if(vd == 1 && va == 3)
        pthread_mutex_unlock(&BD);
    if(vd == 1 && va == 2)
        pthread_mutex_unlock(&BC);
    if(vd == 0 && va == 1)
        pthread_mutex_unlock(&AB);
}


int main(int argc, char* argv[])
{

    pthread_t t1, t2, t3, t4, t5, t6, t7, t8, t9;
    
    pthread_mutex_init(&AB, NULL);
    pthread_mutex_init(&BC, NULL);
    pthread_mutex_init(&BD, NULL);
    
    pthread_create(&t1,NULL, train_de_A_vers_C, NULL);
    pthread_create(&t2,NULL, train_de_D_vers_A, NULL);
    pthread_create(&t3,NULL, train_de_A_vers_C, NULL);
    pthread_create(&t4,NULL, train_de_D_vers_A, NULL);
    pthread_create(&t5,NULL, train_de_A_vers_C, NULL);
    pthread_create(&t6,NULL, train_de_D_vers_A, NULL);
    pthread_create(&t7,NULL, train_de_A_vers_C, NULL);
    pthread_create(&t8,NULL, train_de_D_vers_A, NULL);
    pthread_create(&t9,NULL, train_de_A_vers_C, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);
    pthread_join(t7, NULL);
    pthread_join(t8, NULL);
    pthread_join(t9, NULL);

	printf("fin du programme trains !\n");
	
	pthread_exit(NULL);
}


void* train_de_A_vers_C(void* arg)
{
	utiliser_le_segment(A, B);
	printf("Train %d : utilise segment AB \n", (int)pthread_self());
	attendre(6);
	liberer_le_segment(A, B);

	utiliser_le_segment(B, C);
	printf("Train %d : utilise segment BC \n", (int)pthread_self());
	attendre(6);
	liberer_le_segment(B, C);

	pthread_exit(NULL);
}

void* train_de_D_vers_A(void* arg)
{
	utiliser_le_segment(B, D);
	printf("Train %d : utilise segment DB \n", (int)pthread_self());
	attendre(5);
	liberer_le_segment(B, D);

	utiliser_le_segment(A, B);
	printf("Train %d : utilise segment BA \n", (int)pthread_self());
	attendre(5);
	liberer_le_segment(A, B);

	pthread_exit(NULL);
}


int tirage_aleatoire(double max)
{
        int j=(int) (max*rand()/(RAND_MAX+1.0));
        if(j<1)
                j=1;
        return j;
}


void attendre(double max)
{
        struct timespec delai;

        delai.tv_sec=tirage_aleatoire(max);
        delai.tv_nsec=0;
        nanosleep(&delai,NULL);
}

























