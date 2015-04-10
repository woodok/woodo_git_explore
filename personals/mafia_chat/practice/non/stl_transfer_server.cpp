/*
 * stl_transfer_server.cpp
 *
 *  Created on: Apr 7, 2015
 *      Author: nubuntu
 */

#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX_CLIENT 8

using std::cin;
using std::cout;
using std::endl;

void * handle_clnt(void *);
template <typename T>
void send_vector(std::vector<T>& vec);
void error_handling(char * message);		//? param를 string으로 바꾸면..?

int clnt_cnt = 0;
int clnt_socks[MAX_CLIENT];
pthread_mutex_t mutx;

std::vector<int> gvec;

int main(int argc, char * argv[])
{
	int lstn_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;	//? struct 키워드 없어도 될까..?
//	int clnt_adr_sz;		//?
	socklen_t clnt_adr_sz;
//	pthread_t t_id;
	int vec_size;

	if(argc != 2)
	{
		cout << argv[0] << " <port>"<<endl;
		exit(1);
	}

//	pthread_mutex_init(&mutx, NULL);
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

	gvec.reserve(16);
	cout << "Size: "<<gvec.size() << ", Capacity: "<<gvec.capacity()<<endl;

	for(int i=0; i<10; ++i)
		gvec.push_back(i);
	cout << "Size: "<<gvec.size() << ", Capacity: "<<gvec.capacity()<<endl;
	gvec.shrink_to_fit();
	cout << "Size: "<<gvec.size() << ", Capacity: "<<gvec.capacity()<<endl;

	/* multithread 방식
	while(1)
	{
		clnt_adr_sz = sizeof(clnt_adr);
		clnt_sock = accept(lstn_sock, (struct sockaddr *)&clnt_adr, &clnt_adr_sz);
		if(clnt_sock == -1)
			error_handling("accept() error");

		pthread_mutex_lock(&mutx);
		clnt_socks[clnt_cnt++] = clnt_sock;
		pthread_mutex_unlock(&mutx);

		pthread_create(&t_id, NULL, handle_clnt, (void *)&clnt_sock);
		pthread_detach(t_id);
		cout<<"Connected client IP : " << inet_ntoa(clnt_adr.sin_addr) << endl;
	}
	close(lstn_sock);
	*/

	vec_size = gvec.size();



	return 0;
}
/* multithread 방식
void * handle_clnt(void * arg)
{
	int clnt_sock = *((int *)arg);
	int strlen;
	while(strlen = read()
*/




