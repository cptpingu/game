#ifndef CHUNK_HH_
# define CHUNK_HH_

# include "Core/Container3D.hh"
# include "Core/PairHash.hh"
# include "Core/NonCopyable.hh"

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
  class Coord : private Core::Container3D<double>
  {
  public:
    Coord()
      : Core::Container3D<double>(), _link(0)
    {
    }

    Coord(double x, double y, double z)
      : Core::Container3D<double>(x, y, z), _link(0)
    {
    }

    double getX() const { return _x;}
    double getY() const { return _y;}
    double getZ() const { return _z;}

    void setX(double x) { _x = x;}
    void setY(double y) { _y = y;}
    void setZ(double z)
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

  struct ChunkType : private Core::NonCopyable<std::vector<Coord*> >,
                     public std::vector<Coord*>
  {
  };

  struct TextureCoordType : private Core::NonCopyable<std::vector<double> >,
                            public std::vector<double>
  {
  };

  typedef ChunkType chunk_type;
  typedef std::unordered_map<std::pair<double, double>, double,
          Core::PairHash<double, double> > fast_access_chunk_type;
  typedef chunk_type::iterator iterator;
  typedef chunk_type::const_iterator const_iterator;
  typedef TextureCoordType texture_coord_type;

public:
  Chunk();
  ~Chunk();

  void add(double x, double y, double z);
  void meshAllCoord();
  void clear();
  size_t size() const;
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  static int absoluteToChunkCoord(double absolute);

  void generateTexture(const std::string& filename) const;

  void generateChunk(const texture_coord_type& coords);
  int operator()(double x, double y) const;
private:
  void createRealCoord(const texture_coord_type& coords);

private:
  chunk_type _chunk;
  fast_access_chunk_type _fast_access_chunk;
};

#endif /* !CHUNK_HH_ */
