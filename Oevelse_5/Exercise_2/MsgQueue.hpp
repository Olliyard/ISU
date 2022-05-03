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
    void send(unsigned long id, Message* msg = NULL);
    Message* receive(unsigned long& id);
    ~MsgQueue();
private:
    queue<pair<unsigned long, Message*>* > *queue_;
    unsigned long maxSize_;
    pthread_mutex_t queueMutex_ = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t  queueCond_ = PTHREAD_COND_INITIALIZER;
};

void MsgQueue::send(unsigned long id, Message* msg){
    pthread_mutex_lock(&queueMutex_);
    while(queue_->size() == maxSize_){
        pthread_cond_wait(&queueCond_, &queueMutex_);
    }
    /* WAITS FOR OPEN SPACE IN QUEUE*/
    queue_->push(new pair<unsigned long, Message*>(id, msg));
    pthread_cond_signal(&queueCond_);
    pthread_mutex_unlock(&queueMutex_);
}

Message* MsgQueue::receive(unsigned long& id){
    pthread_mutex_lock(&queueMutex_);
    while(queue_->empty()){
        pthread_cond_wait(&queueCond_, &queueMutex_);
    }
    /* WAITS FOR SOMETHING IN QUEUE*/
    cout << "ID #" << id << " " << queue_->front()->first << queue_->front()->second << endl;
    queue_->pop();
    pthread_cond_signal(&queueCond_);
    pthread_mutex_unlock(&queueMutex_);
    return queue_->front()->second;
}