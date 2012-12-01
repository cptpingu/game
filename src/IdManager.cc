#include "IdManager.hh"

#include <iostream>
IdManager::IdManager()
{
}

IdManager::~IdManager()
{
}

GLuint
IdManager::getNewIdForBlock(Block::Basic* block)
{
  while (true)
  {
    GLuint id = Random::rand() / 1000;
    if (_ids.find(id) == _ids.end())
    {
      _ids.insert(ids_type::value_type(id, block));
      return id * 1000;
    }
  }
  return 0;
}

void
IdManager::deleteId(GLuint id)
{
  _ids.erase(id / 1000);
}

Block::Basic*
IdManager::getBlockFromId(GLuint id) const
{
  auto found = _ids.find(id / 1000);
  if (found != _ids.cend())
    return found->second;
  return 0;
}
