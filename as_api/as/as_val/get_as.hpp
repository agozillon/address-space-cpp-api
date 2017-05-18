#ifndef __GET_AS_HPP__
#define __GET_AS_HPP__

#include "add_as.hpp"

template <typename>
  struct get_as;

template <typename T, unsigned Np, unsigned Nv>
struct get_as<as_val<T,Np,Nv>> {
  static const unsigned value = Nv;
};

template <typename T>
constexpr auto get_as_v = get_as<T>::value;

namespace get_as_hpp_tests {

static_assert(0  == get_as_v<add_as_t<float,0>>, "");
static_assert(1  == get_as_v<add_as_t<float,1>>, "");
static_assert(42 == get_as_v<add_as_t<float,42>>, "");

} // namespace get_as_hpp_tests

#endif // __GET_AS_HPP__
