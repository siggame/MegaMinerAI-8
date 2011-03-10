#ifndef GOCFAMILY_DATA_H
#define GOCFAMILY_DATA_H

#include "gameobject/gocomponent.h"
#include "timeline/timeline.h"
template <class T>
class GOCFamily_Data : public GOComponent
{
	public:
		/** Default constructor */
		GOCFamily_Data();
		/** Default destructor */
		virtual ~GOCFamily_Data() = 0;

		virtual const GOC_IDType & familyID() const {return GOC_IDType("DataFamily");}

		T * getDataAt(const unsigned int & turn, const unsigned int & frame)
		{
			return m_timeline(turn,frame);
		}

	protected:
		typedef Timeline<T> TimelineType;
		TimelineType m_timeline;

	private:
};

#endif

