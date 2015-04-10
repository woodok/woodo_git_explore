/*
 * prac_strtok.cpp
 *
 *  Created on: Apr 7, 2015
 *      Author: nubuntu
 */

#include <iostream>
#include <cstring>

using std::cin;
using std::cout;
using std::endl;

int main()
{
	char buf[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 0};
	cout << buf << endl;
/*
	char * pick = strtok(buf, "3");
	cout << "pick: " << pick << endl;
	cout << "buf: " << buf << endl;

	pick = strtok(NULL, "7");
	cout << "pick: " << pick << endl;
	cout << "buf: " << buf << endl;
*/
	char * pick = strtok(buf, 0);
	cout << "pick: " << pick << endl;
	cout << "buf: " << buf << endl;

	cout << "end of program " << endl;
	return 0;
}
