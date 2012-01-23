#ifndef MAP_HH_
# define MAP_HH_

# include "Block.hh"
# include "SolTriangle.hh"
# include <vector>
# include <iostream>

class Map
{
public:
    typedef std::vector<SolTriangle*> solTriangle_type;
    typedef std::vector<Block*> blocks_type;
    typedef blocks_type::iterator iterator;
    typedef blocks_type::const_iterator const_iterator;

    typedef solTriangle_type::iterator iteratorT;
    typedef solTriangle_type::const_iterator const_iteratorT;


public:
    Map();
    ~Map();

    bool loadMap(const std::string& filename);
    bool loadMapT(const std::string& filename);
    void clear();
    Block* operator()(int x, int y, int z) const;
    //SolTriangle* get(int x,int y,int z) const;
    const_iterator begin() const;
    const_iterator end() const;
    const_iteratorT Tbegin() const;
    const_iteratorT Tend() const;
private:
    blocks_type _blocks;
    solTriangle_type _triangles;
};

#endif /* !MAP_HH_ */
