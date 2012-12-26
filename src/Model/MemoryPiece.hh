#ifndef MODEL_MEMORYPIECE_HH_
# define MODEL_MEMORYPIECE_HH_

# include <array>

namespace Model
{
  struct MemoryPiece
  {
    MemoryPiece()
      : from(0), size(0)
    {
    }
    unsigned int from;
    unsigned int size;
  };

  template <unsigned int Size>
  class MemoryPieces
  {
  public:
    MemoryPieces()
      : _last(0)
    {
    }

    inline const MemoryPiece& operator[](unsigned int index) const
    {
      ASSERT_MSG(index < Size, "index: " << index);
      return _data[index];
    }
    inline MemoryPiece& operator[](unsigned int index)
    {
      ASSERT_MSG(index < Size, "index: " << index);
      return _data[index];
    }
    inline MemoryPiece& last()
    {
      return operator[](_last);
    }
    inline void next()
    {
      ++_last;
    }
  private:
    unsigned int _last;
    std::array<MemoryPiece, Size> _data;
  };
} // Model

#endif /* !MODEL_MEMORYPIECE_HH_ */
