#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>  //for semaphores
#include <iostream>
using namespace std;

void *printThreads(void*tID);
sem_t m;

int main(){
    pthread_t thread1, thread2;
    int a, b;
    int threadID1 = 1;
    int threadID2 = 2;
    cout << "Main: Creating threads" << endl;
    cout << "Main: Waiting for threads to finish" << endl;

    /*
    semaphore init - param: 
    sem_t *sem: address for semaphore 
    int phsared: 0 = shared between threads
    !0 = not shared between threads
    unsigned int value: initial value of semaphore 
    */
    sem_init(&m, 0, 1);  
    a = pthread_create(&thread1, NULL, *printThreads, (void*) threadID1);
    b = pthread_create(&thread2, NULL, *printThreads, (void*) threadID2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    sem_destroy(&m);
    cout << "Main: Exiting" << endl;
}

void *printThreads(void*tID){
    long threadIDs;
    threadIDs = (long) tID;
    for(int i =0; i<10; i++){
        sem_wait(&m);
        cout << "Hello #" << i << " from thread " << threadIDs << endl;
        sem_post(&m);
        sleep(1);
    }
    cout << "Thread " << threadIDs << " terminates" << endl;
    pthread_exit(NULL);
}