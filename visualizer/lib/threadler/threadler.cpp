#include "threadler.h"

/** @brief wakeThread
 *
 * @todo: document this function
 */
bool Threadler::wakeThread(const ThreadID_t& /*index*/)
{
  /** @todo: fill in this function **/
  return false;
}


/** @brief snoozeThread
 *
 * @todo: document this function
 */
bool Threadler::snoozeThread(const ThreadID_t& /*index*/)
{
  /** @todo: fill in this function **/
  return false;
}


/** @brief destroyThread
 * destroy a thread
 * @param index the index of the thread to destroy
 * @return true on successful thread destruction
 */
bool Threadler::destroyThread(const ThreadID_t & index)
{
  #if 0
  if (!isInit())
    return false;
  #endif

  #ifdef WIN32
  return TerminateThread( m_threads[index], 0 );
  #else

  return pthread_cancel( m_threads[index] );
  #endif
}


/** @brief exitThread
 * force the thread this is called from to exit
 * @param exitVal this is the return value the thread should give (akin to a main's return)
 */
void Threadler::exitThread(const int & exitVal)
{
  #if 0
  if (!isInit())
    return;
  #endif

  #ifdef WIN32
  ExitThread(exitVal);
  #else
  pthread_exit((void*)exitVal);
  #endif
}


/** @brief getCurrentThread
 * get a handle on the thread this is called from
 * @return the handle of the thread this is called from
 */
ThreadHandle Threadler::getCurrentThread()
{
  #if 0
  if (!isInit())
    return ThreadHandle();
  #endif

  #ifdef WIN32
  return GetCurrentThread();
  #else
  return pthread_self();
  #endif
}


/** @brief getThread
 * get the thread ascociated with an index
 * @param index the index of the thread to get
 * @return a handle on the thread you are getting
 */
ThreadHandle Threadler::getThread(const ThreadID_t & index)
{
  #if 0
  if (!isInit())
    return ThreadHandle();
  #endif

  return m_threads[index];
}


/** @brief createThread
 * create a thread out of a function
 * @param fxn the function that you want the thread to be run from
 * @param args the arguments you want to pass the function
 * @return the index of the thread created, or (unsigned)-1 if it failed
 */
unsigned int Threadler::createThread(ThreadFxnType fxn(ThreadArgType), ThreadArgType args)
{
  #if 0
  if (!isInit())
    return -1;
  #endif

  #ifdef WIN32
  HANDLE thread = CreateThread( NULL, 0, (LPTHREAD_START_ROUTINE)fxn, args, 0, NULL );
  m_threads.push_back( thread );
  return m_threads.size()-1;
  #else
  pthread_t thread;
  pthread_create(&thread,NULL,fxn,args);
  m_threads.push_back(thread);
  return m_threads.size()-1;
  #endif
}


/** @brief joinThread
 * wait until a chosen thread exits and join with it
 * @param index the index of the thread to join with
 * @return true if the join was successful
 */
bool Threadler::joinThread(const ThreadID_t & index)
{
  #if 0
  if (!isInit())
    return false;
  #endif

  #ifdef WIN32
  bool retval = (WaitForSingleObject(get()->m_threads[index], INFINITE) == WAIT_OBJECT_0);
  m_threads.erase( m_threads.begin() + index );
  return retval;
  #else
  void * temp;
  bool retval = pthread_join( m_threads[index], &temp );
  m_threads.erase( m_threads.begin()+index );
  return retval;
  #endif
}
