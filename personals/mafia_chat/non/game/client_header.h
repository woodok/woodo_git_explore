/*
 * client_header.h
 *
 *  Created on: Apr 4, 2015
 *      Author: nubuntu
 */

#ifndef GAME_CLIENT_HEADER_H_
#define GAME_CLIENT_HEADER_H_

#include "header.h"

using std::cin;
using std::cout;
using std::endl;

void inLobbyDisplay();
void inLobbySelector();
void inRoomDisplay();
void inRoomSelector();

void * inputThread(void *);
void * outputThread(void *);


#endif /* GAME_CLIENT_HEADER_H_ */
