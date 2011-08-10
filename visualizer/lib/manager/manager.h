#ifndef MANAGER_H
#define MANAGER_H

#include "common.h"
#include <map>

namespace visualizer
{

/**
 * This is the class where most manager functionality should
 * be derrived from (A manager is a souped up map class, with special singleton powers)
 */
template < typename IdType, typename DataType >
class _Manager : public Module
{
  public:

    typedef std::map<IdType,DataType> DataTable;
    bool reg(const IdType & id, const DataType & data);
    bool del(const IdType & id);
    bool delPointer(const IdType & id);

    bool exists(const IdType & id);
    void clear();
    void clearPointers();
    unsigned int size();

    DataType * getItem(const IdType & id);
    bool setItem(const IdType & id);

    DataTable * data() { return &m_data; }

  protected:
    DataTable m_data;
    //typedef Singleton < ManagerBase<IdType,DataType> > ManagerSingleton;
    //typedef ManagerBase<IdType,DataType> BaseType;
    typedef _Manager<IdType,DataType> ManagerType;
    //typedef std::map<IdType,DataType> DataTable;
  private:
};

} // visualizer

#include "manager.hpp"

#endif                           // MANAGER_H
