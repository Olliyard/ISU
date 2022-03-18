#ifndef VECTOR_HPP_
#define VECTOR_HPP_
#include <pthread.h>
//=======================================================
// Class: Vector
// contains a size_-size vector of integers.
// Use the function setAndTest to set all elements
// of the vector to a certain value and then test that
// the value is indeed correctly set
//=======================================================
class Vector
{
   pthread_mutex_t m;
public:
   Vector(unsigned int size = 10000) : size_(size)
      {
         vector_ = new int[size_];
         pthread_mutex_init(&m, NULL);
         set(0);
      }
   ~Vector()
      {
         delete[] vector_;
      }
   bool setAndTest(int n)
      {
         pthread_mutex_lock(&m);
         set(n);
         bool testOut = test(n);
         pthread_mutex_unlock(&m);
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