#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include "ScopedLocker.hpp"
//=======================================================
// Class: Vector
// contains a size_-size vector of integers.
// Use the function setAndTest to set all elements
// of the vector to a certain value and then test that
// the value is indeed correctly set
//=======================================================
class Vector
{
public:
   Vector(unsigned int size = 10000) : size_(size)
      {
         vector_ = new int[size_];
         pthread_mutex_init(&m_, NULL);
         set(0);
      }
   ~Vector()
      {
         delete[] vector_;
      }
   bool setAndTest(int n)
      {
         ScopedLocker lock(&m_);
         set(n);
         bool testOut = test(n);
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
   pthread_mutex_t m_;
};
#endif