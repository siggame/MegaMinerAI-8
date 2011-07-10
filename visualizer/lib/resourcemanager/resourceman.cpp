#include "resourceman.h"

_ResourceMan *ResourceMan = 0;

std::vector<ResID_t> _ResourceMan::listResourceNames()
{
  std::vector<ResID_t> names;
  DataTable::iterator it = data()->begin();
  for (; it != data()->end(); it++)
  {
    names.push_back(it->first);
  }
  return names;
}


bool _ResourceMan::exists(const ResID_t & rName)
{
  return ManagerType::exists(rName);
}


bool _ResourceMan::del(const ResID_t & rName)
{
  if (!exists(rName))
  {
    return false;
  }

  DataTable * dt = data();
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


void _ResourceMan::destroy()
{

  DataTable::iterator it = ResourceMan->data()->begin();
  for (; it != ResourceMan->data()->end(); it++)
  {

    //if( it->second )
    if (it->second->numReferences())
    {
      #ifdef __DEBUG__
      //it->second->printReferences();
      #endif
      THROW( Exception, "Resource Manager still contains some references" );
    }

    //if( it->second )
    if (!it->second->unload())
      THROW( Exception, "Problem Unloading ResourceManager" );

    delete it->second;
    it->second = 0;

  }

  delete ResourceMan;
  ResourceMan = 0;

}


Resource * _ResourceMan::reference(const std::string & rName, const std::string & referencer)
{
  Resource ** res = ManagerType::getItem(rName);
  if (!res)
    return NULL;

  if (!*res)
    return NULL;

  if ((*res)->reference(referencer))
    return *res;

  return NULL;

}


void _ResourceMan::setup()
{
  if( !ResourceMan )
  {
    ResourceMan = new _ResourceMan;
  }
  else
  {
    THROW( Exception, "Resource Manager already initialized" );
  }

}


bool _ResourceMan::release(const std::string &rName, const std::string &referencer)
{
  Resource ** res = ManagerType::getItem(rName);

  if (!res)
    return false;

  if (!*res)
    return false;

  if ((*res)->deReference(referencer))
    return true;

  return false;

}
