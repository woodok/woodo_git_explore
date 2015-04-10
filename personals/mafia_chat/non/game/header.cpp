/*
 * header.cpp
 *
 *  Created on: Apr 4, 2015
 *      Author: nubuntu
 */

#include "header.h"

Client::Client()
{
	id = count++;
	status = Client::NOTJOIN;
	pid = -1;		//? pid default를 어떻게 줘야할까?
};
