#include "selectionrender.h"
#include <GL/gl.h>
using namespace std;

void SelectionRender::setSelectionBox(int X1, int Y1, int X2, int Y2)
{
	m_X1 = X1;
  m_Y1 = Y1;
  m_X2 = X2;
  m_Y2 = Y2;
}

bool SelectionRender::getUpdated()
{
	return m_updated;
}

void SelectionRender::setUpdated(bool updated)
{
	m_updated = updated;
}
		
bool SelectionRender::getDragging()
{
	return m_dragging;
}

void SelectionRender::setDragging(bool dragging)
{
	m_dragging = dragging;
}
#include <iostream>
using namespace std;

void SelectionRender::renderAt(const unsigned int & turn, const unsigned int & frame)
{
	if(getDragging())
	{
    cout << "Draggin" << endl;
		glColor4f(0.0f, 0.5f, 0.5f, 1.0f);
		glBegin(GL_QUADS);
			glVertex3f(m_X1, m_Y1, 0);
			glVertex3f(m_X2, m_Y1, 0);
			glVertex3f(m_X2, m_Y2, 0);
			glVertex3f(m_X1, m_Y2, 0);
		glEnd();
	}
}
