// if this were for windows only I would make this file a DLL
//but it isn't, so I'm forced to make this just a seperate .cpp 
//for ease of editing
// 	~Alex Shepard
//	aksfkb@mst.edu

#include "resourceman.h"
#include "texture.h"


/** @brief loadResourceFile
  * load a resource file
  * @param filename the name of the file to load from
  * @return true on success
  */
bool ResourceMan::loadResourceFile(const std::string & filename)
{
}


/** @brief reg
  * register a value from a file
  * @param rName the id to register the resource with
  * @param filename the value exists at (ex: mypic.png)
  * @return true if the file load was successful and the id didnt exist
  */
bool ResourceMan::regFile(const ResID_t & rName, const std::string & filename)
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
