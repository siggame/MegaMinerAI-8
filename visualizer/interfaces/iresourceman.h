#ifndef IRESOURCEMAN_H
#define IRESOURCEMAN_H

#include <vector>
#include <string>
#include "../lib/resourcemanager/resource.h"
#include <QtPlugin>

namespace visualizer
{

class IResourceMan
{
  public:
    virtual Resource* reference( const std::string& rName, const std::string& referencer ) = 0;
    virtual bool release( const std::string& rName, const std::string& references ) = 0;

    virtual bool regFile( const ResID_t& rName, const std::string& filename ) = 0;
    virtual bool del( const ResID_t& rName ) = 0;

    virtual bool loadResourceFile( const std::string& filename ) = 0;
    virtual bool saveResourceFile( const std::string& filename ) = 0;

    virtual bool exists( const ResID_t& rName ) = 0;
    virtual std::vector<std::string> listResourceNames() = 0;

    virtual void loadTexture
      ( 
      const std::string& filename, 
      const std::string& name 
      )= 0;

    virtual void loadTexture
      ( 
      QImage& image, 
      const std::string& name 
      ) = 0;

    virtual void loadFont
      ( 
      const std::string& fontWidths, 
      const std::string& fontTexture, 
      const std::string& name
      ) = 0;

};

} // visualizer

Q_DECLARE_INTERFACE( visualizer::IResourceMan, "siggame.vis2.resourceman/0.1" );

#endif
