#ifndef CHUNK_HH_
# define CHUNK_HH_

# include "Core/Container3D.hh"
# include "Core/PairHash.hh"
# include "Core/Array2D.hh"

# include <vector>
# include <cstddef>
# include <string>
# include <unordered_map>

class Chunk
{
public:
  static const int SIZE = 65;
  static const int QUALITY = 4;
  static const int MIN_HEIGHT = -100;
  static const int MAX_HEIGHT = 100;

  static const int TEXTURE_SIZE = QUALITY * (SIZE - 1) + 1;
  static const int RATIO = QUALITY;

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

  typedef Core::Array2D<double, Chunk::SIZE> chunk_coord_type;
  typedef Core::Array2D<Coord*, Chunk::SIZE, 0> chunk_mesh_type;
  typedef Core::Array2D<double, Chunk::TEXTURE_SIZE> texture_coord_type;

  typedef std::unordered_map<std::pair<double, double>, double,
          Core::PairHash<double, double> > fast_access_chunk_type;
  typedef chunk_mesh_type::iterator iterator;
  typedef chunk_mesh_type::const_iterator const_iterator;

public:
  Chunk(int x, int y);
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
  double operator()(double x, double y) const;
private:
  void createRealCoord(const texture_coord_type& coords);

private:
  int _x;
  int _y;
  chunk_mesh_type _chunk;
  fast_access_chunk_type _fast_access_chunk;
};

#endif /* !CHUNK_HH_ */
