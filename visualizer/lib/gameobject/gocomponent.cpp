#include "gocomponent.h"

namespace visualizer
{

GOComponent::GOComponent() : m_owner(0)
{
}


GOComponent::GOComponent( GameObject* owner ) : m_owner( owner )
{
}


void GOComponent::setOwner( GameObject *owner )
{
  m_owner = owner;
}


GameObject* GOComponent::getOwner()
{
  return m_owner;
}

} // visualizer
