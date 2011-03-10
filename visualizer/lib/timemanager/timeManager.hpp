timeManager::getTurn()
{
  return m_turn;
}

timeManager::getFrame()
{
  return m_frame;
}

timeManager::setTurn(input_turn)
{
  m_turn = input_turn;
  m_frame = 0;
}

timeManager::operator++
{
  m_turn++;
  m_frame = 0;
  
  return * this;
}

timeManager::operator++
{
  return ++(*this);
}

timeManager::operator--
{
  m_turn--;
  m_frame = 0;
  
  return * this;
}

timeManager::operator--
{
  return --(*this);
}
