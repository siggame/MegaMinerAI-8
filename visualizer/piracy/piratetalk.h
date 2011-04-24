#ifndef PIRATETALK_H
#define PIRATETALK_H
#include "../lib/gocfamily_talk.h"

class PirateTalk : public GOCFamily_Talk
{
  public:
    PirateTalk(GameObject*parent, const string & message):GOCFamily_Talk(parent,message){}
    ~PirateTalk(){}
    const GOC_IDType componentID() const {return GOC_IDType("PirateTalk");}
  private:
};
#endif                           // PIRATETALK_H
