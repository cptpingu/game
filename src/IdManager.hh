#ifndef IDMANAGER_HH_
# define IDMANAGER_HH_

# include "Core/NumericalContainerHash.hh"

# include "Core/Singleton.hh"
# include "Core/Container3D.hh"
# include "Block/Basic.hh"
# include "Core/Random.hh"
# include "Opengl.hh"

# include <unordered_map>
# include <map>

class IdManager : public Core::Singleton<IdManager>
{
  friend class Core::Singleton<IdManager>;

private:
  typedef std::unordered_map<Block::id_type, Block::Basic*, Core::NumericalContainerHash<GLuint> > ids_type;

private:
  IdManager();

public:
  ~IdManager();

  Block::id_type getNewIdForBlock(Block::Basic* block);
  void deleteId(const Block::id_type& id);
  Block::Basic* getBlockFromId(const Block::id_type& id) const;

private:
  ids_type _ids;
};

#endif /* !IDMANAGER_HH_ */
