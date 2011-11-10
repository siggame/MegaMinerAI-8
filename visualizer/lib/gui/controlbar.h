#ifndef CONTROLBAR_H
#define CONTROLBAR_H

#include <QSlider>
#include <QPushButton>
#include <QLabel>
#include "../optionsmanager/optionsman.h"
#include "../timemanager/timeManager.h"

namespace visualizer
{

class ControlBar : public QWidget, public UpdateNeeded
{
  friend class _GUI;
  friend class _TimeManager;
  Q_OBJECT
    public:
    ControlBar( QWidget *parent = 0 );

    void update();

  public slots:
    void sliderDrag();
    void sliderRelease();
    void sliderChanged(int value);
    void rewind();
    void play();
    void fastForward();

  private:
    QLabel* turnLabel;
    QSlider* m_slider;
    QPushButton* rewindButton;
    QPushButton* playButton;
    QPushButton* fastForwardButton;
    float originalTimeManagerSpeed;

};

} //visualizer

#endif
