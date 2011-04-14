#ifndef TIMELINE_HPP
#define TIMELINE_HPP

#include "timeline.h"



/** @brief setInterpolation
  *
  * @todo: document this function
  */
template<class T>
void Timeline<T>::setInterpolation(const unsigned int & turnNum, bool interp)
{

}

/** @brief isInterpolating
  *
  * @todo: document this function
  */
template<class T>
bool Timeline<T>::isInterpolating(const unsigned int & turnNum)
{

	return false;
}

/** @brief rem
  *
  * @todo: document this function
  */
template<class T>
void Timeline<T>::rem(const unsigned int & turnNum, const unsigned int & frameNum)
{

}

/** @brief rem
  *
  * @todo: document this function
  */
template<class T>
void Timeline<T>::rem(const unsigned int & turnNum)
{


}

/** @brief add
  *
  * @todo: document this function
  */
template<class T>
void Timeline<T>::add(const unsigned int & turnNum, const unsigned int & frameNum, const T & frame)
{


}


/** @brief operator()
  *
  * @todo: document this function
  */
template<class T>
T * Timeline<T>::operator()(const unsigned int & turn, const unsigned int & frame)
{

	return NULL;
}


#endif

