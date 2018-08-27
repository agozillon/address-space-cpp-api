#ifndef __GET_POINTEE_AS_HPP__
#define __GET_POINTEE_AS_HPP__

#include "add_pointee_as.hpp"

template<typename T, unsigned Nv = 0>
struct get_pointee_as {
   static const unsigned value = Nv;
};

template <typename T, unsigned Nv>
struct get_pointee_as<T __attribute__((address_space(Nv))) *> {
  static const unsigned value = Nv;
};

template <typename T, unsigned Nv>
struct get_pointee_as<T const 		   __attribute__((address_space(Nv))) *> {
  static const unsigned value = Nv;
};

template <typename T, unsigned Nv>
struct get_pointee_as<T 	  volatile __attribute__((address_space(Nv))) *> {
  static const unsigned value = Nv;
};

template <typename T, unsigned Nv>
struct get_pointee_as<T const volatile __attribute__((address_space(Nv))) *> {
  static const unsigned value = Nv;
};

template <typename T>
/*inline*/ constexpr auto get_pointee_as_v = get_pointee_as<T>::value;

/* -------------------------------------------------------------------------- */

namespace get_pointee_as_hpp_tests {

static_assert(0  == get_pointee_as_v<float**>, "");
static_assert(7  == get_pointee_as_v<add_pointee_as_t<double**,7>>, "");
static_assert(42 == get_pointee_as_v<add_pointee_as_t<int**,42>>, "");
static_assert(0 == get_pointee_as_v<add_pointee_as_t<float*,42>*>, "");
static_assert(1  == get_pointee_as_v<float * __attribute__((address_space(1))) *>, "");
} // namespace get_pointee_as_hpp_tests

#endif // __GET_POINTEE_AS_HPP__
