#include "GroupBlock.hh"
#include "../TextureManager.hh"
#include "../ShadersManager.hh"
#include "../Model/StaticModelManager.hh"

#include "../Model/StaticCubeModel.hh"

#include <algorithm>

namespace Block
{
  GroupBlock::GroupBlock()
  {
  }

  GroupBlock::~GroupBlock()
  {
    auto end = _assoc.cend();
    for (auto it = _assoc.cbegin(); it != end; ++it)
      delete it->second;
  }

  void
  GroupBlock::add(int index, Block::Basic* block)
  {
    if (block->isNullIndex(index))
      return;

    auto found = _assoc.find(index);
    if (found == _assoc.end())
    {
      auto pair = _assoc.insert(assoc_type::value_type(index, new list_type));
      ASSERT(pair.second);
      found = pair.first;
    }
    ASSERT_MSG(found != _assoc.end(), "Error while adding model state!");
    found->second->push_back(block);
  }

  void
  GroupBlock::remove(int index, Block::Basic* block)
  {
    if (block->isNullIndex(index))
      return;

    auto found = _assoc.find(index);
    if (found == _assoc.end())
      return;

    auto res = std::remove(found->second->begin(), found->second->end(), block);
    if (res != found->second->end())
      found->second->erase(res, found->second->end());
  }

  void drawModelState(int index, const GroupBlock::list_type* list, GLuint uniform,
                      bool picking)
  {
    const Model::MemoryPiece& mem = Model::CubeModel::getInstance().bindVBO(index);
    auto end = list->cend();
    for (auto it = list->cbegin(); it != end; ++it)
    {
      if (picking)
        (*it)->drawPickingBox(mem);
      else
      {
        glUniform1f(uniform, (*it)->isHighlight() ? 0.2 : 0.0);
        (*it)->draw(mem);
        (*it)->resetHighlight();
      }
    }
  }

  void
  GroupBlock::draw() const
  {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_INDEX_ARRAY);

    ShadersManager& shaders = ShadersManager::getInstance();
    shaders.enable("cube");
    GLuint uniform = glGetUniformLocation(shaders.get("cube"), "cube_color");
    GLuint attrib = glGetAttribLocation(shaders.get("cube"), "face_color");
    glVertexAttrib1f(attrib, 0.0);

    TextureManager& textures = TextureManager::getInstance();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures["brick1"]);

    glBindBuffer(GL_ARRAY_BUFFER, Model::CubeModel::getInstance().getVboId());
    glVertexPointer(3, GL_FLOAT, 0, reinterpret_cast<void*>(0));
    glNormalPointer(GL_FLOAT, 0, reinterpret_cast<void*>(sizeof(Model::Cube::vertices)));
    glTexCoordPointer(3, GL_FLOAT, 0, reinterpret_cast<void*>(sizeof(Model::Cube::vertices) + sizeof(Model::Cube::normals)));

    auto end = _assoc.cend();
    for (auto it = _assoc.cbegin(); it != end; ++it)
      drawModelState(it->first, it->second, uniform, false);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_INDEX_ARRAY);
  }

  void
  GroupBlock::drawPicking() const
  {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_INDEX_ARRAY);

    ShadersManager::getInstance().disable();

    glBindBuffer(GL_ARRAY_BUFFER, Model::CubeModel::getInstance().getVboId());
    glVertexPointer(3, GL_FLOAT, 0, reinterpret_cast<void*>(0));

    auto end = _assoc.cend();
    for (auto it = _assoc.cbegin(); it != end; ++it)
      drawModelState(it->first, it->second, 0, true);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_INDEX_ARRAY);
  }
} // Block
