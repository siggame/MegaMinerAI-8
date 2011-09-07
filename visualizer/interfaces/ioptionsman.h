#ifndef IOPTIONSMAN_H
#define IOPTIONSMAN_H

#include "../lib/optionsmanager/option.h"
#include <string>
#include <QtPlugin>

namespace visualizer
{

  typedef std::string OptID_t;

  class IOptionsMan
  {
    public:
      virtual bool loadOptionFile( const std::string& filename ) = 0;
      virtual bool saveOptionFile( const std::string& filename ) = 0;
      virtual OptionBase* operator() ( const OptID_t& oName ) = 0;

      virtual bool exists( const OptID_t& oName ) = 0;
      virtual OptionType optionType( const OptID_t& oName ) = 0;

      virtual bool addString( const OptID_t& oName, const std::string& val ) = 0;
      virtual bool addInt( const OptID_t& oName, const int& val ) = 0;
      virtual bool addFloat( const OptID_t& oName, const float& val ) = 0;
      virtual bool addBool( const OptID_t& oName, const bool& val ) = 0;

      virtual const int& getInt( const OptID_t& oName ) = 0;
      virtual const float& getFloat( const OptID_t& oName ) = 0;
      virtual const bool& getBool( const OptID_t& oName ) = 0;
      virtual const std::string& getStr( const OptID_t& oName ) = 0;

      virtual void setInt( const OptID_t& oName, const int& val ) = 0;
      virtual void setFloat( const OptID_t& oName, const float& val ) = 0;
      virtual void setBool( const OptID_t& oName, const bool& val ) = 0;
      virtual void setStr( const OptID_t& oName, const std::string& val ) = 0;

  }; // IOptionsMan

} // visualizer

Q_DECLARE_INTERFACE( visualizer::IOptionsMan, "siggame.vis2.optionsman/0.1" );

#endif
