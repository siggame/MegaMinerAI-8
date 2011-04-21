#ifndef GOCFAMILY_TALK_H
#define GOCFAMILY_TALK_H
#include "gameobject/gocomponent.h"

class GOCFamily_Talk : public GOComponent
{
    public:
    GOCFamily_Talk(){m_message.clear();}
    GOCFamily_Talk(GameObject * parent){setOwner(parent); m_message.clear();}
    GOCFamily_Talk(GameObject * parent, const string & message,){setOwner(parent); m_message = message;}

    string message()
    {
      return m_message;
    }

    const GOC_IDType familyID() const { return GOC_IDType("TalkFamily"); }
    void update(){}

protected:
    string m_message;
};

#endif // GOCFAMILY_HEALTH_H
