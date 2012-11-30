#ifndef MAP_HH_
# define MAP_HH_

# include "Block/Basic.hh"
# include "Vector3D.hh"
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
  typedef std::unordered_map<std::pair<int, int>, Chunk*, Core::PairHash<int, int> > chunks_type;
  typedef std::unordered_map<Core::Container3D<int>, Block::Basic*, Core::NumericalContainerHash<int> > blocks_type;

public:
  Map();
  ~Map();



    void InitGroundBlocks(int SIZE);


  /*!
  ** Create a block at a given position.
  **
  ** @param where The position.
  */
  void createBlock(const Core::Container3D<int> & where);


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
  ** Delete a block from the world.
  **
  ** @param who The block to delete.
  */
  void eraseBlock(const Block::Basic* who);

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
  ** Check if a map chunk need to be loaded.
  ** Release too far map chunks.
  ** Inexistant chunk is dynamically generated.
  **
  ** @param position The current position of the camera.
  ** @param chunks All the world chunks.
  */
  void chunkLazyLoading(const Vector3D& position, const Map::chunks_type& chunks);

  /*!
  ** Return an instance on the list of all blocks.
  **
  ** @return Instance on all blocks.
  */
  blocks_type& getBlocks();

  /*!
  ** Return an instance on the list of all chunks.
  **
  ** @return Instance on all chunks.
  */
  chunks_type& getChunks();

  /*!
  ** Return an instance on the list of all blocks.
  **
  ** @return Instance on all blocks.
  */
  const blocks_type& getBlocks() const;

  /*!
  ** Return an instance on the list of all chunks.
  **
  ** @return Instance on all chunks.
  */
  const chunks_type& getChunks() const;

private:
  blocks_type _blocks;
  chunks_type _chunks;
};

#endif /* !MAP_HH_ */
