#include "StaticCubeModel.hh"

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
