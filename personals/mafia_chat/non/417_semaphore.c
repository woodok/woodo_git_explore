/*
 * 417_semaphore.c
 *
 *  Created on: Apr 2, 2015
 *      Author: nubuntu
 */

#define _REENTRANT

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

void * read(void * arg);
void * accu(void * arg);
static sem_t sem_read;
static sem_t sem_accu;
static int num;

int main(int argc, char * argv[])
{
	pthread_t idT1, idT2;
	sem_init(&sem_read, 0, 1);
	sem_init(&sem_accu, 0, 0);

	pthread_create(&idT1, NULL, read, NULL);
	pthread_create(&idT2, NULL, accu, NULL);

	pthread_join(idT1, NULL);
	pthread_join(idT2, NULL);

	sem_destroy(&sem_read);
	sem_destroy(&sem_accu);

	return 0;
}

void * read(void * arg)
{
	int i;
	for(i=0; i<5; i++)
	{
		fputs("Input num: ", stdout);

		sem_wait(&sem_read);
		scanf("%d", &num);
		sem_post(&sem_accu);
	}
	return NULL;
}

void * accu(void * arg)
{
	int sum = 0, i;
	for(i=0; i<5; ++i)
	{
		sem_wait(&sem_accu);
		sum += num;
		sem_post(&sem_read);
	}
	printf("Result : %d\n", sum);
	return NULL;
}
