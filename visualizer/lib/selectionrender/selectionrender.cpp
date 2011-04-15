#include "selectionrender.h"
#include <GL/gl.h>
using namespace std;

SelectionRender::setSelectionBox(X1, Y1, X2, Y2)
{
	m_X1 = X1;
  m_Y1 = Y1;
  m_X2 = X2;
  m_Y2 = Y2;
}

bool getUpdated()
{
	return m_updated;
}

void setUpdated(bool updated)
{
	m_updated = updated;
}
		
bool getDragging()
{
	return m_dragging;
}

void setDragging(bool dragging)
{
	m_dragging = dragging;
}

void renderAt(const unsigned int & turn, const unsigned int & frame)
{
	if(getDragging())
	{
		glColor4f(0f, 0.5f, 0.5f, 1f);
		glBegin(GL_QUADS);
			glVertex3f(m_X1, m_Y1, 10);
			glVertex3f(m_X2, m_Y1, 10);
			glVertex3f(m_X2, m_Y2, 10);
			glVertex3f(m_X1, m_Y2, 10);
		glEnd();
	}
}
