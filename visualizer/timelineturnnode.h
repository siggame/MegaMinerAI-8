#ifndef TIMELINETURNNODE_H
#define TIMELINETURNNODE_H

#include "avl.h"

/** @todo interpolation? **/
template <typename T>
class TimelineTurnNode : public Avl<T>
{
	public:
		/** Default constructor */
		TimelineTurnNode():m_interp(false){}

		void setInterpolation(bool interp);
		bool isInterpolating(){return Avl<T>::isInterpolating();}
	protected:
	private:
		bool m_interp;

};

#include "timelineturnnode.hpp"

#endif // TIMELINETURNNODE_H
