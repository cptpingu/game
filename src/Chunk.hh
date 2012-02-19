#ifndef CHUNK_HH_
# define CHUNK_HH_

# include "Core/Container3D.hh"
# include "Core/PairHash.hh"
# include <vector>
# include <cstddef>
# include <string>
# include <unordered_map>

class Chunk
{
public:
  static const int SIZE = 64;
  static const int TEXTURE_SIZE = 64 * 64;

public:
  class Coord : private Core::Container3D<int>
  {
  public:
    Coord()
      : Core::Container3D<int>(), _link(0)
    {
    }

    Coord(int x, int y, int z)
      : Core::Container3D<int>(x, y, z), _link(0)
    {
    }

    int getX() const { return _x;}
    int getY() const { return _y;}
    int getZ() const { return _z;}

    void setX(int x) { _x = x;}
    void setY(int y) { _y = y;}
    void setZ(int z)
    {
      _z = z;
      if (_link)
        _link->_z = z;
    }

    void setLink(Coord* coord) { _link = coord; }
    Coord* getLink() { return _link; }

  private:
    Coord* _link;
  };

  typedef std::vector<Coord*> chunk_type;
  typedef std::unordered_map<std::pair<int, int>, int,
          Core::PairHash<int, int> > fast_access_chunk_type;
  typedef chunk_type::iterator iterator;
  typedef chunk_type::const_iterator const_iterator;
  typedef std::vector<double> texture_coord_type;

public:
  Chunk();
  ~Chunk();

  void add(int x, int y, int z);
  void meshAllCoord();
  void clear();
  size_t size() const;
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  static int absoluteToChunkCoord(double absolute);

  void generateTexture(const std::string& filename) const;

  void generateChunk();
  int operator()(int x, int y) const;
private:
  void createRealCoord(const texture_coord_type& coords);

private:
  chunk_type _chunk;
  fast_access_chunk_type _fast_access_chunk;
};

#endif /* !CHUNK_HH_ */
