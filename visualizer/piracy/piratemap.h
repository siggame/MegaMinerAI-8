#ifndef PIRATEMAP_H
#define PIRATEMAP_H

#include "parser/parser.h"
#include <QColor>
#include <QImage>
#include "igame.h"
#include <string>
#include <fstream>

namespace visualizer
{

  class PirateMap: public Animatable
  {
    public:

      enum TileType
      {
        water,
        land
      };

      enum Orientation
      {
        horizontal,
        vertical
      };

      void generateMap( Game& g, IGame& intf );

      AnimData *getData()
      {
        return 0;
      }

      int distToTile
        (
        const int& x,
        const int& y,
        const int& mapsize,
        const TileType& type,
        const std::map<int, Tile>& tiles
        );

      void boxBlur
        (
        int **map,
        const int& width,
        const int& height,
        const int& radius 
        );

      void blur
        (
        int **map,
        const int& width,
        const int& height,
        const int& radius,
        const float* gaussian,
        Orientation orient 
        );

      QRgb interpolate
        (
        int x,
        int y,
        int size,
        QImage *images,
        int *depths,
        int depth 
        );

      float interp
        (
        float x,
        float x0,
        float x1,
        float y0,
        float y1  
        );

     int mapW;
     int mapH;
     IRenderer *Renderer;


#if 0
      PirateMap();
      ~PirateMap();


      static void drawTGA( std::string filename );
      int m_width;

      void update();
      virtual void renderAt(
        const unsigned int& turn,
        const unsigned int& frame
        );

    private:
#endif
  };

} // visualizer
#endif
