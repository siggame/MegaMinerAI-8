#include "resourceman.h"

/** @brief listResourceNames
  * get a list of all of the resources
  * @return a list of all of the ids of the resources
  */
std::vector<ResID_t> ResourceMan::listResourceNames()
{
	if (!isInit())
	{
		return std::vector<ResID_t>();
	}

    std::vector<ResID_t> names;
    DataTable::iterator it = get()->data()->begin();
    for (it; it != get()->data()->end(); it++)
    {
        names.push_back(it->first);
    }
    return names;
}

/** @brief exists
  * check if an object exists
  * @param rName the name of the resource in question
  * @return true if it exists
  */
bool ResourceMan::exists(const ResID_t & rName)
{
    return ManagerType::exists(rName);
}

/** @brief saveResourceFile
  * save the resources to a file
  * @param filename the name of the file to save to
  * @return true if it is successful
  */
bool ResourceMan::saveResourceFile(const std::string & filename)
{

}


/** @brief reg
  * register a value within the resource manager
  * @param rName the name to regster the value at
  * @param value the value to register
  * @return true if the value didnt previously exist
  */
template<class T, ResourceType RT>
bool ResourceMan::reg(const ResID_t & rName, const T & value)
{
	if (!exists(rName))
    {
        //load File


        return true;
    }

	#ifdef DEBUG
    std::cout << "Resource name conflict. Name: \"" << rName << "\" already exists\n";
    #endif
    return false;
}







/** @brief del
  *	delete a value from the resource manager
  * @param rName the value to delete
  * @return true if it existed
  */
bool ResourceMan::del(const ResID_t & rName)
{
    if (!exists(rName))
    {
        return false;
    }

    DataTable * dt = get()->data();
    Resource * ref = (*(dt))[rName];
    if (ref->numReferences())
    {
        #ifdef DEBUG
        std::cout << "Resource \"" << rName << "\" still has a reference:\n";
        ref->printReferences();
        #endif
        return false;
    }


    return delPointer(rName);
}

/** @brief destroy
  * destroy the resource manager
  * @return true on success
  */
bool ResourceMan::destroy()
{
	if (!isInit())
	{
		return false;
	}
	DataTable::iterator it = get()->data()->begin();
    for (; it != get()->data()->end(); )
    {
        
        if (it->second->numReferences())
        {
			#ifdef DEBUG
            std::cout << "Resource \"" << it->first << "\" still has a reference:\n";
            it->second->printReferences();
			#endif
            return false;
        }
        

		if (!it->second->unload())
			return false;
		
		delete it->second;

    }

    return ManagerType::destroy();
}


