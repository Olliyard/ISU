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

int main(int argc, char *argv[])
{
    int nThreads;
    nThreads = atoi(argv[1]);
    pthread_t car[nThreads];
    pthread_t entry, exit;
    srand(time(NULL));

    pthread_mutex_init(&entryMutex, NULL);
    pthread_mutex_init(&exitMutex, NULL);

    cout << "Main: Creating entry & exit threads" << endl;
    pthread_create(&entry, NULL, *PLCSEntry, NULL);
    pthread_create(&exit, NULL, *PLCSExit, NULL);

    cout << "Main: Creating cars..." << endl;
    for(long int i = 1; i < nThreads+1; i++){
        pthread_create(&car[i], NULL, *carThread, (void*) i);
    }

    pthread_join(entry, NULL);
    pthread_join(exit, NULL);

    for(int j = 1; j < nThreads+1; j++){
        pthread_join(car[j], NULL);
    }
}

void *carThread(void *carID)
{
    while (1)
    {
        /*----Car entry----*/
        sleep(rand()%4);    //wait random time to request entrance
        pthread_mutex_lock(&entryMutex);

        //Request entrance and signal condition
        entryRequest = true;
        cout << "\nCar #" << (long)carID << " requests entrance." << endl;
        pthread_cond_signal(&entryCond);

        //Wait for entry gate to open
        while (!entryOpen)
        { 
            pthread_cond_wait(&entryCond, &entryMutex);
        }

        //Stop requesting entrance and park car
        entryRequest = false;
        cout << "\nCar #" << (long)carID << " is parked" << endl;
        pthread_cond_signal(&entryCond);
        pthread_mutex_unlock(&entryMutex);
        /*----Car entry done----*/

        /*----Car parked----*/
        sleep(rand()%4);        //park random amount of time
        /*----Car parked done----*/

        /*----Car exit----*/
        pthread_mutex_lock(&exitMutex);

        //Request entrance and signal condition
        exitRequest = true;
        cout << "\nCar #" << (long)carID << " requests exit." << endl;
        pthread_cond_signal(&exitCond);

        //Wait for exit gate to open
        while (!exitOpen)
        {
            pthread_cond_wait(&exitCond, &exitMutex);
        }

        //Stop requesting exit and leave carpark
        exitRequest = false;
        cout << "Car #" << (long)carID << " has left parking space." << endl;
        pthread_cond_signal(&exitCond);
        pthread_mutex_unlock(&exitMutex);
        /*---Car exit done----*/
    }
    return NULL;
}


void *PLCSEntry(void *)
{
    while (1)
    {
        // Entry
        pthread_mutex_lock(&entryMutex);

        //Wait until car requests entry
        while (!entryRequest)
        { 
            pthread_cond_wait(&entryCond, &entryMutex);
        }

        //Open door and signal condition.
        entryOpen = true;
        cout << "Opening entrance..." << endl;
        pthread_cond_signal(&entryCond);

        //Wait while car is entering parking lot
        while (entryRequest)
        { 
            pthread_cond_wait(&entryCond, &entryMutex);
        } 

        //Close door and signal condition
        entryOpen = false;
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

        //Wait until car requests entry
        while (!exitRequest)
        { 
            pthread_cond_wait(&exitCond, &exitMutex);
        }

        //Open door and signal condition.
        exitOpen = true;
        cout << "Opening exit..." << endl;
        pthread_cond_signal(&exitCond);

        //Wait while car is exiting parking lot
        while (exitRequest)
        { 
            pthread_cond_wait(&exitCond, &exitMutex);
        }

        //Close door and signal condition
        exitOpen = false;
        cout << "Closing exit..." << endl;
        pthread_mutex_unlock(&exitMutex);
    }
    return NULL;
}
