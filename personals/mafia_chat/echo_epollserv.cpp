/*
 * echo_epollserv.cpp
 *
 *  Created on: Apr 9, 2015
 *      Author: nubuntu
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define BUF_SIZE 100
#define EPOLL_SIZE 50

void error_handling(char * buf);

int main(int argc, char * argv[])
{
	int lstn_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t adr_sz;
	int str_len, i;
	char buf[BUF_SIZE];

	struct epoll_event * ep_events;
	struct epoll_event event;
	int epfd, event_cnt;

	if(argc != 2) {
		printf("Usage: %s <port>\n", argv[0]);
		exit(1);
	}

	lstn_sock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htonl(atoi(argv[1]));
	if( bind(lstn_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");

	if(listen(lstn_sock, 5) == -1)
		error_handling("listen() error");

	epfd = epoll_create(EPOLL_SIZE);
	ep_events = (epoll_event *)malloc(EPOLL_SIZE * sizeof(struct epoll_event));

	event.events = EPOLLIN;
	event.data.fd = lstn_sock;
	epoll_ctl(epfd, EPOLL_CTL_ADD, lstn_sock, &event);

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

	close(lstn_sock);
	close(epfd);

	return 0;
}

void error_handling(char * buf)
{
	fputs(buf, stderr);
	fputc('\n', stderr);
	exit(1);
}





