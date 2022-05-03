#pragma once

/*-------------------------*/
/* Class: MsgQueue */
/*-------------------------*/
#include <queue>
#include <iostream>
#include <pthread.h>
#include "Message.hpp"
using namespace std;

class MsgQueue
{
public:
    MsgQueue(unsigned long maxSize);
    void send(unsigned long type, Message* msg = NULL);
    Message* receive(unsigned long& type);
    ~MsgQueue(){};
private:
    queue<pair<unsigned long, Message*>* > *queue_;
    unsigned long maxSize_;
    pthread_mutex_t queueMutex_ = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t  queueCond_ = PTHREAD_COND_INITIALIZER;
};

MsgQueue::MsgQueue(unsigned long maxSize) : maxSize_(maxSize) {}

void MsgQueue::send(unsigned long type, Message* msg){
    pthread_mutex_lock(&queueMutex_);
    while(queue_->size() == maxSize_){
        pthread_cond_wait(&queueCond_, &queueMutex_);
    }
    /* WAITS FOR OPEN SPACE IN QUEUE*/
    queue_->push(new pair<unsigned long, Message*>(type, msg));
    pthread_cond_signal(&queueCond_);
    pthread_mutex_unlock(&queueMutex_);
}


Message* MsgQueue::receive(unsigned long& type){
    pthread_mutex_lock(&queueMutex_);
    while(queue_->empty()){
        pthread_cond_wait(&queueCond_, &queueMutex_);
    }
    /* WAITS FOR SOMETHING IN QUEUE*/
    queue_->pop();
    pthread_cond_signal(&queueCond_);
    pthread_mutex_unlock(&queueMutex_);
    return queue_->front()->second;
}