#ifndef LISTCONTAINER3D_HH_
# define LISTCONTAINER3D_HH_

# include <vector>

namespace Core
{
  /*!
  ** @class ListContainer3D
  **
  ** Generic way to store a list of 3D values.
  */
  template <typename T>
  class ListContainer3D
  {
  public:
    typedef T type;
    typedef std::vector<T*> list_type;
    typedef typename list_type::iterator iterator;
    typedef typename list_type::const_iterator const_iterator;

  public:
    ListContainer3D();
    ~ListContainer3D();

    void add(T* item);
    void clear();
    size_t size() const;
    const_iterator begin() const;
    const_iterator end() const;

  private:
    list_type _list;
  };
} // Core

# include "ListContainer3D.hxx"

#endif /* !LISTCONTAINER3D_HH_ */
