#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
using namespace std;

void *printInc(void*shVal);
void *printRead(void*shVal);

int main(){
    pthread_t thread1, thread2;
    int incrementer, reader;
    unsigned int shared = 0;
    cout << "Main: Creating threads" << endl;
    cout << "Main: Waiting for threads to finish" << endl;

    incrementer = pthread_create(&thread1, NULL, *printInc, (void*) shared);
    reader = pthread_create(&thread2, NULL, *printRead, (void*) shared);

    while(true){}
}

void *printInc(void*shVal){
    while(true){
        (unsigned long) ++shVal;
        sleep(1);
    }
    pthread_exit(NULL);
}

void *printRead(void*shVal){
    while(true){
        cout << "Read value: " << (unsigned long) shVal << endl;
        sleep(1);
    }
    pthread_exit(NULL);
}