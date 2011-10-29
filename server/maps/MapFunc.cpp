//Jeremy Daugherty
//Sig-Game, Megaminer8,
//Map Generator fcuntions.

#include"Mapgen.h"

void mapgen_random(char basemap[][mapbase_width], const float max_walls, const float max_empty)
{
  //set base on the far side of the map so they aren't to close. They will be no closer to each other than 20 squares.
  basemap[rand() % mapbase_height][rand() % (mapbase_width/2)] = base;
  
  //used for the probability of the placement
  float walls_left = max_walls, empty_left = max_empty;
  
  //sets walls
  for( int i  = 0; i < mapbase_height; ++i)
  {
    for( int j = 0; j < mapbase_width; ++j)
    {
      if(basemap[i][j] != base)//makes sure there is no base.
      {
        if( ( rand() % ( static_cast<int>(walls_left + empty_left) ) ) < walls_left )
        {
          basemap[i][j] = wall;
          --walls_left;
        }
        else
        {
          --empty_left;
        };
      }
      else
      {
        --empty_left;
      };  
    };
  };
/*  
  for( int i = 0; i < mapbase_height; ++ i)
  {
    for( int j = 0; j < mapbase_width; ++ j)
    {
      cout << basemap[i][j] << " ";
    };
    
    cout << endl;
  };*/
};

/*
void mapgen_building(char basemap[][], )
{

};
*/
/*
void continuitycheck_loop(char basemap[][mapbase_width])
{
  for( int k = 0; k < 4; ++k)
  {
    for( int i = 0; i < mapbase_hieght; ++i)
    {
      for( int j = 0; j < mapbase_width; ++j)
      {
        if(basemap[i][j] == '.')
        {
          if( i == 0)
          {
            if( j == 0)
            {
              continuitycheck();
            }
          }
        }
      }
    }
  }
};

void continuitycheck(char basemap[][mapbase_width], const int& height, const int& width)
{

};

void swap( char basemap[][mapbase_width], int height_change, int width_change, int height, int width)
{
  basemap[i + height_change][j + width_change] = basemap[i][j];
};
*/