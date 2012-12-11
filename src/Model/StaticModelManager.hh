#ifndef MODEL_STATICMODELMANAGER_HH_
# define MODEL_STATICMODELMANAGER_HH_

namespace Model
{
  enum Type
  {
    CubeType,
    TriangleType
  };

  namespace StaticModelManager
  {
    void init();
    void release();
  } // StaticModelManager
} // Model


#endif /* !MODEL_STATICMODELMANAGER_HH_ */
