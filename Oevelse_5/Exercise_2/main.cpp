#include "MsgQueue.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

unsigned long idType = 1;

struct Point3D: public Message{
    int x, y, z;
};

MsgQueue msgQueue(10);

void *sender(void*);
void *receiver(void*);

int main(){
    pthread_t send, receive;
    pthread_create(&send, NULL, *sender, NULL);
    pthread_create(&receive, NULL, *receiver, NULL);
    pthread_join(send, NULL);
    pthread_join(receive, NULL);
}

void *sender(void*){
    while(1){
        Point3D *point = new Point3D;
        point->x = rand()%100;
        point->y = rand()%100;
        point->z = rand()%100;
        msgQueue.send(idType, point);
        sleep(1);
    }
}

void *receiver(void*){
    while(1){
        Message* retMsg;
        retMsg = msgQueue.receive(idType);
        cout << "Points: " << retMsg << endl;
        delete retMsg;
    }
}