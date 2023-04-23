#include <stdio.h>
#include <pthread.h>

// A function that will run in a new thread
void *say_hello(void *name) {
    printf("Hello %s\n", (char *)name);
    return NULL;
}

int main() {
    pthread_t thread; // A variable to store the thread ID
    char *name = "World"; // A name to pass to the function
    int status; // A variable to store the status of the thread creation

    // Create a new thread with the default attributes
    status = pthread_create(&thread, NULL, say_hello, name);

    // Check if the thread creation was successful
    if (status != 0) {
        perror("pthread_create");
        return 1;
    }

    // Wait for the thread to finish
    pthread_join(thread, NULL);

    return 0;
}