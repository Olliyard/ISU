#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
using namespace std;
pthread_mutex_t entryMutex;
pthread_mutex_t exitMutex;
pthread_cond_t  entryCond = PTHREAD_COND_INITIALIZER;
pthread_cond_t  exitCond  = PTHREAD_COND_INITIALIZER;
bool entryOpen = false, exitOpen = false, entryRequest = false, exitRequest = false;

void *carThread(void *carID);
void *PLCSEntry(void *);
void *PLCSExit(void *);

int main()
{
  pthread_t car, entry, exit;
  int id = 1;

  pthread_mutex_init(&entryMutex, NULL);
  pthread_mutex_init(&exitMutex, NULL);

  pthread_create(&entry, NULL, *PLCSEntry, NULL);
  pthread_create(&exit, NULL, *PLCSExit, NULL);
  pthread_create(&car, NULL, *carThread, (void *)id);

  pthread_join(car, NULL);
  pthread_join(entry, NULL);
  pthread_join(exit, NULL);
}

void *carThread(void *carID)
{
  while (1)
  {
    sleep(3);

    // Car entry
    pthread_mutex_lock(&entryMutex);
    cout << "" << endl;
    cout << "Car #" << (long)carID << " requests entrance." << endl;
    entryRequest = true; // car requests entry
    pthread_cond_signal(&entryCond);
    while (!entryOpen)
    { // wait for gate to open
      pthread_cond_wait(&entryCond, &entryMutex);
    }
    entryRequest = false; // stop request
    pthread_cond_signal(&entryCond);
    pthread_mutex_unlock(&entryMutex);

    // Car parked
    cout << "" << endl;
    cout << "Car #" << (long)carID << " is parked" << endl;
    sleep(2);

    // Car exit
    pthread_mutex_lock(&exitMutex);
    cout << "" << endl;
    cout << "Car #" << (long)carID << " requests exit." << endl;
    exitRequest = true;
    pthread_cond_signal(&exitCond);
    while (!exitOpen)
    {
      pthread_cond_wait(&exitCond, &exitMutex);
    }
    exitRequest = false;
    pthread_cond_signal(&exitCond);
    pthread_mutex_unlock(&exitMutex);
  }
  return NULL;
}

void *PLCSEntry(void *)
{
  while (1)
  {
    // Entry
    pthread_mutex_lock(&entryMutex);
    while (!entryRequest)
    { // wait until car requests entry
      pthread_cond_wait(&entryCond, &entryMutex);
    }
    entryOpen = true; // Open gate for car
    cout << "Opening entrance..." << endl;
    pthread_cond_signal(&entryCond);
    while (entryRequest)
    { // wait while car is entering
      pthread_cond_wait(&entryCond, &entryMutex);
    } 
    entryOpen = false;  //close gate
    cout << "Closing entrance..." << endl;
    pthread_mutex_unlock(&entryMutex);
  }
  return NULL;
}

void *PLCSExit(void *)
{
  while (1)
  {
    // Exit
    pthread_mutex_lock(&exitMutex);
    while (!exitRequest) 
    { // wait until car requests entry
      pthread_cond_wait(&exitCond, &exitMutex);
    }
    exitOpen = true; // Open gate for car
    cout << "Opening exit..." << endl;
    pthread_cond_signal(&exitCond);
    while (exitRequest)
    { // wait while car is exiting
      pthread_cond_wait(&exitCond, &exitMutex);
    }
    exitOpen = false; //close gate
    cout << "Closing entrance..." << endl;
    pthread_mutex_unlock(&exitMutex);
  }
  return NULL;
}
