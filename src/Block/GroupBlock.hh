#ifndef BLOCK_GROUPBLOCK_HH_
# define BLOCK_GROUPBLOCK_HH_

# include "Basic.hh"

# include <unordered_map>
# include <vector>

namespace Block
{
  class GroupBlock
  {
  public:
    typedef std::vector<Block::Basic*> list_type;
    typedef std::unordered_map<int, list_type*> assoc_type;

  public:
    GroupBlock();
    ~GroupBlock();

    void add(int index, Block::Basic* block);
    void remove(int index, Block::Basic* block);
    void draw() const;

  private:
    std::string   _shaderName;
    std::string   _textureName;
    assoc_type    _assoc;
  };
} // Block

#endif /* !BLOCK_GROUPBLOCK_HH_ */
