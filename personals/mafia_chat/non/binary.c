/*
 * binary.c
 *
 *  Created on: Mar 26, 2015
 *      Author: nubuntu
 */

#include <stdio.h>
#include <math.h>
#include <arpa/inet.h>

void print_binary(int arr[], int arrLen, int sizeoftype);
void print_binaryc(char * arr, int arrLen, int sizeoftype);

int main(void)
{
	int i;
	char carr[4] = "asdf";
	int iarr[3];
	int beiarr[3];
/*
	for(i=0; i<4; ++i)
		printf("%d ", carr[i]);
*/
	carr[0] = 1;
	carr[1] = 1;
	carr[2] = 1;
	carr[3] = 1;

	iarr[0] = 16;
	iarr[1] = 1;
	iarr[2] = 1024;

	beiarr[0] = htonl(iarr[0]);
	beiarr[1] = htonl(iarr[1]);
	beiarr[2] = htonl(iarr[2]);

	for(i=0; i<4; i++)
		printf("%c ", carr[i]);
	printf("\n");
	for(i=0; i<4; i++)
		printf("%d ", carr[i]);
	printf("\n");

	printf("binary in integer\n");
	print_binary((int*)carr, 4, sizeof(char));
	print_binary(iarr, 3, sizeof(int));

	printf("binary in character\n");
	print_binaryc(carr, 4, sizeof(char));
	print_binaryc((char*)iarr, 3, sizeof(int));

	printf("binary in character(big endian version)\n");
	print_binaryc((char*)beiarr, 3, sizeof(int));

	return 0;
}

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
