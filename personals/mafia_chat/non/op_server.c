/*
 * op_server.c
 *
 *  Created on: Mar 26, 2015
 *      Author: nubuntu
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "myheader.h"

#define BUF_SIZE 1024
#define OPSZ 4

void error_handling(char * message);
int calculate(int opnum, int opnds[], char oprator);

int main(int argc, char * argv[])
{
	int serv_sock, clnt_sock;
	char opinfo[BUF_SIZE];
	int result, opnd_cnt, i;
	int recv_cnt, recv_len;
	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;

	// variable for debugging
	int idx;
	int * iarr;


	if(argc != 2) {
		printf("Usage : %s <port>\n",argv[0]);
		exit(1);
	}

	printf("socket() is called..\n");
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	printf("bind() is called..\n");
	if(bind(serv_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr))==-1)
		error_handling("bind() error");

	printf("listen() is called..\n");
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");

	clnt_adr_sz = sizeof(clnt_adr);

	for(i = 0; i<5; ++i)
	{
		opnd_cnt = 0;
		clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);
		printf("%d client connected..\n", i+1);
		read(clnt_sock, &opnd_cnt, 1);

		printf("while()\n");
		recv_len = 0;
		while((opnd_cnt * OPSZ +1)>recv_len) {
			recv_cnt = read(clnt_sock, &opinfo[recv_len], BUF_SIZE - 1);
			recv_len += recv_cnt;
		}

		// debug
		iarr = (int *)opinfo;
		print_binary(iarr, opnd_cnt, sizeof(int));
		for(idx = 0; idx<opnd_cnt; ++idx)
			printf("opinfo[%d] : %d\n", idx, iarr[idx]);

		//result = calculate(opnd_cnt, (int*)opinfo, opinfo[opnd_cnt * OPSZ]);
		result = calculate(opnd_cnt, (int*)opinfo, opinfo[recv_len-1]);
		write(clnt_sock, (char *)&result, sizeof(result));
		close(clnt_sock);
		printf("client disconnected\n");
	}
	close(serv_sock);
	return 0;
}

int calculate(int opnum, int opnds[], char op)
{
	int result = opnds[0], i;
	printf("opnum = %d, op = %c \nopnds[0] = %d\n", opnum, op, opnds[0]);

	switch(op)
	{
	case '+':
		for(i=1; i<opnum; i++) {
			printf("opnds[%d] = %d\n", i, opnds[i]);
			result += opnds[i];
		}
		break;
	case '-':
		for(i=1; i<opnum; i++) {
			printf("opnds[%d] = %d\n", i, opnds[i]);
			result -= opnds[i];
		}
		break;
	case '*':
		for(i=1; i<opnum; i++) {
			printf("opnds[%d] = %d\n", i, opnds[i]);
			result *= opnds[i];
		}
		break;
	}
	printf("result = %d\n", result);
	return result;
}

void error_handling(char * message)
{
	fputs(message, stderr);
	exit(1);
}
