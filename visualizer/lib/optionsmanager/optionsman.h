#ifndef OPTIONSMAN_H
#define OPTIONSMAN_H

#include "../mutex/Mutex.h"
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include "common.h"

#include "../../interfaces/ioptionsman.h"

namespace visualizer
{

class _OptionsMan: public IOptionsMan
{
  public:

    bool loadOptionFile(const std::string & filename);
    bool saveOptionFile(const std::string & filename);

    OptionBase * operator()(const OptID_t & oName);

    bool exists(const OptID_t & oName);

    int getInt(const OptID_t & oName);
    void setInt(const OptID_t & oName,const int & val);

    float getFloat(const OptID_t & oName);
    void setFloat(const OptID_t & oName,const float & val);

    bool getBool(const OptID_t & oName);
    void setBool(const OptID_t & oName,const bool & val);

    std::string getStr(const OptID_t & oName);
    void setStr(const OptID_t & oName,const std::string & val);

    OptionType optionType(const OptID_t & oName);

    bool destroy();

    //general adding functions
    bool addString(const OptID_t & oName, const std::string & val);
    bool addInt(const OptID_t & oName, const int & val);
    bool addFloat(const OptID_t & oName, const float & val);
    bool addBool(const OptID_t & oName, const bool & val);

    static void setup();

  protected:
  private:
    template<class T, OptionType OT>
      T getVar(const OptID_t & oName);

    template<class T, OptionType OT>
      void setVar(const OptID_t & oName, const T & val);

    bool strToBool(const std::string & val);

    OptionType getTypeFromStr(const std::string & val);

    //helper fxns
    bool addString(const OptID_t & oName, std::stringstream & ss, const unsigned int & lineNum);
    bool addInt(const OptID_t & oName, std::stringstream & ss, const unsigned int & lineNum);
    bool addFloat(const OptID_t & oName, std::stringstream & ss, const unsigned int & lineNum);
    bool addBool(const OptID_t & oName, std::stringstream & ss, const unsigned int & lineNum);

                                 //!< Member variable "m_options"
    std::map<OptID_t, OptionBase* > m_options;
};

extern _OptionsMan *OptionsMan;

} // visualizer

#endif                           // OPTIONSMAN_H
