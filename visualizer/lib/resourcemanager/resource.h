#ifndef RESOURCE_H
#define RESOURCE_H
#include <set>
#include <string>
#include <QImage>
#include <QtOpenGL>
#include "typedefs.h"
#include "common.h"
#include "renderer/text.h"

#ifdef DEBUG
#include <iostream>
#endif

namespace visualizer
{

  struct Coord
  {
    Coord()
    {
      x = y = z = 0;
    }

    Coord( const float& X, const float& Y, const float& Z = 0.0f )
    {
      x = X;
      y = Y;
      z = Z;
    }

    float x;
    float y;
    float z;
  };

  struct Rect
  {
    Coord upLeft, upRight, bottomLeft, bottomRight;
  };

  class Resource
  {
    public:
      /** Default constructor */
      Resource(ResourceType type)
      {
        m_type = type;
      }

      /** Default destructor */
      ~Resource(){}

      bool unload()
      {
        return true;
      }

      ResourceType type()
      {
        return m_type;
      }

      inline bool isReferencedBy(const std::string & referencer)
      {
        if (m_references.find(referencer) != m_references.end())
        {
          return true;
        }
        return false;
      }

      inline std::set<std::string> referenceList()
      {
        return m_references;
      }

      inline unsigned int numReferences()
      {
        return m_references.size();
      }

    #ifdef DEBUG
      void printReferences()
      {
        std::cout << "References:\n"
          for (std::set<std::string>::iterator it = m_references.begin();
          it != m_references.end(); it++)
        {
          std::cout << *it << '\n';
        }
      }
    #endif

      inline bool reference(const std::string & referencer)
      {
        if (!isReferencedBy(referencer))
        {
          m_references.insert(referencer);
          return true;
        }

      #ifdef DEBUG
        std::cout << "Referencer: \"" << reference << "\" already exists\n";
      #endif
        return false;
      }

      inline bool deReference(const std::string & referencer)
      {
        if (isReferencedBy(referencer))
        {
          m_references.erase(referencer);
          return true;
        }

      #ifdef DEBUG
        std::cout << "Referencer: \"" << reference << "\" doesn't exist\n";
      #endif
        return false;
      }

    protected:
      ResourceType m_type;
      std::set<std::string> m_references;
      std::string filename;
    private:
  };

  class ResDisplayList: public Resource
  {
    public:
      ResDisplayList()
        : Resource( RT_DISPLAY_LIST )
      { listNum = glGenLists( 1 ); }

      void startList()
      {
        glNewList( listNum, GL_COMPILE );

      }

      void endList()
      {
        glEndList();
      }

      void draw()
      {
        glCallList( listNum );
      }

    private:
      unsigned int listNum;
  };

  class ResFont : public Resource 
  {
    public: 
      ResFont
        ( 
        const Text& font
        )
        : Resource( RS_FONT ), m_font( font )
        {
        }

      const Text& getFont() const
        {
          return m_font;
        }

    private:
      Text m_font;

  };

  class ResTexture : public Resource
  {
    protected:
      QImage texture;
      unsigned int texId;
    public:
      const QImage& getQImage() const 
      { 
        return texture; 
      }

      ResTexture() 
        : Resource(RT_TEXTURE), texId(0)
      {}

      ResTexture(const QImage &image, const int& id )
        : Resource(RT_TEXTURE), texId( id )
      {
        texture = image;
      }

      size_t getWidth()
      {
        return texture.width();
      }

      size_t getHeight()
      {
        return texture.height();
      }

      int getTexture()
      {
        return texId;
      }
  };

  class ResAnimation : public ResTexture 
  {
    public:
      ResAnimation() 
        : ResTexture()
      {}

      ResAnimation
        ( 
        const QImage& image, 
        const int& id, 
        const size_t& rWidth,
        const size_t& rHeight, 
        const size_t& frames
        ) : ResTexture( image, id ), width( rWidth ), height( rHeight ), numFrames( frames )
      {}
    
      Rect calcTexCoord( const int& frame ) const
      {
        if( frame >= numFrames )
        {
          THROW
            (
            Exception,
            "Animation Frame Out of Bounds"
            );
        }

        int tileX = (int)( texture.width()/width );
        //int tileY = (int)( texture.height()/height );
        int yPos = (int)frame/tileX;
        int xPos = frame-yPos*tileX;
        Rect tRect;
        // Might have to do textureWidth - each of these
        // because of how png stores textures
        tRect.upLeft = Coord( xPos*width, yPos*height );
        tRect.upRight = Coord( (xPos+1)*width, yPos*height );
        tRect.bottomRight = Coord( (xPos+1)*width, (yPos+1)*height );
        tRect.bottomLeft = Coord( xPos*width, (yPos+1)*height );

        return tRect;
      }

      size_t frames() const
      {
        return numFrames;
      }
      
    private:
      size_t width, height;
      size_t numFrames;

  };

} // visualizer

#endif                           // RESOURCE_H
