#ifndef LOOKUPTABLE_H
#define LOOKUPTABLE_H
#include <vector>
#include <map>
#include <cstdlib>


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
class LookupTable
{
	public:
		typedef std::vector< std::map<idtype,LookupNode<T,idtype> > > Table;
		typedef std::map< idtype, LookupNode <T,idtype> > Bucket;
		typedef LookupNode<T,idtype> Node;

		/** Default constructor */
		LookupTable(const unsigned int & turns, const unsigned int & frames);
		LookupTable();

		void setSize(const unsigned int & turns, const unsigned int & frames);
		int getTurns();
		int getFrames();

		void clear();

		void add(const unsigned int & turn, const unsigned int & frame, const idtype & id, const Node & input);

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

#endif // LOOKUPTABLE_H
