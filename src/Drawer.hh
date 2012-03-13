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
  /*!
  ** Draw the chunks.
  **
  ** @param chunks The chunks to draw.
  ** @param selectedCoord The selected coord (or 0 if nothing is selected).
  */
  void drawChunks(const Map::chunks_type& chunks, const Chunk::Coord* selectedCoord) const;

  /*!
  ** Draw the blocks.
  **
  ** @param blocks The blocks to draw.
  */
  void drawBlocks(const Map::blocks_type& blocks) const;

  /*!
  ** Draw the trees.
  **
  ** @param trees The trees to draw.
  */
  // void drawTrees(const Architecte::Model& trees) const;
};

#endif /* !DRAWER_HH_ */
