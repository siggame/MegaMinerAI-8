#include "Mutex.h"

_Mutex *Mutex = 0;

/** @brief get_Mutex
 * get a handle to a mutex
 * @param mutexName the name of the mutex
 * @return a handle to the mutex
 */
MutexHandle _Mutex::getMutex(const MutexID_t & mutexName)
{
  #if 0
  if (!isInit())
  {
    std::cout << "Attempting to get a mutex with an uninitialized singleton\n";
    return MutexHandle();
  }
  #endif

  if ( m_mutexes.find(mutexName) != m_mutexes.end())
  {
    return m_mutexes[mutexName];
  }

  return MutexHandle();
}


/** @brief unlock
 * unlock an existing mutex
 * @param mutexName the name of the mutex to unlock
 * @return true if the lock was successfully released
 */
bool _Mutex::unlock(const MutexID_t & mutexName)
{
  #if 0
  if (!isInit())
  {
    std::cout << "Attempting to unlock a mutex with an uninitialized singleton\n";
    return false;
  }
  #endif
  if ( m_mutexes.find(mutexName) != m_mutexes.end())
  {
    #ifdef WIN32
    Release_Mutex( m_mutexes[mutexName] );
    #else
    pthread_mutex_unlock( &m_mutexes[mutexName] );
    #endif
    return true;
  }

  std::cout <<"\"" << mutexName << "\" is not a valid mutex\n";
  return false;
}


/** @brief lock
 * lock an existing mutex
 * @param mutexName the name of the mutex to lock
 * @return true if the lock was successfully grabbed
 */
bool _Mutex::lock(const MutexID_t & mutexName)
{
  #if 0
  if (!isInit())
  {
    std::cout << "Attempting to lock a mutex with an uninitialized singleton\n";
    return false;
  }
  #endif

  if ( m_mutexes.find(mutexName) != m_mutexes.end() )
  {
    #ifdef WIN32
    WaitForSingleObject( m_mutexes[mutexName], INFINITE );
    #else
    pthread_mutex_lock( &( m_mutexes[mutexName] ) );
    #endif
    return true;
  }

  std::cout <<"\"" << mutexName << "\" is not a valid mutex\n";
  return false;
}


/** @brief create_Mutex
 * create a mutex
 * @param mutexName the name of the mutex to create
 * @return true if the creation was successful
 */
bool _Mutex::createMutex(const MutexID_t & mutexName)
{
  #if 0
  if (!isInit())
  {
    std::cout << "Attempting to create a mutex with an uninitialized singleton\n";
    return false;
  }
  #endif
  if ( m_mutexes.find(mutexName) == m_mutexes.end() )
  {
    #ifdef WIN32
    m_mutexes[mutexName] = Create_Mutex( NULL, false, NULL );
    #else
    pthread_mutex_t temp = PTHREAD_MUTEX_INITIALIZER;
    m_mutexes[mutexName] = temp;
    #endif
    return true;
  }

  std::cout <<"\"" << mutexName << "\" already exists\n";
  return false;
}


void _Mutex::setup()
{
  if( !Mutex )
  {
    Mutex = new _Mutex;
  }
  else
  {
    throw "Mutex already initialized.";
  }
}


void _Mutex::destroy()
{
  delete Mutex;
  Mutex = 0;

}
