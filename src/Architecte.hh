#ifndef ARCHITECTE_HH_
# define ARCHITECTE_HH_

# include "Vector3D.hh"
# include "Map.hh"
# include "Chunk.hh"

namespace Architecte
{
  void building(Map::blocks_type& tmp, const Vector3D& where, int longueur, int hauteur, int largeur);
  void mountain(Chunk& tmp,const Vector3D& where, double peak, int size);
  void mergeGround(Chunk& generateRandomGround, const Chunk& deformation);

  void initChunk(Chunk::chunk_coord_type& coords, const std::pair<int, int>& where, const Map::chunks_type& chunks);
  void smoothGround(Chunk::chunk_coord_type& coords);
  void extractCoords(Chunk::texture_coord_type& extracted, const Chunk::chunk_coord_type& coords);
}

#endif /* !ARCHITECTE_HH_ */
