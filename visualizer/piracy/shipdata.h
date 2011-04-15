#ifndef SHIPDATA_H
#define SHIPDATA_H
#include "../lib/gocfamily_data.h"
#include "../lib/parser/parser.h"

struct ShipDataInfo
{
    int x;
    int y;
    //int owner;
    int facing;
    // 0 - 1 - 2
    // 7 - * - 3
    // 6 - 5 - 4
};

class ShipData : public GOCFamily_Data<ShipDataInfo>
{
public:

    const GOC_IDType componentID() const;
    void parseShip( const Game& game, int shipId, int turn );
    void update(){};
};

#endif // SHIPDATA_H
