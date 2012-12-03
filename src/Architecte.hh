#ifndef ARCHITECTE_HH_
# define ARCHITECTE_HH_

# include "Core/Vector3D.hh"
# include "Map.hh"
# include "Chunk.hh"
# include <vector>


namespace Architecte
{

  typedef Core::Container3D<double> Model_Point;
  typedef std::vector<Model_Point> Model;

  void building(Map::blocks_type& tmp, const Core::Vector3D& where, int longueur, int hauteur, int largeur);
  void mountain(Chunk& tmp,const Core::Vector3D& where, double peak, int size);
  void mergeGround(Chunk& generateRandomGround, const Chunk& deformation);
  void borderSmooth(Chunk::chunk_coord_type& coords);
  void smoothGround(Chunk::chunk_coord_type& coords);
  void Initground(Chunk::chunk_coord_type& coords,int Quality);
  void Mountain(Chunk::chunk_coord_type& coords, const std::pair<int, int>& where,int PeakX,int PeakY,double PeakZ,double R_ext);
  void TreeProcess(Model & Tree,int size,int Density,const Model &where);

  Model_Point Branche(int size,int diffusionX,int diffusionY,const Model_Point &where);
  //void drawTree(Chunk::Model & Tree);

  double Norm(double x,double y,double z,int type);

  double Norm(Core::Vector3D where,int type);

  void initChunk(Chunk::chunk_coord_type& coords, const std::pair<int, int>& where, const Map::chunks_type& chunks);

}

#endif /* !ARCHITECTE_HH_ */
