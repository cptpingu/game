#ifndef MODEL_STATICMODELMANAGER_HH_
# define MODEL_STATICMODELMANAGER_HH_

# include "StaticCubeModel.hh"

namespace Model
{
  namespace StaticModelManager
  {
    void init()
    {
      Cube::init();
    }

    void release()
    {
      Cube::release();
    }
  } // StaticModelManager
} // Model


#endif /* !MODEL_STATICMODELMANAGER_HH_ */
