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

    if (!file)
        return false;

    while (std::getline(file, line))
    {
        // FIXME Load le fichier ici !
        std::cout << line << std::endl;
        // Pour chaque truc chargé, ajouter un block (valeur de x,y,z à trouver).
        _blocks.push_back(new Block(0, 0, 0, 10));
        // !FIXME
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
   // FIXME Trouver formule adéquate.
   return _blocks[x + y * _blocks.size() + z];
}
