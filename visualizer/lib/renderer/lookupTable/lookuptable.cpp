#include "lookuptable.h"

/** @brief ~LookupTable
  *
  * @todo: document this function
  */
template <typename T, typename idtype>
 LookupTable<T,idtype>::~LookupTable()
{
	clear();
}

/** @brief node
  *
  * @todo: document this function
  */
template <typename T, typename idtype>
LookupNode<T,idtype> * LookupTable<T,idtype>::node(const unsigned int & turn, const unsigned int & frame, const idtype & id)
{

	Bucket * buck = bucket(turn,frame);

	if (buck == NULL)
		return NULL;

	typename Bucket::iterator it = buck->find(id);

	if (it == buck.end())
		return NULL;

	return &(it->second);
}

/** @brief add
  *
  * @todo: document this function
  */
template <typename T, typename idtype>
void LookupTable<T,idtype>::add(const unsigned int & turn, const unsigned int & frame, const idtype & id , const Node & input)
{
	Bucket * buck = bucket(turn,frame);

	if (buck)
		(*buck)[id] = input;
}

/** @brief clear
  *
  * @todo: document this function
  */
template <typename T, typename idtype>
void LookupTable<T,idtype>::clear()
{
	for (unsigned int i = 0; i < m_table.size(); i++)
		m_table[i].clear();

	m_table.clear();

	m_turns = 0;
	m_frames = 0;
}

/** @brief getFrames
  *
  * @todo: document this function
  */
template <typename T, typename idtype>
int LookupTable<T,idtype>::getFrames()
{
	return m_frames;
}

/** @brief getTurns
  *
  * @todo: document this function
  */
template <typename T, typename idtype>
int LookupTable<T,idtype>::getTurns()
{
	return m_turns;
}

/** @brief setSize
  *
  * @todo: document this function
  */
template <typename T, typename idtype>
void LookupTable<T,idtype>::setSize(const unsigned int & turns, const unsigned int & frames)
{
	clear();
	m_turns = turns;
	m_frames = frames;

	m_table.resize(turns*frames);
}

/** @brief LookupTable
  *
  * @todo: document this function
  */
template <typename T, typename idtype>
 LookupTable<T,idtype>::LookupTable()
{
	m_turns = 0;
	m_frames = 0;
}

/** @brief LookupTable
  *
  * @todo: document this function
  */
template <typename T, typename idtype>
 LookupTable<T,idtype>::LookupTable(const unsigned int & turns, const unsigned int & frames)
{
	setSize(turns,frames);
}

/** @brief bucket
  *
  * @todo: document this function
  */
template <typename T, typename idtype>
std::map< idtype, LookupNode<T,idtype> > * LookupTable<T,idtype>::bucket(const unsigned int & turn, const unsigned int & frame)
{
	if (turn >= m_turns || frame >= m_frames)
		return NULL;

	return &m_table[turn*frame + frame];
}


