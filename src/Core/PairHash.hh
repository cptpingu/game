#ifndef PAIRHASH_HH_
# define PAIRHASH_HH_

# include <utility>
# include <unordered_map>
# include <cstddef>

namespace Core
{
  /*!
  ** @class PairHash
  **
  ** Hash class for std::unorderd_map used with a std::pair.
  */
  template <typename A, typename B>
  class PairHash
  {
  public:
    PairHash()
      : ah(), bh()
    {
    }

    size_t operator()(const std::pair<A, B>& p) const
    {
      size_t seed = ah(p.first);
      return bh(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

  private:
    const std::hash<A> ah;
    const std::hash<B> bh;
  };
} // Core

#endif /* !PAIRHASH_HH_ */
