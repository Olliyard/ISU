#ifndef VECTOR_HPP_
#define VECTOR_HPP_
#include <pthread.h>
#include <semaphore.h>
//=======================================================
// Class: Vector
// contains a size_-size vector of integers.
// Use the function setAndTest to set all elements
// of the vector to a certain value and then test that
// the value is indeed correctly set
//=======================================================
class Vector
{
   sem_t semSet, semTest;
public:
   Vector(unsigned int size = 10000) : size_(size)
      {
         vector_ = new int[size_];
         sem_init(&semSet, 0, 1);
         sem_init(&semTest, 0, 0);
         set(0);
      }
   ~Vector()
      {
         delete[] vector_;
      }
   bool setAndTest(int n)
      {
         sem_wait(&semSet);    //semSet 1->0 (låst)
         set(n);
         sem_post(&semTest);   //semTest 0->1 (ulåst)

         sem_wait(&semTest);   //semTest 1->0 (låst)
         bool testOut = test(n);
         sem_post(&semSet);    //semSet 0->1 (ulåst)
         return testOut;
      }
   
private:
   void set(int n)
      {
         for(unsigned int i=0; i<size_; i++) vector_[i] = n;
      }
   bool test(int n)
      {
         for(unsigned int i=0; i<size_; i++) if(vector_[i] != n) return false;
         return true;
      }
   int*           vector_;
   unsigned int   size_;
};
#endif