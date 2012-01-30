namespace Core
{
  template <typename T, bool is_pointer>
  ListContainer3DTrait<T, is_pointer>::ListContainer3DTrait()
    : _list()
  {
  }

  template <typename T, bool is_pointer>
  ListContainer3DTrait<T, is_pointer>::~ListContainer3DTrait()
  {
    clear();
  }

  template <typename T, bool is_pointer>
  inline void
  ListContainer3DTrait<T, is_pointer>::add(item_type item)
  {
    _list.push_back(item);
  }

  template <typename T, bool is_pointer>
  inline void
  ListContainer3DTrait<T, is_pointer>::clear()
  {
    const_iterator end = _list.end();
    for (const_iterator it = _list.begin(); it != end; ++it)
      delete *it;
    _list.clear();
  }

  template <typename T, bool is_pointer>
  inline size_t
  ListContainer3DTrait<T, is_pointer>::size() const
  {
    return _list.size();
  }

  template <typename T, bool is_pointer>
  inline typename ListContainer3DTrait<T, is_pointer>::const_iterator
  ListContainer3DTrait<T, is_pointer>::begin() const
  {
    return _list.begin();
  }

  template <typename T, bool is_pointer>
  inline typename ListContainer3DTrait<T, is_pointer>::const_iterator
  ListContainer3DTrait<T, is_pointer>::end() const
  {
    return _list.end();
  }
} // Core
