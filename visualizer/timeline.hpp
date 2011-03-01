#ifndef TIMELINE_HPP
#define TIMELINE_HPP

#include "timeline.h"

/** @brief add
  *
  * @todo: document this function
  */
template<class T>
void Timeline<T>::add(const unsigned int & turnNum, const TimelineTurnNode<T> & node)
{
	insert(turnNum,node);
}

/** @brief setInterpolation
  *
  * @todo: document this function
  */
template<class T>
void Timeline<T>::setInterpolation(const unsigned int & turnNum, bool interp)
{
	if (Avl<TimelineTurnNode<T> >::exists(turnNum))
	{
		Avl< TimelineTurnNode<T> >::get(turnNum)->setInterpolation(interp);
	}
}

/** @brief isInterpolating
  *
  * @todo: document this function
  */
template<class T>
bool Timeline<T>::isInterpolating(const unsigned int & turnNum)
{
	if (Avl< TimelineTurnNode<T> >::exists(turnNum))
	{
		return Avl< TimelineTurnNode<T> >::get()->isInterpolating();
	}
	return false;
}

/** @brief rem
  *
  * @todo: document this function
  */
template<class T>
void Timeline<T>::rem(const unsigned int & turnNum, const unsigned int & frameNum)
{
	if (Avl< TimelineTurnNode<T> >::exists(turnNum))
	{
		Avl< TimelineTurnNode<T> >::get(turnNum)->erase(frameNum);
	}
}

/** @brief rem
  *
  * @todo: document this function
  */
template<class T>
void Timeline<T>::rem(const unsigned int & turnNum)
{
	Avl< TimelineTurnNode<T> >::erase(turnNum);
}

/** @brief add
  *
  * @todo: document this function
  */
template<class T>
void Timeline<T>::add(const unsigned int & turnNum, const unsigned int & frameNum, const T & frame)
{
	if (!Avl< TimelineTurnNode<T> >::exists(turnNum))
		Avl< TimelineTurnNode<T> >::insert(turnNum,TimelineTurnNode<T>());

	Avl< TimelineTurnNode<T> >::get(turnNum)->insert(frameNum,frame);
}


/** @brief operator()
  *
  * @todo: document this function
  */
template<class T>
T * Timeline<T>::operator()(const unsigned int & turn, const unsigned int & frame)
{
	TimelineTurnNode<T> * tempTurn = (*(this))[turn];
	if (tempTurn)
		return (*tempTurn)[frame];

	return NULL;
}


#endif

