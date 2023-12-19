#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#define N_READERS 10 // Number of reader threads
#define N_WRITERS 5 // Number of writer threads
sem_t mutex; // Mutual exclusion semaphore
sem_t wrt; // Writer semaphore
int reader_count = 0; // Number of readers reading
void reader_thread(void) {
while (1) {
// Try to acquire the mutex semaphore
sem_wait(&mutex);
// Increment reader count
reader_count++;
// Release the mutex semaphore
sem_post(&mutex);
// Simulate reading data
printf("Reader is reading...\n");
sleep(1);
// Try to acquire the mutex semaphore again
sem_wait(&mutex);
// Decrement reader count
reader_count--;
// If there are no readers left, signal any waiting writers
if (reader_count == 0) {
sem_post(&wrt);
}
// Release the mutex semaphore
sem_post(&mutex);
// Do something else (not reading)
printf("Reader done reading...\n");
sleep(2);
}
}
void writer_thread(void) {
while (1) {
// Try to acquire the writer semaphore
sem_wait(&wrt);
// Try to acquire the mutex semaphore
sem_wait(&mutex);
// Simulate writing data
printf("Writer is writing...\n");
sleep(3);
// Release the mutex semaphore
sem_post(&mutex);
// Release the writer semaphore
sem_post(&wrt);
// Do something else (not writing)
printf("Writer done writing...\n");
sleep(5);
}
}
int main(void) {
// Initialize semaphores
sem_init(&mutex, 0, 1);
sem_init(&wrt, 0, 1);
// Create reader threads
for (int i = 0; i < N_READERS; i++) {
pthread_t thread;
pthread_create(&thread, NULL, (void*)reader_thread, NULL);
}
// Create writer threads
for (int i = 0; i < N_WRITERS; i++) {
pthread_t thread;
pthread_create(&thread, NULL, (void*)writer_thread, NULL);
}
// Wait for all threads to finish
pthread_join(thread, NULL);
// Destroy semaphores
sem_destroy(&mutex);
sem_destroy(&wrt);
return 0;
}

