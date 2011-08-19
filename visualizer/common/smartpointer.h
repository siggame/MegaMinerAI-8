#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

template <class T>
class SmartPointer
{
  private:
    T* m_data;
    int *m_ref;
    string msg;
  public:
    SmartPointer() : m_data(0)
    {
      m_ref = new int;
      *m_ref = 1;
      msg = "";
    }

    SmartPointer( T* data ) : m_data( data )
    {
      m_ref = new int;
      *m_ref = 1;
      msg = "";
    }

    SmartPointer( T* data, string mesg ) : m_data( data ), msg( mesg )
    {
      m_ref = new int;
      *m_ref = 1;
    }

    SmartPointer( const SmartPointer<T>& data ) : m_data( data.m_data ), m_ref( data.m_ref )
    {
      (*m_ref)++;
      msg = data.msg;
    }

    ~SmartPointer()
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
        msg = sp.msg;
        (*m_ref)++;
      }

      return *this;
    }

    operator bool()
    {
      return m_data != 0;
    }

    T* ptr()
    {
      return m_data;
    }

};

#endif
