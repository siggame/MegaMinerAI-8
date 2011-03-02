#ifndef OPTIONSMAN_H
#define OPTIONSMAN_H

#include "option.h"
#include "../singleton.h"
#include "../mutex/Mutex.h"
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>


class optionsMan : public Singleton <optionsMan>
{
	public:

		static bool loadOptionFile(const std::string & filename);
		static bool saveOptionFile(const std::string & filename);

		OptionBase * operator()(const std::string & oName);

		static bool exists(const std::string & oName);

		static int getInt(const std::string & oName);
		static void setInt(const std::string & oName,const int & val);

		static float getFloat(const std::string & oName);
		static void setFloat(const std::string & oName,const float & val);

		static bool getBool(const std::string & oName);
		static void setBool(const std::string & oName,const bool & val);

		static std::string getStr(const std::string & oName);
		static void setStr(const std::string & oName,const std::string & val);

		static OptionType optionType(const std::string & oName);

		static bool destroy();

	protected:
	private:
		template<class T, OptionType OT>
		static T getVar(const std::string & oName);

		template<class T, OptionType OT>
		static void setVar(const std::string & oName, const T & val);

		static bool strToBool(const std::string & val);

		static OptionType getTypeFromStr(const std::string & val);

		//Helper Fxns for readability
		static bool addString(const std::string & namebuff, std::stringstream & ss, const unsigned int & lineNum);
		static bool addInt(const std::string & namebuff, std::stringstream & ss, const unsigned int & lineNum);
		static bool addFloat(const std::string & namebuff, std::stringstream & ss, const unsigned int & lineNum);
		static bool addBool(const std::string & namebuff, std::stringstream & ss, const unsigned int & lineNum);


		std::map<std::string, OptionBase* > m_options; //!< Member variable "m_options"
};

#endif // OPTIONSMAN_H
