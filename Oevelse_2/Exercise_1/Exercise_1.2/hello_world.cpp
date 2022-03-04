#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

void *hello_world(void*msg);

int main(){
    pthread_t thread1;
    const char*hello = "Hello world!";
    int cthread;

    cthread = pthread_create(&thread1, NULL, *hello_world, (void*) hello);
    pthread_join(thread1, NULL);
}

void *hello_world(void*msg){
    const char*message;
    message = (const char*) msg;
    std::cout << message << std::endl;
    pthread_exit(NULL);
}