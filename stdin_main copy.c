#include "codec.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct thread_data
{
	char* data;
	int key;
};

void* encrypt_thread(void* arg)
{
	struct thread_data* data = (struct thread_data*)arg;
	encrypt(data->data, data->key);
	printf("encripted data: %s\n", data->data);
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
	    printf("usage: key < file \n");
	    printf("!! data more than 1024 char will be ignored !!\n");
	    return 0;
	}

	long number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);
	printf("\n%ld", number_of_processors);

	int key = atoi(argv[1]);
	printf("key is %i \n",key);

	char c;
	int counter = 0;
	int dest_size = 1024;
	char data[dest_size]; 

	pthread_t tid;
	struct thread_data tdata;

	while ((c = getchar()) != EOF)
	{
	  data[counter] = c;
	  counter++;

	  if (counter == 1024){
		tdata.data = strdup(data); // create a copy of the data buffer
		tdata.key = key;
		pthread_create(&tid, NULL, encrypt_thread, (void*)&tdata);
		counter = 0;
	  }
	}
	
	if (counter > 0)
	{
		char lastData[counter];
		lastData[0] = '\0';
		strncat(lastData, data, counter);
		tdata.data = strdup(lastData); // create a copy of the data buffer
		tdata.key = key;
		pthread_create(&tid, NULL, encrypt_thread, (void*)&tdata);
	}

	pthread_exit(NULL);
}
