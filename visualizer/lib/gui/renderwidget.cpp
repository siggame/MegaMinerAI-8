#include "renderwidget.h"
#include "../../piracy/dupObj.h"
#include "gui.h"

#include <iostream>
using namespace std;

RenderWidget::RenderWidget( QWidget *parent )
: QGLWidget( QGLFormat( QGL::SampleBuffers ), parent )
{
  initializeGL();

}

RenderWidget::~RenderWidget()
{
}

void RenderWidget::initializeGL()
{

  Renderer<DupObj>::create();
  Renderer<DupObj>::setParent( this );

}

void RenderWidget::resizeEvent( QResizeEvent *evt )
{
  Renderer<DupObj>::resize( evt->size().width(), evt->size().height() );
}

void RenderWidget::mousePressEvent( QMouseEvent *e )
{
    if( e->button() == Qt::LeftButton )
    {
      QString line;
      
      initialX = e->x();
      initialY = e->y();
       
     	SelectionRender::get()->setSelectionBox(initialX, initialY, initialX+1, initialY+1);
 	    //+1 guarantees we create a box, rather than a point.
       
      line.clear();
      line.append("Left click: ( ");
      line.append(QString::number(initialX));
      line.append(", ");
      line.append(QString::number(initialY));
      line.append(")");

      GUI::get()->m_consoleArea->append(line);

      leftButtonDown = true;
      

      /* Thus, dragX and dragY become our starting point, 
       * and curX and curY will be contiuously updated, eventually becoming 
       * our ending point if dragging.
       */
    }


}

void RenderWidget::mouseReleaseEvent( QMouseEvent *e )
{

    currentX = e->x()+1;
    currentY = e->y()+1;
    //+1 guarantees we create a box, rather than a point.
    
		SelectionRender::get()->setUpdated(true); 
		SelectionRender::get()->setDragging(false); 		   
    
    int selectWidth, selectHeight;
//  int selectX = selectWidth = curX/getAttr(unitSize);
//  int selectY = selectHeight = curY/getAttr(unitSize);

//   if( e->button() == Qt::LeftButton )
//  {
//    if( leftButtonDrag )
//    {
//      selectX = (curX<dragX ? curX : dragX)/getAttr(unitSize);
//      selectWidth = (curX<dragX ? dragX : curX)/getAttr(unitSize);
//      selectY = (curY<dragY ? curY : dragY)/getAttr(unitSize);
//      selectHeight = (curY<dragY ? dragY : curY)/getAttr(unitSize);
//    }


//    Game *game = parent->gamelog;
//    int frame = getAttr( frameNumber );
//    if( game )
//    {
//      if( !(QApplication::keyboardModifiers() & Qt::ShiftModifier) )
//        selectedIDs.clear();

//      addSelection(game->states[frame].units, selectedIDs, selectX, selectY, selectWidth, selectHeight);
//      std::map<int,Unit> tBots;
//      for( std::map<int,Bot>::iterator i = game->states[frame].bots.begin(); i != game->states[frame].bots.end(); i++ )
//      {
//        if( !i->second.partOf )
//          tBots[i->second.id] = i->second;
//      }

//      addSelection(tBots, selectedIDs, selectX, selectY, selectWidth, selectHeight);
//      addSelection(game->states[frame].frames, selectedIDs, selectX, selectY, selectWidth, selectHeight);
//      addSelection(game->states[frame].walls, selectedIDs, selectX, selectY, selectWidth, selectHeight);

//      stringstream ss;
//      ss << "Selected Units: " << selectedIDs.size() << ", X: " << selectX << ", Y: " << selectY << '\n';

//      for (map<int,string>::iterator it = selectedIDs.begin(); it != selectedIDs.end(); it++)
//      {
//        ss << it->second << '\n';
//      }

//      //parent->console->setText( ss.str().c_str() );
//    }

//    leftButtonDown = false;
//    leftButtonDrag = false;
//  } 

//  // Invalidate last frame so we get the latest talkers.
//  setAttr( lastFrame, -1 );
}


void RenderWidget::mouseMoveEvent( QMouseEvent *e )
{
  currentX = e->x();
  currentY = e->y();

  // If Manhattan distance is m_DRAG_DISTANCE or greater, we're draggin
  if( e->buttons() & Qt::LeftButton && 
    abs(currentX-initialX)+abs(currentY-initialY) > m_DRAG_DISTANCE )
  {
    leftButtonDrag = true;
    SelectionRender::get()->setDragging(true);
   	SelectionRender::get()->setSelectionBox(initialX, initialY, currentX, currentY);        
  }
}
