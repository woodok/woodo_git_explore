/*
 * prac_strstr.cpp
 *
 *  Created on: Apr 7, 2015
 *      Author: nubuntu
 */

#include <iostream>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;

int main(void)
{
	char buf[] = "0123456389";

	cout << "buf[]: " << buf << endl << endl;
/*	cout << "buf[10]: " << ((buf[5]==NULL)? "NULL" : &buf[5]) << endl;*/

	char * pick = strstr(buf, "3");
	cout << "buf[]: " << buf << endl;
	cout << "pick: " << pick << endl;

	pick = strstr(pick+1, "3");
	cout << "buf[]: " << buf << endl;
	cout << "pick: " << pick << endl;

//	pick = strstr(NULL, "3");

	cout << "end of program" << endl;

	return 0;
}
