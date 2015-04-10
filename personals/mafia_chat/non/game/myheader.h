/*
 * myheader.h
 *
 *  Created on: Mar 27, 2015
 *      Author: nubuntu
 */

#ifndef MYHEADER_H_
#define MYHEADER_H_

#include <stdio.h>
//#include <stdlib.h>
#include <arpa/inet.h>

// debug
void print_binary(int * arr, int arrLen, int sizeoftype)
{
	int i, j;

	int BITS_IN_BYTE = 8 * sizeoftype;
	//arrLen /= (sizeof(int) / sizeoftype);

	for(i=0; i<arrLen; ++i) {
		for(j=BITS_IN_BYTE-1; j>=0; --j)
			printf("%d", (arr[i] & (1<<j))>>j);
		printf(" ");
	}
	printf("\n");
}

void print_binaryc(char * arr, int arrLen, int sizeoftype)
{
	int i, j;

	int BITS_IN_BYTE = 8;
	arrLen *= sizeoftype;

	for(i=0; i<arrLen; ++i) {
		for(j=BITS_IN_BYTE-1; j>=0; --j)
			printf("%d", (arr[i] & (1<<j))>>j);
		printf(" ");
	}
	printf("\n");
}


#endif /* MYHEADER_H_ */
