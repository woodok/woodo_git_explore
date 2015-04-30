/*
 * memcpy_vector.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: nubuntu
 */

#include <iostream>
#include <vector>
#include <cstring>

#define MAX_BUF 1000

using std::cin;
using std::cout;
using std::endl;

char buf[MAX_BUF];

namespace PersonCosnt
{
	int NICKNAME_MAX_LENGHT = 16;
};

class Person
{
private:
	int id;
	char nickName[100];

public:

};

namespace RoomConst
{
	int TITLE_MAX_LENGTH = 256;
/*	namespace state
	{
		int WAIT = 0;
		int PLAYING = 1;
	}*/
	enum state {WAIT, PLAYING};

};

class Room
{
private:
	int roomId;
	char title[RoomConst::TITLE_MAX_LENGTH];
	int state;
	//rev 현재 참가 인원, 참가자 리스트

	static int roomCount;
public:
	Room()
	{

	}
	Room(char * _title)
	{
		roomId = roomCount++;
		strncpy(title, _title, RoomConst::TITLE_MAX_LENGTH);
		state = RoomConst::state::WAIT;
	}
};

int main(void)
{
	std::vector<Room> orig;
	std::vector<Room> dest;



	return 0;
}


