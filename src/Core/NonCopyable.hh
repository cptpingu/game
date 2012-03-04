#ifndef NONCOPYABLE_HH_
# define NONCOPYABLE_HH_

namespace Core
{
  /*!
  ** @struct NonCopyable
  **
  ** This structure is used to ensure that an object can't be copied.
  */
  template <typename T>
  struct NonCopyable
  {
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    T& operator= (const T&) = delete;
  };
} // Core

#endif /* !NONCOPYABLE_HH */
