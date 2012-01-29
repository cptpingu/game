#ifndef SOLTRIANGLE_HH_
# define SOLTRIANGLE_HH_

# include "Core/Container3D.hh"

class SolTriangle : public Core::Container3D<double>
{
  typedef Core::Container3D<double> super;

public:
  SolTriangle(double x, double y, double z)
    : super(x, y, z)
  {
  }
};

#endif /* !SOLTRIANGLE_HH_ */
