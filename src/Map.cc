#include "Map.hh"
#include <fstream>

Map::Map()
{

}

Map::~Map()
{
    clear();
}

bool Map::loadMap(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    std::string line;

    int x,y,z;

    while (file)
    {   file >> x >> y >> z;

        _blocks.push_back(new Block(x, y, z, 10));

    }
    return true;
}

void Map::clear()
{
    const_iterator end = _blocks.end();
    for (const_iterator it = _blocks.begin(); it != end; ++it)
        delete *it;
    _blocks.clear();
}

Block* Map::operator()(int x, int y, int z) const
{
    return _blocks[x + y * _blocks.size() + z* _blocks.size()*_blocks.size()];
}


Map::const_iterator Map::begin() const
{
  return _blocks.begin();
}

Map::const_iterator Map::end() const
{
  return _blocks.end();
}
