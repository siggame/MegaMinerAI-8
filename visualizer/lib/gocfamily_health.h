#ifndef GOCFAMILY_HEALTH_H
#define GOCFAMILY_HEALTH_H
#include "gameobject/gocomponent.h"

class GOCFamily_Health : public GOComponent
{
    public:
    GOCFamily_Health(){m_currentHealth = 0;}
    GOCFamily_Health(GameObject * parent){setOwner(parent);m_currentHealth = 0;}
    GOCFamily_Health(GameObject * parent, const int & currentHealth){setOwner(parent);m_currentHealth = currentHealth;}

    virtual unsigned int maxHealth() = 0;
    unsigned int currentHealth()
    {
	return m_currentHealth;
    }

    const GOC_IDType familyID() const { return GOC_IDType("HealthFamily"); }
    void update(){}

protected:
    unsigned int m_currentHealth;
};

#endif // GOCFAMILY_HEALTH_H
