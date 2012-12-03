#include "IdManager.hh"

#include <iostream>
IdManager::IdManager()
{
}

IdManager::~IdManager()
{
}

Block::id_type
IdManager::getNewIdForBlock(Block::Basic* block)
{
  while (true)
  {
    const Block::id_type id(Core::Random::rand() % 256, Core::Random::rand() % 256, 0);
    if (_ids.find(id) == _ids.end())
    {
      _ids.insert(ids_type::value_type(id, block));
      return id;
    }
  }
  return Block::id_type();
}

void
IdManager::deleteId(const Block::id_type& id)
{
  const Block::id_type convertedId(id._x, id._y, 0);
  _ids.erase(convertedId);
}

Block::Basic*
IdManager::getBlockFromId(const Block::id_type& id) const
{
  const Block::id_type convertedId(id._x, id._y, 0);
  auto found = _ids.find(convertedId);
  if (found != _ids.cend())
    return found->second;
  return 0;
}
