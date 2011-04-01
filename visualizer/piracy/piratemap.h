#ifndef PIRATEMAP_H
#define PIRATEMAP_H

#include "../lib/gocfamily_render.h"
#include "../lib/parser/parser.h"

class PirateMap : public GOCFamily_Render
{
public:
  PirateMap();
  ~PirateMap();

  virtual const GOC_IDType componentID() const;

  void generateMap( Game& g );

  void update();
  virtual void renderAt(
      const unsigned int& turn,
      const unsigned int& frame
      );
  
private:
};

#endif
