#ifndef PIRATEMAP_H
#define PIRATEMAP_H

#include "../lib/gocfamily_render.h"
#include "../lib/parser/parser.h"
#include <string>
#include <fstream>

class PirateMap : public GOCFamily_Render
{
public:
  PirateMap();
  ~PirateMap();

  virtual const GOC_IDType componentID() const;

  void generateMap( Game& g );

  static void drawTGA( std::string filename );

  void findClosest( 
      int **map, 
      const int& width, 
      const int& height, 
      const int& xc, 
      const int& yc, 
      const int& rad );

  void update();
  virtual void renderAt(
      const unsigned int& turn,
      const unsigned int& frame
      );
  
private:
};

#endif
