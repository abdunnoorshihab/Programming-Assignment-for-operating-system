#include <stdio.h> #include <string.h> #include <pthread.h> #include <stdlib.h> #include <unistd.h> #include <semaphore.h>
// Declare the semaphores and shared variables sem_t x, y, z, rsem, wsem;
int readcount, writecount;
// Initialize the semaphores and shared variables void initialize() {
sem_init(&rsem, 0, 1);
sem_init(&wsem, 0, 1);
sem_init(&x, 0, 1);
sem_init(&y, 0, 1);
sem_init(&z, 0, 1);
readcount = 0;
writecount = 0;
}
// Reader thread function void* reader(void* arg) {
// Wait on the appropriate semaphores to enter the critical section sem_wait(&z);
sem_wait(&rsem); sem_wait(&x);
// Increment the reader count and check if it's the first reader printf("Reader is trying to enter\n");
sleep(1); readcount++;
if (readcount == 1) { sem_wait(&wsem);
}
// Release the semaphores and print out the reader count sem_post(&x);
sem_post(&rsem); sem_post(&z);
printf("Reader is inside critical section \n"); sleep(1);
// Decrement the reader count and check if it's the last reader printf("Reader is leaving\n");
sem_wait(&x); readcount--;
if (readcount == 0) { sem_post(&wsem);
}
sem_post(&x);
}
// Writer thread function void* writer(void* arg) {
// Wait on the appropriate semaphores to enter the critical section printf("Writer is trying to enter\n");
sleep(1); sem_wait(&y); writecount++;
if (writecount == 1) { sem_wait(&rsem);
}
// Acquire the wsem semaphore to ensure mutual exclusion among writers sem_post(&y);
sem_wait(&wsem);
// Release the semaphores and print out the writer count printf("Writer has entered the critical section\n"); sleep(1);
printf("Writer is leaving\n"); sem_post(&wsem);
sem_wait(&y);
// Decrement the writer count and check if it's the last writer writecount--;
if (writecount == 0) { sem_post(&rsem);
}
sem_post(&y);
}
int main() {
int r = 5; int w = 3;
// Initialize the semaphores and shared variables initialize();
// Create the reader threads with random delay pthread_t rtid[r];
for (int i = 0; i < r; ++i) {
int delay = rand() % 5; // generate a random delay between 0 and 4 seconds sleep(delay); // wait for the delay
pthread_create(&(rtid[i]), NULL, &reader, NULL);
}
// Create the writer threads with random delay pthread_t wtid[w];
for (int i = 0; i < w; ++i) {
int delay = rand() % 5; // generate a random delay between 0 and 4 seconds sleep(delay); // wait for the delay
pthread_create(&(wtid[i]), NULL, &writer, NULL);
}
// Wait for all reader threads to finish for (int i = 0; i < r; ++i) {
pthread_join(rtid[i], NULL);
}
// Waits for all writer threads to finish for (int i = 0; i < w; ++i) {
pthread_join(wtid[i], NULL);
}
return 0;
}

