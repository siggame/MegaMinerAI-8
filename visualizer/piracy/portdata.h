#ifndef PORTDATA_H
#define PORTDATA_H
#include "../lib/gocfamily_data.h"
#include "../lib/parser/parser.h"

struct PortDataInfo
{
    int x;
    int y;
    int owner;
};

class PortData : public GOCFamily_Data<PortDataInfo>
{
public:

    const GOC_IDType componentID() const;
    void parsePort( const Game& game, int portId, int turn );
    void update(){};
};

#endif // PORTDATA_H
