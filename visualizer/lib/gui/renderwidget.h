//////////////////////////////////////////////////////////////////////////////
/// @file renderwidget.h
/// @brief Contiains the class definitions for the widget where all the 
/// rendering will occur.
//////////////////////////////////////////////////////////////////////////////
#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QtOpenGL>
#include "../selectionrender/selectionrender.h"

//////////////////////////////////////////////////////////////////////////////
/// @class RenderWidget
/// @brief This class sets up the OpenGL context, and prepares the visualizer
/// for rendering.  It utilizes QGLWidget for cross-platformity.
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
/// @fn RenderWidget::initializeGL()
/// @brief Does all the set up related to rendering
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
/// @fn RenderWidget::resizeEvent( QResizeEvent *evt )
/// @brief Event that is typically triggered when the rendering area 
/// has been resized in some way.  It re-adjusts the parameters so that
/// everything still looks correct
/// @param evt Event pointer which contains all the juicy details related
/// to the resize event, mainly the new size.
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
/// @fn RenderWidget::mousePressEvent( QMouseEvent *event )
/// @brief This event is automatically triggered when the user has pressed
/// but not released his mouse within the render area.  Currently, this is
/// being used only for selection boxes, but could be expanded to dragging 
/// the render area.
/// @param event Event pointer which contains the details related to the 
/// mouse press event such as which button was pressed and where.
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
/// @fn RenderWidget::mouseReleaseEvent( QMouseEvent *event )
/// @brief This event is automatically triggered when the user has released 
/// the button on his mouse within the render area.  Currently, this is
/// being used only for selection boxes, but could be expanded to dragging 
/// the render area.
/// @param event Event pointer which contains the details related to the 
/// mouse release event such as which button was pressed and where.
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
/// @fn RenderWidget::mouseMoveEvent( QMouseEvent *event )
/// @brief This event is automatically triggered when the user has moved his
/// mouse within the render area.  Currently, this is being used only for
/// selection boxes, but could be expanded to dragging the render area.
/// @param event Event pointer which contains the details related to the 
/// mouse move event such as where the pointer is.
//////////////////////////////////////////////////////////////////////////////


namespace visualizer
{

  class RenderWidget: public QGLWidget
  {
    public:
      RenderWidget( QWidget *parent );
      ~RenderWidget();
      void initializeGL();

      void resizeEvent( QResizeEvent *evt );

    private:
      /// @TODO Need to send the result of the selection
      /// events to the loaded game module for unit selection
      void mousePressEvent( QMouseEvent *event );
      void mouseReleaseEvent( QMouseEvent *event );
      void mouseMoveEvent( QMouseEvent *event );

      bool leftButtonDown;
      bool leftButtonDrag;

      int currentX;
      int currentY;

      int initialX;
      int initialY;

      static const int m_DRAG_DISTANCE = 6;

  };

} // visualizer

#endif
