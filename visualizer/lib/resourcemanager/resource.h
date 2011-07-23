#ifndef RESOURCE_H
#define RESOURCE_H
#include <set>
#include <string>
#include <QImage>
#include "typedefs.h"

#ifdef DEBUG
#include <iostream>
#endif

namespace visualizer
{

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

  class ResTexture : public Resource
  {
    private:
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

      ResTexture(const QImage &image )
        : Resource(RT_TEXTURE)
      {
        texture = image;
      }

      int getWidth()
      {
        return texture.width();
      }

      int getHeight()
      {
        return texture.height();
      }

      int getTexture()
      {
        return texId;
      }
  };


} // visualizer

#endif                           // RESOURCE_H
