#include "optionsman.h"
#include <iostream>

/// @TODO Move documentation into the header file
namespace visualizer
{

  _OptionsMan *OptionsMan = 0;

  /** @brief exists
   * check to see if the string is a valid option name
   * @param oName The name of the option to check
   * @return true if it exists
   */
  bool _OptionsMan::exists(const std::string & oName)
  {
    if ( m_options.find(oName) != m_options.end() )
    {
      return true;
    }
    return false;
  }


  void _OptionsMan::setup()
  {
    if( !OptionsMan )
    {
      OptionsMan = new _OptionsMan;
    } else
    {
      THROW( Exception, "Options Manager is already initialized" );
    }
  }


  /** @brief operator()
   *	Directly access an option's pointer
   * @param oName the name of the option to access
   * @return a pointer to the option if it exists, otherwise NULL
   */
  OptionBase * _OptionsMan::operator()(const std::string & oName)
  {
    if (exists(oName))
      return m_options[oName];

    return NULL;
  }


  /** @brief loadOptionFile
   * this loads in an option file to the singleton
   * @param filename the option file to load
   * @return true if all goes well
   * @todo: clean this function up a bit
   */
  bool _OptionsMan::loadOptionFile(const std::string & filename)
  {

    std::ifstream input(filename.c_str());

    if (input.eof())
    {
      return false;
    }

    std::string buffer;
    unsigned int lineNum = 1;
    while (!input.eof())
    {
      std::stringstream ss;

      getline(input,buffer);

      if (buffer.size())
      {
        if( buffer[ 0 ] == '#' )
        {
          // Store comment
        }

        //2 different line carriages because windows is strange
        else if( buffer[0] != '\n' && buffer[0] != (char)13)
        {
          ss << buffer;
          string n;
          ss >> n;
          cout << n << endl;
          ss >> n;
          cout << n << endl;

          
#if 0
          ss << buffer;
          std::string typebuff;
          std::string namebuff;

          ss >> typebuff;
          OptionType ot = getTypeFromStr(typebuff);

          if (ss >> namebuff)
          {
            if (!exists(namebuff))
            {
              switch (ot)
              {
                case OT_INT:
                  addInt(namebuff,ss,lineNum);
                  break;
                case OT_FLOAT:
                  addFloat(namebuff,ss,lineNum);
                  break;
                case OT_STRING:
                  addString(namebuff,ss,lineNum);
                  break;
                case OT_BOOL:
                  addBool(namebuff,ss,lineNum);
                  break;
                default:
                  THROW
                    (
                      Exception,
                      "Option Load Error Line %d: \"%s\" is not a type.", 
                      lineNum, typebuff.c_str()
                    );
              }
            }
            else
            {
              THROW
                (
                  Exception,
                  "Option Load Error Line %d: Option name already exists.", lineNum
                );
            }
          }
          else
          {
            THROW
              (
                Exception,
                "Option Load Error Line %d: Name buff read error.", lineNum
              )
          }
#endif
        }
      }

      lineNum++;
    }

    input.close();
    return true;
  }


  /** @brief getTypeFromStr
   * Helper function to get the enum type from a string
   * @param val the value to attempt to get an enum from
   * @return OT_INT, OT_FLOAT, OT_STRING, or OT_BOOL when valid. OT_NONE when not valid
   */
  OptionType _OptionsMan::getTypeFromStr(const std::string & val)
  {
    if (val == "float")
    {
      return OT_FLOAT;
    }
    if (val == "int")
    {
      return OT_INT;
    }
    if (val == "bool")
    {
      return OT_BOOL;
    }
    if (val == "string")
    {
      return OT_STRING;
    }

    return OT_NONE;
  }


  /** @brief strToBool
   * helper function to get the bool value from a set of possible strings
   * @param val the value to find a bool from
   * @return true or false if valid, will throw an exception of type std::string on failure
   */
  bool _OptionsMan::strToBool(const std::string & val)
  {
    if (val == "yes" || val == "Yes" || val == "YES" ||
      val == "true" || val == "True" || val == "TRUE" ||
      val == "on" || val == "On" || val == "ON"||
      val == "y" ||val == "Y"||val == "t" ||val == "T")
    {
      return true;
    }
    else if (val == "no" || val == "No" || val == "NO" ||
      val == "false" || val == "False" || val == "FALSE" ||
      val == "off" || val == "Off" || val == "OFF"||
      val == "n" ||val == "N"||val == "f" ||val == "F")
    {
      return false;
    }

    THROW( Exception, "Invalid bool value" ) ;
  }


  /** @brief addBool
   *	helper function to extract a bool from a string stream and give it a name
   * @param namebuff the name that will be given the bool
   * @param ss the string stream to pull the bool value from
   * @param lineNum the number of the line this is happening on
   * @return true on a success otherwise false
   */
  bool _OptionsMan::addBool(const std::string & namebuff, std::stringstream & ss, const unsigned int & lineNum)
  {
    #if 0
    if (!isInit())
      return false;
    #endif

    std::string valbuff;
    if (ss >> valbuff)
    {
      try
      {
        bool retval = strToBool(valbuff);
        m_options[namebuff] = new Option<bool,OT_BOOL>(retval);
        //Mutex->createMutex(namebuff);
      }
      catch (std::string s)
      {
        THROW
          (
            Exception,
            "Option Load Error Line %d: \"%s\" %s", lineNum, valbuff.c_str(), s.c_str()
          );
      }
      return true;
    }

    THROW
      (
        Exception,
        "Option Load Error Line %d: Invalid bool value.", lineNum
      );

    return false;

  }


  /** @brief addFloat
   *	helper function to extract a float from a string stream and give it a name
   * @param namebuff the name that will be given the float
   * @param ss the string stream to pull the float value from
   * @param lineNum the number of the line this is happening on
   * @return true on a success otherwise false
   */
  bool _OptionsMan::addFloat(const std::string & namebuff, std::stringstream & ss, const unsigned int & lineNum)
  {
    #if 0
    if (!isInit())
      return false;
    #endif

    float val;
    if (ss >> val)
    {
      m_options[namebuff] = new Option<float,OT_FLOAT>(val);
      //Mutex->createMutex(namebuff);
      return true;
    }

    THROW
      (
        Exception,
        "Option Load Error Line %d: Invalid float value.", lineNum
      );

    return false;
  }


  /** @brief addInt
   *	helper function to extract a int from a string stream and give it a name
   * @param namebuff the name that will be given the int
   * @param ss the string stream to pull the int value from
   * @param lineNum the number of the line this is happening on
   * @return true on a success otherwise false
   */
  bool _OptionsMan::addInt(const std::string & namebuff, std::stringstream & ss, const unsigned int & lineNum)
  {
    #if 0
    if (!isInit())
      return false;
    #endif

    int val;

    if (ss >> val)
    {
      m_options[namebuff] = new Option<int,OT_INT>(val);
      //Mutex->createMutex(namebuff);
      return true;
    }

    THROW
      (
        Exception,
        "Option Load Error Line %d: Invalid integer value.", lineNum
      );

    return false;
  }


  /** @brief addString
   *	helper function to extract a string from a string stream and give it a name
   * @param namebuff the name that will be given the string
   * @param ss the string stream to pull the string value from
   * @param lineNum the number of the line this is happening on
   * @return true on a success otherwise false
   */
  bool _OptionsMan::addString(const std::string & namebuff, std::stringstream & ss, const unsigned int & lineNum)
  {
    #if 0
    if (!isInit())
      return false;
    #endif

    std::string val;
    if (ss >> val)
    {
      while (!ss.eof())
      {
        std::string tmp;
        ss>>tmp;
        val += std::string(" ") + tmp;
      }

      m_options[namebuff] = new Option<std::string,OT_STRING>(val);
      //Mutex->createMutex(namebuff);
      return true;
    }

    THROW
      (
        Exception,
        "Option Load Error Line %d: Invalid ... string value?  How did you pull that one off?", lineNum
      );

    return false;
  }


  /** @brief saveOptionFile
   *	save all of your options to file
   * @param filename the name of the file to save the options into
   * @return true if all goes well
   * @todo find a way to maintain comments and white space
   * @todo better error checking
   */
  bool _OptionsMan::saveOptionFile(const std::string & filename)
  {
    #if 0
    if (!isInit())
    {
      return false;
    }
    #endif

    std::ofstream output(filename.c_str());

    std::map<std::string,OptionBase*>::iterator it = m_options.begin();

    for (; it != m_options.end(); it++)
    {
      OptionType optType = it->second->type();

      output << it->first << " ";

      switch(optType)
      {
        case OT_INT:
          output << "int " << getInt(it->first) << '\n';
          break;

        case OT_STRING:
          output << "string " << getStr(it->first) << '\n';
          break;

        case OT_FLOAT:
          output << "float " << getFloat(it->first) << '\n';
          break;

        case OT_BOOL:
          output << "bool ";
          if ( getBool(it->first) )
          {
            output << "Yes\n";
          }
          else
          {
            output << "No\n";
          }
          break;
        default:                   //shouldn't happen, this is for the warnings
          THROW
          (
            Exception,
            "Error saving options!!: A variable has no type!."
          );
          break;
      }

    }

    return true;
  }


  /** @brief setStr
   * set a string option to the intended value
   * @param oName the name of the option to be modified
   * @param val the value to change the option to
   */
  void _OptionsMan::setStr(const std::string & oName,const std::string & val)
  {
    setVar<std::string,OT_STRING>(oName,val);
  }


  /** @brief getStr
   * get the value of a string option
   * @param oName the name of the option
   * @return the value of the option or a default variable value if it
      doesnt exist
    */
  const std::string& _OptionsMan::getStr(const std::string & oName)
  {
    return getVar<std::string,OT_STRING>(oName);
  }


  /** @brief setBool
   * set a bool option to the intended value
   * @param oName the name of the option to be modified
   * @param val the value to change the option to
   */
  void _OptionsMan::setBool(const std::string & oName,const bool & val)
  {
    setVar<bool,OT_BOOL>(oName,val);
  }


  /** @brief getBool
   * get the value of a bool option
   * @param oName the name of the option
   * @return the value of the option or a default variable value if it
      doesnt exist
    */
  const bool& _OptionsMan::getBool(const std::string & oName)
  {
    return getVar<bool,OT_BOOL>(oName);
  }


  /** @brief getFloat
   * get the value of a float option
   * @param oName the name of the option
   * @return the value of the option or a default variable value if it
      doesnt exist
    */
  const float& _OptionsMan::getFloat(const std::string & oName)
  {
    return getVar<float,OT_FLOAT>(oName);
  }


  /** @brief setInt
   * set an integer option to the intended value
   * @param oName the name of the option to be modified
   * @param val the value to change the option to
   */
  void _OptionsMan::setInt(const std::string & oName,const int & val)
  {
    setVar<int,OT_INT>(oName,val);
  }


  /** @brief getInt
   * get the value of a integer option
   * @param oName the name of the option
   * @return the value of the option or a default variable value if it
      doesnt exist
    */
  const int& _OptionsMan::getInt(const std::string & oName)
  {
    return getVar<int,OT_INT>(oName);
  }


  /** @brief setFloat
   * set a float option to the intended value
   * @param oName the name of the option to be modified
   * @param val the value to change the option to
   */
  void _OptionsMan::setFloat(const std::string & oName,const float & val)
  {
    setVar<float,OT_FLOAT>(oName,val);
  }


  /** @brief optionType
   * get the type of the option in question
   * @param oName the name of the option
   * @return the type of the option if it exists, otherwise OT_NONE
   */
  OptionType _OptionsMan::optionType(const std::string & oName)
  {
    if (exists(oName))
      return m_options[oName]->type();

    return OT_NONE;
  }


  /** @brief destroy
   * destroy the options manager
   * @return true if all goes well
   */
  bool _OptionsMan::destroy()
  {
    std::map<std::string, OptionBase*>::iterator it = m_options.begin();

    for (; it != m_options.end(); it++)
    {
      delete it->second;
    }

    return true;
  }


  /** @brief getInt
   * get the value of a integer option
   * @param oName the name of the option
   * @return the value of the option or a default variable value if it
      doesnt exist
    */
  template<class T, OptionType OT>
  const T& _OptionsMan::getVar(const std::string & oName)
  {
    if (!exists(oName))
    {
      THROW
        (
        Exception,
        "Getting invalid string option \"%s\"", oName.c_str()
        );
    }

    if (optionType(oName) != OT)
    {
      THROW
        (
        Exception,
        "Getting option, \"%s\", of wrong type: string", oName.c_str()
        );
    }

    //Mutex->lock(oName);
    //Mutex->unlock(oName);
    return (((Option<T,OT>*)(m_options[oName]))->get());
  }


  /** @brief setVar
   * set an option to the intended value
   * @param oName the name of the option to be modified
   * @param val the value to change the option to
   */
  template<class T, OptionType OT>
  void _OptionsMan::setVar(const std::string & oName, const T & val)
  {
    if (!exists(oName))
    {
      THROW
        (
          Exception,
          "Object: \"%s\" doesn't exist.", oName.c_str()
        );
      return;
    }

    if (optionType(oName) != OT)
    {
      THROW
        (
          Exception,
          "Setting option \"%s\" to wrong type.", oName.c_str()
        );
      return;
    }

    //Mutex->lock(oName);
    ((Option<T,OT>*)(m_options[oName]))->set(val);
    //Mutex->unlock(oName);
  }


  bool _OptionsMan::addString(const OptID_t & oName, const std::string & val)
  {
    #if 0
    if (!isInit())
      return false;
    #endif

    if (exists(oName))
      return false;

    m_options[oName] = new Option<std::string,OT_STRING>(val);
    //Mutex->createMutex(oName);

    setStr(oName,val);

    return true;
  }


  bool _OptionsMan::addInt(const OptID_t & oName, const int & val)
  {
    #if 0
    if (!isInit())
      return false;
    #endif

    if (exists(oName))
      return false;

    m_options[oName] = new Option<int,OT_INT>(val);
    //Mutex->createMutex(oName);

    setInt(oName,val);

    return true;
  }


  bool _OptionsMan::addFloat(const OptID_t & oName, const float & val)
  {
    #if 0
    if (!isInit())
      return false;
    #endif

    if (exists(oName))
      return false;

    m_options[oName] = new Option<float,OT_FLOAT>(val);
    //Mutex->createMutex(oName);

    setFloat(oName,val);

    return true;
  }


  bool _OptionsMan::addBool(const OptID_t & oName, const bool & val)
  {
    if (exists(oName))
      return false;

    m_options[oName] = new Option<bool,OT_BOOL>(val);
    //Mutex->createMutex(oName);

    setBool(oName,val);

    return true;
  }

} // visualizer

