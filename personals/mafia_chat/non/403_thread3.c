/*
 * 403_thread3.c
 *
 *  Created on: Mar 30, 2015
 *      Author: nubuntu
 */

#define _REENTRANT

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * thread_summation(void * arg);
void * thread_test(void * arg);
void * thread_test2(void * arg);

int sum=1;

int main(int argc, char * argv[])
{
	pthread_t id_t1, id_t2;
	//int range1[] = {1, 5};
	//int range2[] = {6, 10};
	//int range1[] = {1, 10};
	//int range2[] = {2, 5};
	int range1[] = {5, 10};
	int range2[] = {0, 100};
	int ret1, ret2;

	/*
	pthread_create(&id_t1, NULL, thread_summation, (void *)range1);
	pthread_create(&id_t2, NULL, thread_summation, (void *)range2);
	*/
	/*
	pthread_create(&id_t1, NULL, thread_test, (void *)range1);
	pthread_create(&id_t2, NULL, thread_test, (void *)range2);
	*/
	pthread_create(&id_t1, NULL, thread_test2, (void *)range1);
	pthread_create(&id_t2, NULL, thread_test2, (void *)range2);
	/*
	printf("thread 1 join\n");
	pthread_join(id_t1, NULL);
	printf("thread 2 join\n");
	pthread_join(id_t2, NULL);
	*/
	printf("thread 1 join\n");
	pthread_join(id_t1, (void **)&ret1);	//? &ret1이면 void형 double pointer가 아니라 void형 pointer로 받아야하지 않나?
	printf("thread 2 join\n");
	pthread_join(id_t2, (void **)&ret2);

	printf("Thread 1 result : %d\n", ret1);
	printf("Thread 2 result : %d\n", ret2);

	printf("main process run\n");

	//printf("result : %d\n", sum);
	return 0;
}

void * thread_summation(void * arg)
{
	int start = ((int *)arg)[0];
	int end = ((int *)arg)[1];		//?

	while(start<=end)
	{
		sum += start;
		start++;
	}

	return NULL;
}

void * thread_test(void * arg)
{
	int i;
	int t_num = ((int *)arg)[0];
	int iter = ((int *)arg)[1];

	for(i=0; i<iter; ++i) {
		printf("thread %d running\n", t_num);
		sleep(1);
	}
	/*
	ret = (char*)malloc(sizeof(char)*50);
	fputf(ret, "Thread ");
	fputf(ret, (char)t_num);
	fputf(ret, " return\n");
	return (void *)ret;
	*/
	return NULL;
}

void * thread_test2(void * arg)
{
	int time = ((int*)arg)[0];
	int sumTo = ((int*)arg)[1];
	int i;
	int ret = 0;
	int id = sum++;

	printf("Thread %d begin.\n", id);
	for(i=0; i<time; i++) {
		printf("Thread %d sleeps\n", id);
		sleep(1);
	}
	for(i=0; i<sumTo; i++)
		ret += i;

	printf("Thread %d end & result : %d\n", id, ret);

	return (void *) ret;
}
