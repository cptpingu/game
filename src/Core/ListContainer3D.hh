#ifndef LISTCONTAINER3D_HH_
# define LISTCONTAINER3D_HH_

# include <vector>

namespace Core
{
  /*!
  ** @class ListContainer3DTrait
  **
  ** Generic way to store a list of 3D values.
  */
  template <typename T, bool is_pointer>
  class ListContainer3DTrait
  {
  public:
    typedef typename DerefType<T>::type raw_item_type;
    typedef T item_type;
    typedef std::vector<T> list_type;
    typedef typename list_type::iterator iterator;
    typedef typename list_type::const_iterator const_iterator;

  public:
    ListContainer3DTrait();
    ~ListContainer3DTrait();

    void add(item_type item);
    void clear();
    size_t size() const;
    const_iterator begin() const;
    const_iterator end() const;

  protected:
    list_type _list;
  };

  template <typename T>
  class ListContainer3DPtr : public ListContainer3DTrait<T, true>
  {
  };

  template <typename T>
  class ListContainer3D : public ListContainer3DTrait<T, false>
  {
  };

} // Core

# include "ListContainer3D.hxx"

#endif /* !LISTCONTAINER3D_HH_ */
