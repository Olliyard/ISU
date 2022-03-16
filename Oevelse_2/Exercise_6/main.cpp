#include "Vector.hpp"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
#define vSize 10000
using namespace std;

void *writer(void*tID);

int sleepTime;
int errCount = 0;
Vector vector1(vSize);

int main(int argc, char *argv[]){
    int nThreads;
    nThreads = atoi(argv[1]);
    sleepTime = atoi(argv[2]);
    pthread_t thread_id[nThreads];
    
    if (argc < 2){
        perror("Not enough arguments given");
    }
    if(nThreads < 1 || nThreads > 100){
        cout << "Number must be between 1 and 100" << endl;
    }
    if(sleepTime < 0){
        cout << "Invalid time set" << endl;
    }

    cout << "Threads: " << nThreads << endl;
    cout << "Delay: " << sleepTime << endl;
    cout << "Elements: " << vSize << endl;

    cout << "Main: Creating threads" << endl;
    for(long int i = 1; i < nThreads+1; i++){
        pthread_create(&thread_id[i], NULL, *writer, (void*) i);
    }

    for(int j = 1; j < nThreads+1; j++){
        pthread_join(thread_id[j], NULL);
    }

    cout << "End of main -- Total errors in writer function: " << errCount << endl;
    cout << "Error percentage: " << (((double)errCount/((double)nThreads*10))*100) << "%" << endl;
}

void *writer(void*tID){
    bool status;
    long threadIDs;
    threadIDs = (long) tID;
    for(int i = 0; i < 10; i++){
        status = vector1.setAndTest(threadIDs);
        if(status == false){
            errCount++;
        }
        usleep(sleepTime);
    }
    pthread_exit(NULL);
}