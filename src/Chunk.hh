#ifndef CHUNK_HH_
# define CHUNK_HH_

# include "Core/Container3D.hh"
# include "Core/PairHash.hh"
# include "Core/Array2D.hh"

# include <vector>
# include <unordered_map>

/*!
** @class Chunk
**
** Store all coords of a part of a dynamically generated terrain.
*/
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
  /*!
  ** @class Coord
  **
  ** Store point coordinate and automatically handle collapsing.
  */
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

public:
  typedef Core::Array2D<double, Chunk::SIZE> chunk_coord_type;
  typedef Core::Array2D<Coord*, Chunk::SIZE, 0> chunk_mesh_type;

  typedef std::pair<double, double> pair;
  typedef Core::PairHash<double, double> hash;
  typedef std::unordered_map<pair, double, hash> fast_access_chunk_type;
  typedef chunk_mesh_type::iterator iterator;
  typedef chunk_mesh_type::const_iterator const_iterator;

public:
  Chunk(int x, int y);
  ~Chunk();

  /*!
  ** Add a new points into the chunk system.
  **
  ** @param x Horizontal coordinate.
  ** @param y Vertical coordinate.
  ** @param z Depth coordinate.
  */
  void add(double x, double y, double z);

  /*!
  ** Detect all collapsing points, and link them.
  */
  void meshAllCoord();

  /*!
  ** Delete all points.
  */
  void clear();

  /*!
  ** Get the number of points contained in the chunks
  ** (Even collapsed points is counted).
  **
  ** @return Size of the chunk.
  */
  size_t size() const;

  /*!
  ** Get an iterator on the first point in the chunk.
  **
  ** @return An iterator on the first point of the chunk.
  */
  iterator begin();

  /*!
  ** Get an iterator after the last point in the chunk.
  **
  ** @return An iterator after the last point of the chunk.
  */
  iterator end();

  /*!
  ** Get an iterator on the first point in the chunk.
  **
  ** @return A const iterator on the first point of the chunk.
  */
  const_iterator cbegin() const;

  /*!
  ** Get an iterator after the last point in the chunk.
  **
  ** @return A const iterator after the last point of the chunk.
  */
  const_iterator cend() const;

  /*!
  ** Convert world coord to chunk coord.
  **
  ** @param absolute Absolute coordinate.
  ** @return Coordinate converted in chunk coordinate.
  */
  static int absoluteToChunkCoord(double absolute);

  /*!
  ** Given a (x,y) coord, gets the height.
  **
  ** @param x X coord.
  ** @param y Y coord.
  ** @return Height at the coord (x,y).
  */
  double operator()(double x, double y) const;

  /*!
  ** Given x,y,z coords, get the coords pointer.
  **
  ** @param x X coord.
  ** @param y Y coord.
  ** @param z Z coord.
  ** @return A pointer on coord, or 0 if not found.
  */
  Coord* getCoord(double x, double y, double z) const;

  /*!
  ** Get coords list.
  **
  ** @return A list of coords.
  */
  const chunk_mesh_type& getCoords() const;

  /*!
  ** Get coords list.
  **
  ** @return A list of coords.
  */
  chunk_mesh_type& getCoords();

  /*!
  ** Create all points from a grid of points.
  ** Points need to be inserted in a specific order to be draw correctly,
  ** this function guaranty this constraint.
  **
  ** @param coords Absolute coords on a grid.
  */
  void createRealCoord(const chunk_coord_type& coords);

private:
  int _x;
  int _y;
  chunk_mesh_type _chunk;
  fast_access_chunk_type _fast_access_chunk;
};

#endif /* !CHUNK_HH_ */
