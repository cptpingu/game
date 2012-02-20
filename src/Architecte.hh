#ifndef ARCHITECTE_HH_
# define ARCHITECTE_HH_

# include "Vector3D.hh"
# include "Map.hh"
# include "Chunk.hh"

namespace Architecte
{
  void generateRandomGround(Chunk& tmp, const Vector3D& where);
  void building(Map::blocks_type& tmp, const Vector3D& where, int longueur, int hauteur, int largeur);
  void mountain(Map::triangles_type& tmp,const Vector3D& where, double peak, int size);
  void mergeGround(Map::triangles_type& generateRandomGround, const Map::triangles_type& deformation);
  /*void interpolateCoords(std::vector<Chunk::Coord*> destination , const std::vector<Chunk::Coord*>& source);*/
  Chunk::texture_coord_type generateGround();

  Chunk::chunk_type initChunk(const std::pair<int, int>& Where, const Map::chunks_type& chunks);
  void smoothGround(Chunk::chunk_type& coords, int size);
  Chunk::texture_coord_type extractCoords(const Chunk::chunk_type& coords, int size);
}

#endif /* !ARCHITECTE_HH_ */
