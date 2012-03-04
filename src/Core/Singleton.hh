#ifndef SINGLETON_HH_
# define SINGLETON_HH_

namespace Core
{
  /*!
  ** This template is an helper to make a singleton.
  ** How to use it:
  ** @code
  ** class MyClass : public Singleton<MyClass>
  ** {
  **   // ...
  ** };
  ** @endcode
  */
  template <typename T>
  class Singleton
  {
  public:
    /*!
    ** Retrives the instance.
    */
    static T& getInstance();
  };
} // Core

# include "Singleton.hxx"

#endif /* !SINGLETON_HH_ */
