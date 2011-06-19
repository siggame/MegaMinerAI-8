#ifndef GRANOLABAR_H 
#define GRANOLABAR_H 

// GRANularity 
// Over
// Limited 
// Action set
// BAR

#include "granolabutton.h"

#include <QWidget>
#include <QtGui>

#include <list>

using namespace std;

typedef unsigned short int frame_t16;


class GranolaBar : public QWidget 
{
public:
  GranolaBar( QWidget *parent );
  void paintEvent( QPaintEvent * );

  void setMaxFrame( frame_t16 frameNum );
  void addDebugPoint( frame_t16 frame, frame_t16 subframe );
  void addBookmark( frame_t16 frame, frame_t16 subframe );
  void setNumSubframes( frame_t16 frameNum, frame_t16 subframeCnt );

private:
  GranolaButton *m_sliderControl;
  QColor        *m_borderStyle;
  QBrush        *m_grooveStyle;
  QBrush        *m_bookmarkStyle;
  QBrush        *m_debugPointStyle;
  QWidget       *m_parent;

  frame_t16     m_maxFrame;
  list<frame_t16> 
                m_bookmarkFrames;
  list<frame_t16>
                m_debugPointFrames;
};

#endif
