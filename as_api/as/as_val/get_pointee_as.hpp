#ifndef __GET_POINTEE_AS_HPP__
#define __GET_POINTEE_AS_HPP__

#include "add_pointee_as.hpp"

template <typename>
  struct get_pointee_as;

template <typename T, unsigned Np, unsigned Nv>
struct get_pointee_as<as_val<T,Np,Nv>> {
  static const unsigned value = Np;
};

template <typename T>
constexpr auto get_pointee_as_v = get_pointee_as<T>::value;

namespace get_pointee_as_hpp_tests {

/*
static_assert(0  == get_pointee_as_v<add_pointee_as_t<float**,0>>, "");
static_assert(1  == get_pointee_as_v<add_pointee_as_t<double**,1>>, "");
static_assert(42 == get_pointee_as_v<add_pointee_as_t<int**,42>>, "");
static_assert(1  == get_pointee_as_v<as_val<float**, 1, 0>>, "");
*/
} // namespace get_pointee_as_hpp_tests

#endif // __GET_POINTEE_AS_HPP__
