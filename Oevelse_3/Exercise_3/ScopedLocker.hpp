#ifndef SCOPEDLOCKER_HPP_
#define SCOPEDLOCKER_HPP_
#include <pthread.h>
//=======================================================
// Class: ScopedLocker
// is passed a mutex as a reference.
// Use the function to ensure mutex is unlocked
// before program completion
//=======================================================

class ScopedLocker
{
public:
    ScopedLocker(pthread_mutex_t *m): m_(m)
    {
        pthread_mutex_lock(m_);
    }
    virtual ~ScopedLocker()
    {
        pthread_mutex_unlock(m_);
    }

private:
    pthread_mutex_t *m_;
};

#endif