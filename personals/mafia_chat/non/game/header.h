/*
 * header.h
 *
 *  Created on: Apr 4, 2015
 *      Author: nubuntu
 */

#ifndef GAME_HEADER_H_
#define GAME_HEADER_H_

#include <iostream>
#include <vector>
#include <list>
#include <pthread.h>
#include <cstring>
#include "myheader.h"

using std::cin;
using std::cout;
using std::endl;

#define MAX_CLIENT 1024
#define MAX_WAITING_ROOM 128
#define MAX_PARTICIPANT 8	//rev class Room에 들어가는게 맞지 않나.?
#define MAX_TITLE 128		//rev class Room에 들어가는게 맞지 않나.?

class GameConst
{
	// 각종 const values

};

class GameMessage
{
	// 각종 const values

};

// 대기실에서 client 목록 확인 위해..
class Client
{
public:	//rev Client const(client status 등..) enum으로 선언
	const static enum {
		READY,
		NOTREADY,
		JOIN,
		NOTJOIN
	};
private:
	static int count = 0;
private:
	int id;
	int status;
	pthread_t pid;
public:
	Client();
	/*
	// accessor
	int get_id() const;
	int get_status() const;
	int get_pid() const;
	// mutator
	void set_id(int newId);
	void set_status(int newStatus);
	void set_pid(pthread_t newPid);
*/
};

class Room
{
public:	//rev WaitingRoom const(=status 등..) enum으로 선언
	const static enum {
		WAITING,
		PLAYING,


	};
private:
	int id;
	int status;
	char title[MAX_TITLE];
	std::vector<int> entry;
public:
	Room(int hostId);
	bool playerJoin(int newPlayerId);
	bool playerQuit(int quitPlayerId);
	// accessor
	int get_id() const;
	int get_status() const;
	const std::vector<int>& get_entry() const;
	// mutator
	void set_id(int newId);
	void set_status(int newStatus);



};


#endif /* GAME_HEADER_H_ */
