#ifndef NONCOPYABLE_HH_
# define NONCOPYABLE_HH_

namespace Core
{
  template <typename T>
  struct NonCopyable
  {
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    T& operator= (const T&) = delete;
//  protected:
//     NonCopyable()
//     {
//     }
//    ~NonCopyable ()
//    {
//    }

//  private:
//    NonCopyable(const NonCopyable&);
//    T& operator=(const T&);
  };
} // Core

#endif /* !NONCOPYABLE_HH */
