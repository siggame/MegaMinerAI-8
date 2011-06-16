#include "gui.h"
#include "coolslider.h"

const int bookmarks[] =
{
  0, 10, 20, 30, 40, 50, 60
};

GUI::GUI()
{
  resize( 1280, 1024 );

  //setCentralWidget( m_slider );
  statusBar()->setFixedHeight( 20 );
  statusBar()->setContentsMargins( 0, 0, 0, 0 );
  GranolaBar *m_slider = new GranolaBar( statusBar() );
  statusBar()->addPermanentWidget( m_slider, 100 );

  m_slider->setMaxFrame( 500 );

  for( int i = 0; i < 30; i++)
  {
    m_slider->addBookmark( i*500/30,  0 );
  }

  for( int i =0; i < 250; i++ )
  {
    m_slider->addDebugPoint( i*2, 0 );
  }
}
