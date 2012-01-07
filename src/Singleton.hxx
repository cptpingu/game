template <typename T>
inline T&
Singleton<T>::getInstance()
{
  static T instance_;
  return instance_;
}
