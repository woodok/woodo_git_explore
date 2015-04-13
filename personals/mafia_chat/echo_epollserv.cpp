/*
 * echo_epollserv.cpp
 *
 *  Created on: Apr 9, 2015
 *      Author: nubuntu
 */

#define D_REENTRANT

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <semaphore.h>		//? mutex를 쓰는게 나을까, semaphore를 쓰는게 나을까?

#define BUF_SIZE 100
#define EPOLL_SIZE 50

void error_handling(const char * buf);
void * catch_event(void *);
void * handle_event(void *);

struct epoll_event * ep_events;
int epfd, event_cnt;
static sem_t sem_catch, sem_handle;
int lstn_sock;

int main(int argc, char * argv[])
{
	struct sockaddr_in serv_adr;
	pthread_t tid_catch, tid_handle;

	struct epoll_event event;

	if(argc != 2) {
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}

	sem_init(&sem_catch, 0, 1);
	sem_init(&sem_handle, 0, 0);

	lstn_sock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));
	if( bind(lstn_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");

	if(listen(lstn_sock, 5) == -1)
		error_handling("listen() error");

	epfd = epoll_create(EPOLL_SIZE);
	ep_events = (epoll_event *)malloc(EPOLL_SIZE * sizeof(struct epoll_event));

	event.events = EPOLLIN;
	event.data.fd = lstn_sock;
	epoll_ctl(epfd, EPOLL_CTL_ADD, lstn_sock, &event);

	pthread_create(&tid_catch, NULL, catch_event, NULL);
	pthread_create(&tid_handle, NULL, handle_event, NULL);

	pthread_join(tid_catch, NULL);
	pthread_join(tid_handle, NULL);

/*	//rev thread 안으로 옮겨질 부분
	while(1)
	{
		event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
		if(event_cnt == -1)
		{
			puts("epoll_wait() error");
			break;
		}

		for(i=0; i<event_cnt; ++i)
		{
			if(ep_events[i].data.fd == lstn_sock)
			{
				adr_sz = sizeof(clnt_adr);
				clnt_sock = accept(lstn_sock, (struct sockaddr *)&clnt_adr, &adr_sz);
				event.events = EPOLLIN;
				event.data.fd = clnt_sock;
				epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);
				printf("connected client: %d\n", clnt_sock);
			}
			else
			{
				str_len = read(clnt_sock, buf, BUF_SIZE);
				if(str_len == 0)
				{
					epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
					close(ep_events[i].data.fd);
					printf("close client: %d\n", ep_events[i].data.fd);
				}
				else
				{
					write(ep_events[i].data.fd, buf, str_len);
				}
			}
		}
	}
*/

	sem_destroy(&sem_catch);
	sem_destroy(&sem_handle);

	close(lstn_sock);
	close(epfd);

	printf("Good bye.\n");

	return 0;
}

void error_handling(const char * buf)
{
	fputs(buf, stderr);
	fputc('\n', stderr);
	exit(1);
}

void * catch_event(void * arg)
{
	int i;

	while(1)
	{
		sem_wait(&sem_catch);
		event_cnt = epoll_wait(epfd, ep_events, EPOLL_SIZE, -1);
		if(event_cnt == -1)
		{
			puts("epoll_wait() error");
			break;
		}
		sem_post(&sem_handle);
	}

}
void * handle_event(void * arg)
{
	int i, str_len;
	socklen_t adr_sz;
	sockaddr_in clnt_adr;
	char buf[BUF_SIZE];
	int clnt_sock;
	struct epoll_event event;

	while(1)
	{
		sem_wait(&sem_handle);
		for(i=0; i<event_cnt; ++i)
		{
			if(ep_events[i].data.fd == lstn_sock)
			{
				adr_sz = sizeof(clnt_adr);
				clnt_sock = accept(lstn_sock, (struct sockaddr *)&clnt_adr, &adr_sz);
				event.events = EPOLLIN;
				event.data.fd = clnt_sock;
				epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);
				printf("connected client: %d\n", clnt_sock);
			}
			else
			{
				str_len = read(clnt_sock, buf, BUF_SIZE);
				if(str_len == 0)
				{
					epoll_ctl(epfd, EPOLL_CTL_DEL, ep_events[i].data.fd, NULL);
					close(ep_events[i].data.fd);
					printf("close client: %d\n", ep_events[i].data.fd);
				}
				else
				{
					write(ep_events[i].data.fd, buf, str_len);
				}
			}
		}
		sem_post(&sem_catch);
	}
}
