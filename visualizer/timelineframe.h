#ifndef TIMELINEFRAME_H
#define TIMELINEFRAME_H
#include <cstdlib>

template<class T>
class TimelineFrame
{
	public:
		/** Default constructor */
		TimelineFrame(const unsigned int & frameNum, const T & data):m_parent(NULL),m_left(NULL),m_right(NULL),m_frameNum(frameNum),m_data(data){}
		TimelineFrame():m_parent(NULL),m_left(NULL),m_right(NULL),m_frameNum(0){}
		/** Default destructor */
		virtual ~TimelineFrame(){}

		T & data(){return m_data;}

	protected:
	private:
		friend class TimelineTurnNode;

		TimelineFrame * m_parent;
		TimelineFrame * m_left;
		TimelineFrame * m_right;

		T m_data;

		const unsigned int m_frameNum;
};

#endif // TIMELINEFRAME_H
