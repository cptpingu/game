#ifndef MAP_HH_
# define MAP_HH_

# include "Block.hh"

# include <vector>
# include <iostream>

class Map
{
public:
    typedef std::vector<Block*> blocks_type;
    typedef blocks_type::iterator iterator;
    typedef blocks_type::const_iterator const_iterator;

public:
    Map();
    ~Map();

    bool loadMap(const std::string& filename);
    void clear();
    Block* operator()(int x, int y, int z) const;
    const_iterator begin() const;
    const_iterator end() const;
private:
    std::vector<Block*> _blocks;
};

#endif /* !MAP_HH_ */
