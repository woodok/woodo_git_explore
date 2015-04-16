/*
 * test_arrSend_serv.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: nubuntu
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <cmath>
#include "myheader.h"

#define COUNT 5

using std::cout;
using std::cin;
using std::endl;

void error_handling(const char * message);

int main(int argc, char * argv[])
{
	sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;
	int lstn_sock, clnt_sock;
	int count = COUNT;
	int buf[COUNT];
	char * bufc;

	if(argc != 2)
	{
		std::cout<< "Usage: " << argv[0] << " <port>" << endl;
		exit(1);
	}

	cout << "Server started successfully" << endl;

	cout << "Put array length: ";
	cin >> count;
	bufc = new char[sizeof(int) * count];
	for(int i=0; i<count; ++i)
		((int*)bufc)[i] = pow(2, i);
	for(int i=0; i<count; ++i)
		cout << ((int*)bufc)[i] << ' ';
	cout << endl;
	print_binary((int *)bufc, count, sizeof(int));
	print_binaryc(bufc, count, sizeof(int));
/*
	for(int i=0; i<count; ++i)
		buf[i] = pow(2, i);

	for(int i=0; i<count; ++i)
		cout << buf[i] << ' ';
	cout << endl;
	print_binary(buf, count, sizeof(int));
*/
	lstn_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(lstn_sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if(bind(lstn_sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");
	if(listen(lstn_sock, 5) == -1)
		error_handling("listen() error");

	clnt_adr_sz = sizeof(clnt_adr);
	clnt_sock = accept(lstn_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);

	write(clnt_sock, &count, sizeof(int));
	write(clnt_sock, bufc, sizeof(int) * count);
/*	write(clnt_sock, &buf, sizeof(int) * count);	*/

	cout << "Sending completed. Server closed..." << endl;

	delete[] bufc;

	close(lstn_sock);
	close(clnt_sock);

	return 0;
}

void error_handling(const char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}



