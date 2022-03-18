#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
using namespace std;

void *printThreads(void*tID);
pthread_mutex_t m;

int main(){
    pthread_t thread1, thread2;
    int a, b;
    int threadID1 = 1;
    int threadID2 = 2;
    cout << "Main: Creating threads" << endl;
    cout << "Main: Waiting for threads to finish" << endl;

    pthread_mutex_init(&m, NULL);
    a = pthread_create(&thread1, NULL, *printThreads, (void*) threadID1);
    b = pthread_create(&thread2, NULL, *printThreads, (void*) threadID2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    cout << "Main: Exiting" << endl;
}

void *printThreads(void*tID){
    long threadIDs;
    threadIDs = (long) tID;
    for(int i =0; i<10; i++){
        pthread_mutex_lock(&m);
        cout << "Hello #" << i << " from thread " << threadIDs << endl;
        pthread_mutex_unlock(&m);
        sleep(1);
    }
    cout << "Thread " << threadIDs << " terminates" << endl;
    pthread_exit(NULL);
}