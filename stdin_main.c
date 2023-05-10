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
	
	struct data_stream* d = (struct data_stream*)args;

    // Cast the arguments back to their original types
    char* input = d->data;
    // Call the encrypt function
    encrypt(input, key);
	d->finished = 1;
    // Exit the thread
    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
	int number_of_processors = sysconf(_SC_NPROCESSORS_ONLN);
	FILE *fp;
	fp = fopen("output.txt", "w");
	printf("\nnumber of cores %d ", number_of_processors);

	pthread_t* threads = malloc(number_of_processors*sizeof(pthread_t));
	char thread_count = 0;
	char **inputs = malloc(number_of_processors * sizeof(char *));
	struct data_stream* data_s =(struct data_stream *) malloc(number_of_processors * sizeof(struct data_stream));
	for (int i = 0; i < number_of_processors; i++) {
		inputs[i] = malloc(1024 * sizeof(char));
	}
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
	data[0] = '\0';

	while ((c = getchar()) != EOF)
	{
	  counter++;
	  char a[1];
	  a[0] = c;
	  strcat(data, a);
	  if (counter == 1024){
		a[0] = '\0';
		strcat(data, a);
		strcpy(inputs[thread_count], data);

		data_s[thread_count].data = inputs[thread_count];
		data_s[thread_count].finished = 0;

		
		int rc = pthread_create(&threads[thread_count], NULL, encrypt_thread, (void *) &data_s[thread_count]);		
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
		for(int t = 0; t < number_of_processors; t++)
		{
			if(data_s[t].finished){
				fputs(data_s[t].data, fp);
				printf("encripted data: %s\n",data_s[t].data);
				//Todo: free this data!
			}
				
		}
		
		counter = 0;
		strcpy(data, "");// this will reset data string
	  }
	}
	
	if (counter > 0)
	{
		char lastData[counter];
		lastData[0] = '\0';
		strncat(lastData, data, counter);
		encrypt(lastData,key);
		fputs(lastData, fp);
		printf("encripted data:\n %s\n",lastData);
	}

	fclose(fp);
	
	for (int i = 0; i < number_of_processors; i++) {
    free(inputs[i]);
	}
	free(inputs);

	return 0;
}
