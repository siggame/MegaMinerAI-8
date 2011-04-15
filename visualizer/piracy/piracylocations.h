#ifndef PIRACYLOCATIONS_H
#define PIRACYLOCATIONS_H
#include "../lib/gocfamily_location.h"
#include "../lib/parser/parser.h"

class PiracyLocation: public GOCFamily_Location
{
public:
    bool parseLocation(Mappable * mappable)
    {
	m_x = mappable->x;
	m_y = mappable->y;
    }

    const GOC_IDType componentID() const {return GOC_IDType("Location");}
    ~PiracyLocation(){}

};

#endif // PIRACYLOCATIONS_H
