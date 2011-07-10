#ifndef RESOURCEMAN_H
#define RESOURCEMAN_H

#include "../manager/manager.h"
#include "../../interfaces/iresourceman.h"
#include <map>

/** @todo merge this into the options manager... maybe **/

class _ResourceMan : protected _Manager< ResID_t, Resource* >, public IResourceMan
{
  public:
    /** Default constructor */
    _ResourceMan()
    {
    };
    /** Default destructor */
    ~_ResourceMan() {};

    Resource * reference(const std::string & rName, const std::string & referencer);
    bool release(const std::string & rName, const std::string & referencer);

    //template<class T, ResourceType RT>
    //    bool reg(const ResID_t & rName, const T & value);
    bool regFile(const ResID_t & rName, const std::string & filename);
    bool del(const ResID_t & rName);

    bool loadResourceFile(const std::string & filename);
    bool saveResourceFile(const std::string & filename);

    static void setup();
    static void destroy();

    bool exists(const ResID_t & rName);

    std::vector<std::string> listResourceNames();

  protected:
  private:

    ResourceType findFileType(const std::string & filename);

};

extern _ResourceMan *ResourceMan;
#endif                           // RESOURCEMAN_H
