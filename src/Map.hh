#ifndef MAP_HH_
# define MAP_HH_

# include "Block.hh"
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

  typedef std::unordered_map<Core::Container3D<int>, Block*, Core::NumericalContainerHash<int> > temp_map_type;
  typedef std::unordered_map<std::pair<int, int>, Chunk*, Core::PairHash<int, int> > chunks_type;
  typedef std::unordered_map<Core::Container3D<int>, Block*, Core::NumericalContainerHash<int> > blocks_type;
  typedef Core::ListContainer3D<Core::Container3D<double> > objects_type;



    void insertBlockfromBlock(const Block* who, const Block::FaceType where);
    Block::Block* findBlock(const Core::Container3D<int>& where) const;
    void eraseBlock(const Block::Block* who);
    void createBlock(const Core::Container3D<int> & where);



public:

  Map();
  ~Map();

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
