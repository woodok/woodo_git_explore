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
#include "myheader.h"

#define MAX_BUF 1000

void error_handling(const char * message);

int main(int argc, char * argv[])
{
	int sock;
	struct sockaddr_in serv_adr;
	char buf[MAX_BUF];
	int count;
	int totallen, recvlen;

	memset(buf, 0, MAX_BUF);

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
	totallen = 0;
	while(totallen < count*sizeof(int))
	{
		recvlen = read(sock, &buf, MAX_BUF);
		totallen += recvlen;
	}

	for(int i=0; i<count; ++i)
		printf("%d ", ((int *)buf)[i]);
	printf("\n");

	print_binary((int*)&buf, count, sizeof(int));
	print_binaryc((char *)&buf, count, sizeof(int));

	close(sock);

	return 0;
}

void error_handling(const char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
