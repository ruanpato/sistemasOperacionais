#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread1(void *data);
void *thread2(void *data);

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER, mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_t Thread1, Thread2;

int main(void) {
    pthread_create(&Thread1, NULL, thread1, NULL);
    pthread_create(&Thread2, NULL, thread2, NULL);
    //now join them
    pthread_join(Thread1, NULL);
    printf("Thread ID%ld returned\n", Thread1);
    pthread_join(Thread2, NULL);
    printf("Thread ID%ld returned\n", Thread2);


    return 1;
}

void *thread1(void *data){
    unsigned long i,j;
    if(pthread_mutex_lock(&mutex1) == 0) {
        printf("Thread ID%ld got mutex1.\n", pthread_self());
        for(i=0; i< 10000000; ++i); // just for wasting some time
        while(1) {
            pthread_mutex_unlock(&mutex1); // If can't get needs free the used mutex, and if get need's free too
            if(pthread_mutex_trylock(&mutex2) == 0) {
                printf("Thread ID%ld got mutex2.\n", pthread_self());          
                for(i=0; i< 10000000; ++i); // just for wasting some time
                pthread_mutex_unlock(&mutex2);
                break;
            }
        }
    } else { 
        printf("\nThread ID%ld did not get mutex1.\n", pthread_self());
        pthread_mutex_unlock(&mutex1);
        pthread_exit(NULL);
    }
}

void *thread2(void *data){
    unsigned long i,j;
    if(pthread_mutex_lock(&mutex2) == 0) {
        printf("Thread ID%ld got mutex2.\n", pthread_self());
        for(i=0; i< 10000000; ++i); // just for wasting some time
        while(1) {
            pthread_mutex_unlock(&mutex2); // If can't get needs free the used mutex, and if get need's free too
            if(pthread_mutex_trylock(&mutex1) == 0) {
                printf("Thread ID%ld got mutex1.\n", pthread_self());          
                for(i=0; i< 10000000; ++i); // just for wasting some time
                pthread_mutex_unlock(&mutex1);
                break;
            }
        }
    } else { 
        printf("\nThread ID%ld did not get mutex2.\n", pthread_self());
        pthread_mutex_unlock(&mutex2);
        pthread_exit(NULL);
    }
}
