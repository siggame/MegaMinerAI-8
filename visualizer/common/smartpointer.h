//////////////////////////////////////////////////////////////////////////////
/// @file smartpointer.h
/// @brief Contains the class definition for the templated smart pointer 
/// class. 
//////////////////////////////////////////////////////////////////////////////
#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "common.h"

//////////////////////////////////////////////////////////////////////////////
/// @class SmartPointer
/// @brief This class is the smart pointer class, created to mimic the 
/// behavior of a real pointer, but automatically deletes itself when no
/// more references to the pointer exist.
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
/// @fn SmartPointer::SmartPointer()
/// @brief Default constructor for the SmartPointer.  This instantiates the 
/// wrapped pointer to 0 and sets the number of references to 1.
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
/// @fn SmartPointer::SmartPointer( T* data )
/// @brief Constructor for the smart pointer which wraps the given pointer, 
/// and sets the number of references to 1.
/// @param data Pointer to the templated parameter to wrap in the pointer. 
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
/// @fn SmartPointer::~SmartPointer()
/// @brief Destructor for the smart pointer class.  If no more references 
/// exist for the wrapped pointer, then the pointer is destroyed.  Otherwise,
/// the number of references is decremented and the pointer continues to live.
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
/// @fn SmartPointer::operator *()
/// @brief Dereferencing operator overload which returnes a reference to the 
/// dereferenced pointer.
/// @return A reference to the dereferenced pointer.
//////////////////////////////////////////////////////////////////////////////


template <class T>
class SmartPointer
{
  private:
    T* m_data;
    int *m_ref;
  public:
    SmartPointer() : m_data(0)
    {
      m_ref = new int;
      *m_ref = 1;
    }

    SmartPointer( T* data ) : m_data( data )
    {
      m_ref = new int;
      *m_ref = 1;
    }

    SmartPointer( const SmartPointer<T>& data ) : m_data( data.m_data ), m_ref( data.m_ref )
    {
      (*m_ref)++;
    }

    template<class U> friend class SmartPointer;

    template<class U>
    SmartPointer( const SmartPointer<U>& data ) : m_data( data.m_data ), m_ref( data.m_ref )
    {
      (*m_ref)++;
    }

    virtual ~SmartPointer()
    {
      (*m_ref)--;
      if( *m_ref == 0 )
      {
        delete m_data;
        delete m_ref;
        m_data = 0;
        m_ref = 0;
 
      }
    }

    operator T*()
    {
      return m_data;
    }

    T& operator *()
    {
      return *m_data;
    }

    T* operator -> ()
    {
      return m_data;
    }

    const T* operator -> () const
    {
      return m_data;
    }

    SmartPointer<T>& operator = ( const SmartPointer<T>& sp )
    {
      if( this != &sp )
      {
        (*m_ref)--;
        if( *m_ref == 0 )
        {
          delete m_ref;
          delete m_data;
        }

        m_data = sp.m_data;
        m_ref = sp.m_ref;
        (*m_ref)++;
      }

      return *this;
    }

    operator bool()
    {
      return m_data != 0;
    }

};

#endif
