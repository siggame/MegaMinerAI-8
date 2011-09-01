#ifndef PLANT_H
#define PLANT_H

namespace visualizer
{

  class plantData: public AnimData
  {
    public:
  };

  class plant: public Animatable
  {
    public:
      int objectID;
      int ownerID;
      int x;
      int y;
      int root;
      int leaf;
      int flower;
      int health;
      int rootLevel;
      int leafLevel;
      int flowerLevel;
      int rootLevelUp;
      int leafLevelUp;
      int flowerLevelUp;

      plantData m_data;

      AnimData* getData()
      {
        return &m_data;
      } // getData();
     
  }; // plant

} // visualizer

#endif // PLANT_H
