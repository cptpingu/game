#ifndef MODEL_STATICMODELMANAGER_HH_
# define MODEL_STATICMODELMANAGER_HH_

# include "StaticCubeModel.hh"

namespace Model
{
  namespace StaticModelManager
  {
    void init()
    {
      CubeModel::getInstance().init();
    }

    void release()
    {
      CubeModel::getInstance().release();
    }
  } // StaticModelManager
} // Model


#endif /* !MODEL_STATICMODELMANAGER_HH_ */
