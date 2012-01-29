#ifndef MAP_HH_
# define MAP_HH_

# include "Block.hh"
# include "SolTriangle.hh"

# include "Core/ListContainer3D.hh"

# include <vector>
# include <iostream>

class Map
{
public:
  typedef Core::ListContainer3D<SolTriangle> triangles_type;
  typedef Core::ListContainer3D<Block> blocks_type;

public:
  Map();
  ~Map();

  bool loadBlocks(const std::string& filename);
  bool loadTriangles(const std::string& filename);
  void clear();

  const blocks_type& getBlocks() const;
  const triangles_type& getTriangles() const;

private:
  blocks_type _blocks;
  triangles_type _triangles;
};

#endif /* !MAP_HH_ */
