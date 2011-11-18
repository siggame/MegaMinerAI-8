#ifndef COMMON_H
#define COMMON_H

#include "exception.h"
#include "smartpointer.h"
#include <QtOpenGL>

#if __DEBUG__

#include <stdio.h>
#include <iostream>

#include <map>


typedef struct {
  long int address;
  long int size;
  char  file[64];
  long int line;

} ALLOC_INFO;

extern list< ALLOC_INFO > allocMap;

void DumpUnfreed();

#ifdef __DEBUG_NEW__

void AddTrack(long int addr,  long int asize,  const char *fname, long int lnum);
void RemoveTrack( long int addr );

inline void *operator new( size_t size, const char *file, int line )
{
  void *ptr = (void*)malloc( size );
  AddTrack( (unsigned long)ptr, size, file, line );
  return ptr;

}

inline void *operator new [] ( size_t size, const char *file, int line )
{
  void *ptr = (void*)malloc( size );
  AddTrack( (unsigned long)ptr, size, file, line );
  return ptr;

}

inline void operator delete( void *p )
{
  RemoveTrack( (long int)p );
  free( p );
  
}

inline void operator delete [] ( void *p )
{
  RemoveTrack( (long int)p );
  free( p );
  
}

#define DEBUG_NEW new( __FILE__, __LINE__ )
#define DEBUG_DELETE( x ) Delete( x )

#define new DEBUG_NEW

#endif

//void * operator new( size_t size )
//{
  //cout << file << ": " << line << endl;
  //return new char[size];
  
//}

//#define new new( __FILE__, __LINE__ )


#endif

namespace visualizer 
{

#define THROW( x, y, ... ) \
  { \
  char message[512]; \
  sprintf( message, y, ##__VA_ARGS__ ); \
  throw x( message, __FILE__, __LINE__ ); \
  } 

#define WARNING( y, ... ) \
  { \
  char message[512]; \
  sprintf( message, y, ##__VA_ARGS__ ); \
  cerr << "WARNING: " << message << endl; \
  } 

#if __DEBUG__

#define SETUP(x) std::cout << x << " initialized at line " << __LINE__ << "." << endl;

inline void printStackTrace() 
{
#ifdef __STACKTRACE__ 
  // Exception is closing everything down anyway.  May as well use up some memory
  void *array[256];
  size_t size;
  cerr << " Stack Trace: " << endl;
  size = backtrace( array, 10 );
  backtrace_symbols_fd( array, size, 2 );
#endif
}
inline void openglErrorCheck()
{
  unsigned int err;
  while( (err = glGetError() ) )
  {
    switch( err )
    {
      case GL_INVALID_ENUM:
      {
        WARNING( "Invalid Enumeration Used In Some OpenGL Thing"  );
      } break;
      case GL_INVALID_VALUE:
      {
        WARNING( "An Invalid Value Was Used In Some OpenGL Argument And Was Ignored.  Wish I had more details for you..." );
      } break;
      case GL_INVALID_OPERATION:
      {
        WARNING( "An Invalid OpenGL Operation Was Performed and Ignored.  Wish I had more details for you..." );
      } break;
      case GL_STACK_OVERFLOW:
      {
        WARNING( "An OpenGL Comman You Tried to Perform Would Have Caused A Stack Overflow.  It was ignored.  Wish I had more details for you..." );
      } break;
      case GL_STACK_UNDERFLOW:
      {
        WARNING( "WHAT THE FUCK DID YOU DO!?!?" );
      } break;
      case GL_OUT_OF_MEMORY:
      {
        THROW( OpenGLException, "OpenGL Is Out Of Memory.  Clean up after yourself." );
      } break;
      case GL_NO_ERROR:
      break;
      default:
        THROW( OpenGLException, "OpenGL Error Occurred Somewhere." );

    }
  }

}

#define IMPLEMENT_ME THROW( Exception, "This Feature Is Not Yet Implemented." );

#define DBG_MSG( x ) std::cout << "DEBUG MSG: " << x << endl;

#else

#define SETUP(x)
#define DBG_MSG( x )

#endif                           /* __DEBUG__ */

class Module
{
  public:
    static void setup();
    static void destroy();
    virtual ~Module() {};
};

} // visualizer

#endif
