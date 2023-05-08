#include "codec.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


int key = 0;
struct data_stream
{
	char* data;
	char finished;
};


// The function that each thread will execute
void *encrypt_thread(void *args) {
    // Cast the arguments back to their original types
    char* input = (char*)args;
    // Call the encrypt function
    encrypt(input, key);

    // Exit the thread
    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
	int number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);

	printf("\n%d", number_of_processors);

	pthread_t* threads = malloc(number_of_processors*sizeof(pthread_t));
	char thread_count = 0;
	char *inputs = malloc(number_of_processors*sizeof(char)*1024);

	if (argc != 2)
	{
	    printf("usage: key < file \n");
	    printf("!! data more than 1024 char will be ignored !!\n");
	    return 0;
	}


	key = atoi(argv[1]);
	printf("key is %i \n",key);

	char c;
	int counter = 0;
	int dest_size = 1024;
	char data[dest_size]; 
	

	while ((c = getchar()) != EOF)
	{
	  data[counter] = c;
	  counter++;

	  if (counter == 1024){
		inputs[thread_count] = data;
		//open new thread
		int rc = pthread_create(&threads[thread_count], NULL, encrypt_thread, (void *) &inputs[thread_count]);
		if(thread_count >= 1)
			pthread_join(threads[thread_count - 1], NULL);

        if (rc)
        {
            printf("Error: unable to create thread %d, return code %d\n", thread_count, rc);
            return -1;
        }
		if(thread_count >= number_of_processors)
		{
			thread_count = 0;
		}else
			thread_count++;
		// encrypt(data,key);
		printf("encripted data: %s\n",data);
		counter = 0;
	  }
	}
	
	if (counter > 0)
	{
		char lastData[counter];
		lastData[0] = '\0';
		strncat(lastData, data, counter);
		encrypt(lastData,key);
		printf("encripted data:\n %s\n",lastData);
	}

	return 0;
}
