#include "lightRevelation.h"
#include "lightRevelationAnimatable.h"
#include "frame.h"
#include "animations.h"

namespace visualizer
{

  LightRevelation::LightRevelation()
  {
  } // LightRevelation::LightRevelation()

  LightRevelation::~LightRevelation()
  {
  } // LightRevelation::~LightRevelation()

  LogRegex LightRevelation::logFileInfo()
  {
    LogRegex lr;
    lr.regex = "\x89PNG";
    lr.startSize = 40;

    return lr;
  } // LogRegex LightRevelation::logFileInfo()

  void LightRevelation::loadGamelog( std::string toBeLalalaloaded )
  {
    cout << "Load Bloom Gamelog" << endl;

    resourceManager->loadTexture( toBeLalalaloaded, "visualExplosion" );
    Frame turn;
    image *i = new image( renderer );
    i->addKeyFrame( new StartAnim );
    i->addKeyFrame( new DrawImage( i ) );
    turn.addAnimatable( i );
    addFrame( turn );

    timeManager->setNumTurns( 1 );
    animationEngine->registerFrameContainer( this );
    timeManager->play();					//really don't need this beeteedubs

  } // LightRevelation::loadGamelog()



} // visualizer

Q_EXPORT_PLUGIN2( lightRevelation, visualizer::LightRevelation );
