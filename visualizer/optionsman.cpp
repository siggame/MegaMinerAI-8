#include "optionsman.h"

/** @brief exists
  * check to see if the string is a valid option name
  * @param oName The name of the option to check
  * @return true if it exists
  */
bool optionsMan::exists(const std::string & oName)
{
	if (!isInit())
		return false;


	if (get()->m_options.find(oName) != get()->m_options.end())
	{
		return true;
	}
	return false;
}

/** @brief operator()
  *	Directly access an option's pointer
  * @param oName the name of the option to access
  * @return a pointer to the option if it exists, otherwise NULL
  */
OptionBase * optionsMan::operator()(const std::string & oName)
{
	if (exists(oName))
		return get()->m_options[oName];

	return NULL;
}

/** @brief loadOptionFile
  * this loads in an option file to the singleton
  * @param filename the option file to load
  * @return true if all goes well
  * @todo: clean this function up a bit
  */
bool optionsMan::loadOptionFile(const std::string & filename)
{
	if (!isInit())
	{
		return false;
	}

	/* if we allow multiple loading we can combine files easily
	if (get()->m_options.size())
	{
		//obviously this is the second time you are loading the damn thing
		return false;
	}*/

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
        //2 different line carriages because windows is strange
		if (buffer.c_str()[0] != '#' && buffer.c_str()[0] != '\n' && buffer.c_str()[0] != (char)13)
		{
			ss << buffer;
			std::string typebuff;
			std::string namebuff;

			if (ss >> namebuff)
			{
				if (!exists(namebuff))
				{
					if (ss >> typebuff)
					{
						if (typebuff == "int")
						{
							int val;

                           if (ss >> val)
							{
							    get()->m_options[namebuff] = new Option<int,OT_INT>(val);
                                if (Mutex::isInit())
                                {
                                    Mutex::createMutex(namebuff);
                                }
							}
							else
							{
								std::cout << "Option Load Error Line "<< lineNum << ": Invalid integer value\n";
							}
						}
						else if (typebuff == "float")
						{
							float val;
							if (ss >> val)
							{
								get()->m_options[namebuff] = new Option<float,OT_FLOAT>(val);
                                if (Mutex::isInit())
                                {
                                    Mutex::createMutex(namebuff);
                                }
							}
							else
							{
								std::cout << "Option Load Error Line "<< lineNum << ": Invalid float value\n";
							}
						}
						else if (typebuff == "string")
						{
							std::string val;
							if (ss >> val)
							{
							    while (!ss.eof())
							    {
							        std::string tmp;
							        ss>>tmp;
							        val += std::string(" ") + tmp;
							    }


								get()->m_options[namebuff] = new Option<std::string,OT_STRING>(val);
                                if (Mutex::isInit())
                                {
                                    Mutex::createMutex(namebuff);
                                }
							}
							else
							{
								std::cout << "Option Load Error Line "<< lineNum << ": Invalid ...string value? How did you pull that one off?\n";
							}
						}
						else if (typebuff == "bool")
						{
							std::string valbuff;
							if (ss >> valbuff)
							{
								// all true posibilities
								if (valbuff == "yes" || valbuff == "Yes" || valbuff == "YES" ||
									valbuff == "true" || valbuff == "True" || valbuff == "TRUE" ||
									valbuff == "on" || valbuff == "On" || valbuff == "ON"||
									valbuff == "y" ||valbuff == "Y"||valbuff == "t" ||valbuff == "T")
								{
									get()->m_options[namebuff] = new Option<bool,OT_BOOL>(true);
									if (Mutex::isInit())
									{
									    Mutex::createMutex(namebuff);
									}
								}//all false posibilities
								else if (valbuff == "no" || valbuff == "No" || valbuff == "NO" ||
									valbuff == "false" || valbuff == "False" || valbuff == "FALSE" ||
									valbuff == "off" || valbuff == "Off" || valbuff == "OFF"||
									valbuff == "n" ||valbuff == "N"||valbuff == "f" ||valbuff == "F")
								{
									get()->m_options[namebuff] = new Option<bool,OT_BOOL>(false);
                                    if (Mutex::isInit())
									{
									    Mutex::createMutex(namebuff);
									}
								}
								else
								{
									std::cout << "Option Load Error Line "<< lineNum << ": \"" << valbuff << "\" is not a valid bool value\n";
								}
							}
							else
							{
								std::cout << "Option Load Error Line "<< lineNum << ": Invalid bool value\n";
							}
						}
					}
					else
					{
						std::cout << "Option Load Error Line "<< lineNum << ": \"" << typebuff << "\" is not a type\n";
					}
				}
				else
				{
					std::cout << "Option Load Error Line "<< lineNum << ": Option name already exists\n";
				}
			}
			else
			{
				std::cout << "Option Load Error Line "<< lineNum << ": Name buffer read error\n";
			}
		}
		}

		lineNum++;
	}

	input.close();
	return true;
}


/** @brief saveOptionFile
  *	save all of your options to file
  * @param filename the name of the file to save the options into
  * @return true if all goes well
  * @todo find a way to maintain comments and white space
  * @todo better error checking
  */
bool optionsMan::saveOptionFile(const std::string & filename)
{
	if (!isInit())
	{
		return false;
	}

	std::ofstream output(filename.c_str());

	std::map<std::string,OptionBase*>::iterator it = get()->m_options.begin();

	for (it; it != get()->m_options.end(); it++)
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
		}

	}

	return true;
}


/** @brief ~optionsMan
  * default destructor
  * @todo get rid of or find a use for this
  */
 optionsMan::~optionsMan()
{

}

/** @brief optionsMan
  * default constructor
  * @todo get rid of or find a use for this
  */
 optionsMan::optionsMan()
{

}

/** @brief setStr
  * set a string option to the intended value
  * @param oName the name of the option to be modified
  * @param val the value to change the option to
  */
void optionsMan::setStr(const std::string & oName,const std::string & val)
{
	setVar<std::string,OT_STRING>(oName,val);
}

/** @brief getStr
  * get the value of a string option
  * @param oName the name of the option
  * @return the value of the option or a default variable value if it
		doesnt exist
  */
std::string optionsMan::getStr(const std::string & oName)
{
	return getVar<std::string,OT_STRING>(oName);
}

/** @brief setBool
  * set a bool option to the intended value
  * @param oName the name of the option to be modified
  * @param val the value to change the option to
  */
void optionsMan::setBool(const std::string & oName,const bool & val)
{
	setVar<bool,OT_BOOL>(oName,val);
}

/** @brief getBool
  * get the value of a bool option
  * @param oName the name of the option
  * @return the value of the option or a default variable value if it
		doesnt exist
  */
bool optionsMan::getBool(const std::string & oName)
{
	return getVar<bool,OT_BOOL>(oName);
}

/** @brief getFloat
  * get the value of a float option
  * @param oName the name of the option
  * @return the value of the option or a default variable value if it
		doesnt exist
  */
float optionsMan::getFloat(const std::string & oName)
{
	return getVar<float,OT_FLOAT>(oName);
}

/** @brief setInt
  * set an integer option to the intended value
  * @param oName the name of the option to be modified
  * @param val the value to change the option to
  */
void optionsMan::setInt(const std::string & oName,const int & val)
{
	setVar<int,OT_INT>(oName,val);
}

/** @brief getInt
  * get the value of a integer option
  * @param oName the name of the option
  * @return the value of the option or a default variable value if it
		doesnt exist
  */
int optionsMan::getInt(const std::string & oName)
{
	return getVar<int,OT_INT>(oName);
}

/** @brief setFloat
  * set a float option to the intended value
  * @param oName the name of the option to be modified
  * @param val the value to change the option to
  */
void optionsMan::setFloat(const std::string & oName,const float & val)
{
	setVar<float,OT_FLOAT>(oName,val);
}

/** @brief optionType
  * get the type of the option in question
  * @param oName the name of the option
  * @return the type of the option if it exists, otherwise OT_NONE
  */
OptionType optionsMan::optionType(const std::string & oName)
{
	if (exists(oName))
		return get()->m_options[oName]->type();

	return OT_NONE;
}

/** @brief destroy
  * destroy the options manager
  * @return true if all goes well
  */
bool optionsMan::destroy()
{
	if (!isInit())
		return false;

	std::map<std::string, OptionBase*>::iterator it = get()->m_options.begin();

	for (it; it != get()->m_options.end(); it++)
	{
		delete it->second;
	}

	return Singleton<optionsMan>::destroy();
}

/** @brief getInt
  * get the value of a integer option
  * @param oName the name of the option
  * @return the value of the option or a default variable value if it
		doesnt exist
  */
template<class T, OptionType OT>
T optionsMan::getVar(const std::string & oName)
{
	if (!exists(oName))
	{
		std::cout << "Getting invalid string option \"" << oName << "\"\n";
		return T();
	}

	if (optionType(oName) != OT)
	{
		std::cout << "Getting option \"" << oName << "\" of wrong type: string\n";
		return T();
	}

	Mutex::lock(oName);
	T temp (((Option<T,OT>*)(get()->m_options[oName]))->get());;
	Mutex::unlock(oName);
	return temp;
}

/** @brief setVar
  * set an option to the intended value
  * @param oName the name of the option to be modified
  * @param val the value to change the option to
  */
template<class T, OptionType OT>
void optionsMan::setVar(const std::string & oName, const T & val)
{
	if (!exists(oName))
	{
		std::cout << "Setting invalid float option \"" << oName << "\"\n";
		return;
	}

	if (optionType(oName) != OT)
	{
		std::cout << "Setting option \"" << oName << "\" to wrong type\n";
		return;
	}

	Mutex::lock(oName);
	((Option<T,OT>*)(get()->m_options[oName]))->set(val);
	Mutex::unlock(oName);
}


