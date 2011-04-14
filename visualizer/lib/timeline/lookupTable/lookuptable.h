#ifndef LOOKUPTABLE_H
#define LOOKUPTABLE_H
#include <vector>
#include <map>
#include <cstdlib>

//! @todo move shit to .hpp
template <typename T, typename idtype = unsigned int>
struct LookupNode
{

	LookupNode()
	{
		prev = NULL;
		next = NULL;
	}

	LookupNode(const T & t)
	{
		prev = NULL;
		next = NULL;
		data = t;
	}

	LookupNode(const T & t,LookupNode<T> * p, LookupNode<T> * n)
	{
		prev = p;
		next = n;
		data = t;
	}

	LookupNode<T> *prev, *next;
	T data;

};


template <typename T, typename idtype = unsigned int>
class LookupSet
{
public:
    LookupSet(const unsigned int & frames, const unsigned int & turns, const idtype & id)
    {
	m_set.resize(frames*turns);
	m_frames = frames;
	m_turns = turns;

	for (unsigned int i = 0; m_set.size > i; i++)
	{
	    m_set[i] = NULL;
	}
	m_id = id;
    }

    bool addNode(const T & data, const unsigned int & frame, const unsigned int & turn)
    {
	 if (frame >= m_frames || turn >= m_turns)
		return false;

	 if (m_set[frame*m_turns + turn])
	     return false;

	 m_set[frame*m_turns + turn] = new LookupNode<T,idtype>(data);


	 LookupNode<T,idtype> prev;
	 LookupNode<T,idtype> next;

	 for (int i = frame*m_turns + turn-1; i > -1; i--)
	 {
	    if (m_set[i])
		prev = m_set[i];
	 }

	 for (unsigned int i = frame*m_turns + turn+1; i < m_set.size(); i++)
	 {
	    if (m_set[i])
		next = m_set[i];
	 }

	 m_set[frame*m_turns+turn]->prev = prev;
	 m_set[frame*m_turns+turn]->next = next;


	 return true;
    }

    bool addNode(const LookupNode<T,idtype> *& node, const unsigned int & turn, const unsigned int & frame  )
    {
	if (frame >= m_frames || turn >= m_turns)
	       return false;

	if (m_set[frame*m_turns + turn])
	    return false;

	m_set[frame*m_turns + turn] = node;

	return true;
    }

    idtype id()
    {
	return m_id;
    }

private:
    std::vector<LookupNode<T,idtype>*> m_set;
    unsigned int m_frames, m_turns;
    idtype m_id;
    friend class LookupTable;
};



template <typename T, typename idtype = unsigned int>
class LookupTable
{
	public:
		typedef std::vector< std::map<idtype,LookupNode<T,idtype>* > > Table;
		typedef std::map< idtype, LookupNode <T,idtype>* > Bucket;
		typedef LookupNode<T,idtype> Node;
		typedef LookupSet<T,idtype> Set;

		/** Default constructor */
		LookupTable(const unsigned int & turns, const unsigned int & frames);
		LookupTable();

		void setSize(const unsigned int & turns, const unsigned int & frames);
		int getTurns();
		int getFrames();

		void clear();

		void add(const unsigned int & turn, const unsigned int & frame, const idtype & id, const Node & input);
		void add(const Set & set);

		Node * node(const unsigned int & turn, const unsigned int & frame, const idtype & id);
		Bucket * bucket(const unsigned int & turn, const unsigned int & frame);

		/** Default destructor */
		virtual ~LookupTable();

	protected:
		Table m_table;
		unsigned int m_frames;
		unsigned int m_turns;
	private:
};

#include "lookuptable.hpp"
#endif // LOOKUPTABLE_H
