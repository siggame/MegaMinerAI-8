#ifndef TIMELINE_H
#define TIMELINE_H
#include "timelineturnnode.h"

template<class T>
class Timeline : private Avl < TimelineTurnNode <T> >
{
	public:
		T * operator()(const unsigned int & turn, const unsigned int & frame);

		void add(const unsigned int & turnNum, const unsigned int & frameNum, const T & frame);
		void rem(const unsigned int & turnNum);
		void rem(const unsigned int & turnNum, const unsigned int & frameNum);

		bool isInterpolating(const unsigned int & turnNum);
		void setInterpolation(const unsigned int & turnNum, bool interp);

	protected:
	private:
		void add(const unsigned int & turnNum, const TimelineTurnNode<T> & node);
};

#include "timeline.hpp"

#endif // TIMELINE_H
