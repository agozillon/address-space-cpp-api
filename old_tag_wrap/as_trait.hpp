#ifndef __AS_TRAIT_HPP__
#define __AS_TRAIT_HPP__

#include "basic.hpp"

template <typename, typename> struct tag_wrap;    // forward declaration

template <typename T>
struct as_trait {
  using type = T;
  static constexpr uint value = 0;
};

template <typename T, typename U>
struct as_trait<tag_wrap<T,U>> {
  using type = T;
  static constexpr U value = U{};
};

template <typename T, typename Is>
struct add_as {
  using type = tag_wrap<T,Is>;
};

#endif // __AS_TRAIT_HPP__
