/*
 * test_arrSend_clnt.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: nubuntu
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX_BUF 1000

void error_handling(const char * message);

int main(int argc, char * argv[])
{
	int sock;
	struct sockaddr_in serv_adr;
	void buf[MAX_BUF];
	int count;

	if(argc != 3)
	{
		printf("Usage: %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("connect() error");
	else
		puts("connected...........");

	read(sock, &count, sizeof(int));
	read(sock, buf, MAX_BUF);

	for(int i=0; i<count; ++i)
		printf("%d ", ((int *)buf)[i]);

	close(sock);

	return 0;
}

void error_handling(const char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
