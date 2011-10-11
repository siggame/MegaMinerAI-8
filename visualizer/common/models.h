#ifndef MODELS_H 
#define MODELS_H 

namespace visualizer
{

  struct Color
  {
    Color()
    {
      r = g = b = a = 1;
    }

    Color( const float& R, const float& G, const float& B, const float& A = 1.0f )
    {
      r = R;
      g = G;
      b = B;
      a = A;
    }

    float r;
    float g;
    float b;
    float a;

  };

  struct vertex 
  {
    vertex()
    {
      x = y = z = 0;
    }

    vertex( const vertex& rhs )
    {
      x = rhs.x;
      y = rhs.y;
      z = rhs.z;
    }

    vertex( const float& X, const float& Y=0, const float& Z=0 )
    {
      x = X;
      y = Y;
      z = Z;
    }


    // These are for map comparisons.
    bool operator < ( const vertex& rhs ) const
    {
      
      if( x*1000 + y < rhs.x*1000 + rhs.y )
        return true;

      return false;
    }

    vertex operator + ( const vertex& rhs )
    {
      vertex r;
      r.x = x + rhs.x;
      r.y = y + rhs.y;
      r.z = z + rhs.z;

      return r;
    }

    vertex& operator += ( const vertex& rhs )
    {
      x += rhs.x;
      y += rhs.y;
      z += rhs.z;
      return *this;
    }
    
    float x;
    float y;
    float z;

  }; // vertex


} // visualizer


#endif // MODELS_H
