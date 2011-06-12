#ifndef COOLSLIDER_H
#define COOLSLIDER_H

#include <QtGui/qabstractslider.h>

QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE

QT_MODULE(Gui)

#ifndef QT_NO_SLIDER

class QSliderPrivate;
class QSliderOptionSlider;
class Q_GUI_EXPORT CoolSlider : public QAbstractSlider
{
  Q_OBJECT;
  Q_ENUMS(TickPosition);
  Q_PROPERTY( TickPosition tickPosition READ tickPosition WRITE setTickPosition );
  Q_PROPERTY( int tickInterval READ tickInterval WRITE setTickInterval );

public:


};


#endif

#endif
