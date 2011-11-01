#ifndef RESOURCEMAN_H
#define RESOURCEMAN_H

#include "../manager/manager.h"
#include "iresourceman.h"
#include "itextureloader.h"
#include <map>

namespace visualizer
{

/** @todo merge this into the options manager... maybe **/

class _ResourceMan : protected _Manager< ResID_t, Resource* >, public IResourceMan
{
  Q_INTERFACES( IResourceMan );
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

    void loadTexture( const std::string& filename, const std::string& name );
    void loadAnimation( const std::string& filename, const std::string& name );
    void loadTexture( QImage& image, const std::string& name );
    void loadFont( const std::string& fontWidths, const std::string& fontTexture, const std::string& name );
    void newDisplayList( const std::string& name );

    static void setup();
    static void destroy();

    bool exists(const ResID_t & rName);

    std::vector<std::string> listResourceNames();

  protected:
  private:

    ResourceType findFileType(const std::string & filename);

};

extern _ResourceMan *ResourceMan;

} // visualizer

#endif                           // RESOURCEMAN_H
