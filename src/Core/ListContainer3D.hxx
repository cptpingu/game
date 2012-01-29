namespace Core
{
  template <typename T>
  ListContainer3D<T>::ListContainer3D()
    : _list()
  {
  }

  template <typename T>
  ListContainer3D<T>::~ListContainer3D()
  {
    clear();
  }

  template <typename T>
  inline void
  ListContainer3D<T>::add(T* item)
  {
    _list.push_back(item);
  }

  template <typename T>
  inline void
  ListContainer3D<T>::clear()
  {
    const_iterator end = _list.end();
    for (const_iterator it = _list.begin(); it != end; ++it)
      delete *it;
    _list.clear();
  }

  template <typename T>
  inline size_t
  ListContainer3D<T>::size() const
  {
    return _list.size();
  }

  template <typename T>
  inline typename ListContainer3D<T>::const_iterator
  ListContainer3D<T>::begin() const
  {
    return _list.begin();
  }

  template <typename T>
  inline typename ListContainer3D<T>::const_iterator
  ListContainer3D<T>::end() const
  {
    return _list.end();
  }
} // Core
