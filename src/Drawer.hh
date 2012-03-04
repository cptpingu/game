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
    Drawer();

    /*!
    ** Draw the map.
    **
    ** @param map The map to draw.
    */
    void drawMap(const Map &map) const;
};

#endif /* !DRAWER_HH_ */
