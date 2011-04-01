TimeManager::getTurn()
{
  return m_turn;
}

TimeManager::getFrame()
{
  return m_frame;
}

TimeManager::setTurn(input_turn)
{
  m_turn = input_turn;
  m_frame = 0;
}

#if 0
TimeManager::operator++ (int)
{
  m_turn++;
  m_frame = 0;
  
  return * this;
}

TimeManager::operator++ ()
{
  return ++(*this);
}

TimeManager::operator-- (int)
{
  m_turn--;
  m_frame = 0;
  
  return * this;
}

TimeManager::operator-- ()
{
  return --(*this);
}
#endif
