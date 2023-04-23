#include "codec.h"
#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
	char data[] = "my text to encrypt";
	int key = 12;
	long number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);
	printf("%ld", number_of_processors);
	//encrypt(data,key);
	printf("encripted data: %s\n",data);

	decrypt(data,key);
	printf("decripted data: %s\n",data);

	return 0;
}
