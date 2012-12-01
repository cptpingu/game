#ifndef IDMANAGER_HH_
# define IDMANAGER_HH_

# include "Core/Singleton.hh"
# include "Random.hh"
# include "Opengl.hh"
# include "Block/Basic.hh"

# include <unordered_map>

class IdManager : public Core::Singleton<IdManager>
{
  friend class Core::Singleton<IdManager>;

private:
  typedef std::unordered_map<GLuint, Block::Basic*> ids_type;

private:
  IdManager();

public:
  ~IdManager();
  GLuint getNewIdForBlock(Block::Basic* block);
  void deleteId(GLuint id);
  Block::Basic* getBlockFromId(GLuint id) const;

private:
  ids_type _ids;
};

#endif /* !IDMANAGER_HH_ */
