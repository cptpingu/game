#ifndef DRAWER_HH_
# define DRAWER_HH_

# include "Map.hh"

/*!
** @class Drawer
**
** This class is used to draw every aspect of the game.
*/
class Drawer
{
public:
  void drawPickingBox(const Map& map) const;

  /*!
  ** Draw the blocks.
  **
  ** @param map The current map.
  */
  void drawBlocks(const Map& map) const;



  /*!
  ** Draw the trees.
  **
  ** @param trees The trees to draw.
  */
  // void drawTrees(const Architecte::Model& trees) const;

  /*!
  **Light fixing ....*/
  void light(unsigned int timestep);

  std::vector<Core::Vector3D> collisionlist(const  Core::Vector3D &from,const Core::Vector3D &to);
  void initVBO(const Map& map);
  void drawVBO();
  void drawSomeBlocks(Map& map);

};

#endif /* !DRAWER_HH_ */
