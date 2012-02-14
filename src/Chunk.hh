#ifndef CHUNK_HH_
# define CHUNK_HH_

# include "Core/Container3D.hh"
# include <vector>
# include <cstddef>

class Chunk
{
public:
  static const int SIZE = 50;

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

  typedef std::vector<Coord*> chunk_type;
  typedef chunk_type::iterator iterator;
  typedef chunk_type::const_iterator const_iterator;

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

private:
  chunk_type _chunk;
};

#endif /* !CHUNK_HH_ */
