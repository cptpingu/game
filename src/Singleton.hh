#ifndef SINGLETON_HH_
# define SINGLETON_HH_

/*!
** @brief this template is an helper to make a singleton.
**
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
  /** Retrives the instance. */
  static T& getInstance();
};

# include "Singleton.hxx"

#endif /* !SINGLETON_HH_ */
