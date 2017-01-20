#ifndef __AS_TRAIT_HPP__
#define __AS_TRAIT_HPP__

#include "basic.hpp"

template <typename, typename> struct as;    // forward declaration

template <typename T>
struct as_trait {
  using type = T;
  static constexpr uint value = 0;
};

template <typename T, typename Is>
struct as_trait<as<T,Is>> {
  using type = T;
  static constexpr Is value = Is{};
};

template <typename T, typename Is>
struct add_as {
  using type = as<T,Is>;
};

#endif // __AS_TRAIT_HPP__
