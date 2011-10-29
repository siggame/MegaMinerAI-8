//Jeremy Daugherty
//Sig-Game, Megaminer 8, 
//map generator.

#include"Mapgen.h"
using namespace std;

int main()
{
  srand(time(NULL));

  char basemap[mapbase_height][mapbase_width];
  char fullmap[mapbase_height][fullmap_width];
  
  //clearing map of all useless junk.
  for(int i = 0; i < mapbase_height; ++i)
  {
    for(int j = 0; j < mapbase_width; ++ j)
    {
      basemap[i][j] = empty;
    };
  };

  mapgen_random(basemap, max_walls, max_empty);
  
  //full map maker
  for(int i = 0; i < mapbase_height; ++i)
  {
    for( int j = 0; j < mapbase_width; ++j)
    {
      fullmap[i][j] = basemap[i][j];
      
      fullmap[mapbase_height - 1 - i][fullmap_width - 1 - j] = basemap[i][j];
      
      if(basemap[i][j] == '0')
        fullmap[mapbase_height - 1 - i][fullmap_width - 1 - j] = '1';
    };
  };
  
  for(int i = 0; i < mapbase_height; ++i)
  {
    for( int j = 0; j < fullmap_width; ++ j)
    {
      cout << fullmap[i][j] << " ";
    }
    
    cout << endl;
  }
}