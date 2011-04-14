#ifndef OBJECTLOADER_H
#define OBJECTLOADER_H
#include "../singleton.h"
#include <string>

class ObjectLoader : public Singleton<ObjectLoader>
{
public:
    //! @todo load definitions file for translation
    // bool loadDefs(const std::string & filename);

    bool loadGamelog(const std::string & filename);

private:
    //! @todo make this object-v
    //LoadLogic m_logic;
};

#endif // OBJECTLOADER_H
