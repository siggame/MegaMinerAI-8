#ifndef PIRATEHEALTH_H
#define PIRATEHEALTH_H
#include "../lib/gocfamily_health.h"

class PirateHealth : public GOCFamily_Health
{
public:
    PirateHealth(GameObject*parent, int & currentHealth):GOCFamily_Health(parent,currentHealth){}
    ~PirateHealth(){}
    const GOC_IDType componentID() const {return GOC_IDType("PirateHealth");}
    unsigned int maxHealth(){return 100;} //! @todo make this the apropriate value
private:
};


#endif // PIRATEHEALTH_H
