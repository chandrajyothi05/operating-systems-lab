#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int buffer[5];
int item, in = 0, out = 0;
sem_t full, empty;  
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int isBufferFull() {
    return ((in + 1) % 5) == out;
}

int isBufferEmpty() {
    return in == out;
}

void producer() {
    if (isBufferFull()) {
        printf("Buffer is full, producer is waiting...\n");
        return;
    }

    item = rand() % 500;

    sem_wait(&empty);               
    pthread_mutex_lock(&mutex);     

    buffer[in] = item;
    printf("Producer inserts item %d at %d\n", item, in);
    in = (in + 1) % 5;

    pthread_mutex_unlock(&mutex);   
    sem_post(&full);                
}

void consumer() {
    if (isBufferEmpty()) {
        printf("Buffer is empty, consumer is waiting...\n");
        return;
    }

    sem_wait(&full);                
    pthread_mutex_lock(&mutex);     

    item = buffer[out];
    printf("Consumer consumes item %d at %d\n", item, out);
    out = (out + 1) % 5;

    pthread_mutex_unlock(&mutex);   
    sem_post(&empty);               
}

int main() { 
    int n, c = 0;
    sem_init(&full, 0, 0);   
    sem_init(&empty, 0, 5);  
    printf("Enter number of random numbers generated:\n");
    scanf("%d", &n);

    while (c < n) {
        int i = rand();
        if (i % 2 == 1) {
            producer();
        } else {
            consumer();
        }
        c++;
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}