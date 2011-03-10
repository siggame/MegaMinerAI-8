#ifndef MANAGER_H
#define MANAGER_H

#include "../singleton.h"
#include <map>

/**
  *This is just a helper class because I cant get it to work any other way, ignore this
  *
  */
template < typename IdType, typename DataType >
class ManagerBase
{
	template <typename idType = IdType,typename dataType = DataType>
	friend class Manager;
	typedef std::map<IdType,DataType> DataTable;
	DataTable m_data;
	public:
	DataTable * data(){return &m_data;}
};


/**
  * This is the class where most manager functionality should
  * be derrived from (A manager is a souped up map class, with special singleton powers)
  */
template < typename IdType, typename DataType >
class Manager : public Singleton < ManagerBase<IdType,DataType> >
{
	public:

		static bool reg(const IdType & id, const DataType & data);
		static bool del(const IdType & id);
		static bool delPointer(const IdType & id);

		static bool exists(const IdType & id);
		static void clear();
		static void clearPointers();
		static unsigned int size();

		static DataType * getItem(const IdType & id);
		static bool setItem(const IdType & id);

	protected:
		typedef Singleton < ManagerBase<IdType,DataType> > ManagerSingleton;
		typedef ManagerBase<IdType,DataType> BaseType;
		typedef Manager<IdType,DataType> ManagerType;
		typedef std::map<IdType,DataType> DataTable;
	private:
};

#include "manager.hpp"

#endif // MANAGER_H
