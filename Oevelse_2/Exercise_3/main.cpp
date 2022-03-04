#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <iostream>
using namespace std;

void *printInc(void*);
void *printRead(void*);
unsigned int shared = 0;

int main(){
    pthread_t thread1, thread2;
    int incrementer, reader;
    cout << "Main: Creating threads" << endl;
    cout << "Main: Waiting for threads to finish" << endl;

    incrementer = pthread_create(&thread1, NULL, *printInc, NULL);
    reader = pthread_create(&thread2, NULL, *printRead, NULL);

    while(true){}
}

void *printInc(void*){
    while(true){
        shared++;
        sleep(1);
    }
}

void *printRead(void*){
    while(true){
        cout << "Read value: " << shared << endl;
        sleep(1);
    }
}