/*
 * vec.cpp
 *
 *  Created on: Apr 7, 2015
 *      Author: nubuntu
 */

#include <iostream>
#include <vector>
#include <iterator>

using std::cin;
using std::cout;
using std::endl;

std::vector<int> gvec;

void vec_add(std::vector<int>& vec);

int main(void)
{
	std::vector<int> lvec;

	vec_add(gvec);
	vec_add(lvec);

	copy(gvec.cbegin(), gvec.cend(), std::ostream_iterator<int>(cout, " "));
	copy(lvec.cbegin(), lvec.cend(), std::ostream_iterator<int>(cout, " "));

	return 0;
}

void vec_add(std::vector<int>& vec)
{
	for(int i=0; i<5; ++i)
		vec.push_back(i);
}




