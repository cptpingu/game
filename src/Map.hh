#ifndef MAP_HH_
# define MAP_HH_

# include "Block/Basic.hh"
# include "Block/GroupBlock.hh"
# include "Core/Vector3D.hh"
# include "Model/StaticModelManager.hh"
# include "Chunk.hh"

# include "Core/ListContainer3D.hh"
# include "Core/PairHash.hh"
# include "Core/NumericalContainerHash.hh"

# include <string>
# include <utility>
# include <unordered_map>

/*!
** @class Map
**
** This class hold the terrain and all that can be put on it (like the blocks).
*/
class Map
{
public:
  typedef std::unordered_map<Core::Container3D<int>, Block::Basic*, Core::NumericalContainerHash<int> > blocks_type;
  typedef std::unordered_map<Model::Type, Block::GroupBlock*, std::hash<int> > groups_type;

public:
  Map();
  ~Map();

  /*!
  ** Create a block at a given position.
  **
  ** @param where The position.
  */
  void createBlock(const Core::Container3D<int> & where, unsigned int state = 0);

  void changeBlockState(const Core::Container3D<int>& where, bool propagate);
  void changeNeighbourState(const Core::Container3D<int>& where, bool propagate);
  bool fillNeighbours(const Core::Container3D<int>& where,
                      Block::NeighbourMatrix& neighbours);
  void changeAllBlockState();

  /*!
  ** Create a block near another block.
  **
  ** @param who The coordinate of the block which is alread there.
  ** @param where The face of the block where to create a new block.
  */
  void insertBlockNearBlock(const Block::Basic* who, const Block::FaceType where);

  /*!
  ** Given its coordinate, find a block.
  **
  ** @param where The position.
  **
  ** @return The block or 0 if not found.
  */
  Block::Basic* findBlock(const Core::Container3D<int>& where) const;

  /*!
  ** Given its coordinate, find a block.
  **
  ** @param x The X coord.
  ** @param y The Y coord.
  ** @param z The Z coord.
  **
  ** @return The block or 0 if not found.
  */
  Block::Basic* findBlock(int x, int y, int z) const;

  /*!
  ** Delete a block from the world.
  **
  ** @param who The block to delete.
  */
  void eraseBlock(Block::Basic* who);

  /*!
  ** Load blocks from file.
  **
  ** @param filename The file name.
  ** @return If load succeed.
  */
  bool loadBlocks(const std::string& filename);

  /*!
  ** Delete all objects the map own.
  */
  void clear();

  /*!
  ** Return an instance on the list of all blocks.
  **
  ** @return Instance on all blocks.
  */
  blocks_type& getBlocks();

  /*!
  ** Return an instance on the list of all blocks.
  **
  ** @return Instance on all blocks.
  */
  const blocks_type& getBlocks() const;

  const groups_type& getGroups() const;
private:
  blocks_type _blocks;
  groups_type _groups;
};

#endif /* !MAP_HH_ */
