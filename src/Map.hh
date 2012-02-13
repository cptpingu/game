#ifndef MAP_HH_
# define MAP_HH_

# include "Block.hh"
# include "SolTriangle.hh"
# include "Vector3D.hh"
# include "Chunk.hh"

# include "Core/ListContainer3D.hh"

# include <vector>
# include <iostream>
# include <utility>
# include <unordered_map>

class Map
{
public:
  struct Container3DIntHash : public std::unary_function<Core::Container3D<int>, size_t>
  {
  public:
    size_t operator()(const Core::Container3D<int>& p) const
    {
      size_t m(1000003), x(0x345678), y(hash(p._x));
      x = (x ^ y) * m;
      m += 82524;
      y = hash(p._y);
      x = (x ^ y) * m;
      m += 82522;
      y = hash(p._z);
      x = (x ^ y) * m;
      return x + 97531;
    }
  private:
    size_t hash(int i) const
    {
      static std::hash<size_t> _hash;
      return _hash(i);
    }
  };
  typedef std::unordered_map<Core::Container3D<int>, Block*, Container3DIntHash> temp_map_type;
public:
  //typedef Core::ListContainer3D<SolTriangle*> triangles_type;
  typedef Chunk triangles_type;
  typedef std::unordered_map<Core::Container3D<int>, triangles_type> chunks_type;
  typedef Core::ListContainer3D<Block*> blocks_type;
  typedef Core::ListContainer3D<Core::Container3D<double> > objects_type;

public:
  Map();
  ~Map();

  bool loadBlocks(const std::string& filename);
  bool loadTriangles(const std::string& filename);
  void clear();

  /*!
  ** Check if a map chunk need to be loaded.
  ** Release too far map chunks.
  ** Inexistant chunk is dynamically generated.
  **
  ** @param position The current position of the camera.
  */
  void lazyChunkLoading(const Vector3D& position);

  blocks_type& getBlocks();
  triangles_type& getTriangles();
  const blocks_type& getBlocks() const;
  const triangles_type& getTriangles() const;

private:
  blocks_type _blocks;
  triangles_type _triangles;
};

#endif /* !MAP_HH_ */
