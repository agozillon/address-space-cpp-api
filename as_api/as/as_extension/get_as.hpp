#ifndef __GET_AS_HPP__
#define __GET_AS_HPP__

#include "add_as.hpp"

template<typename T, unsigned Nv = 0>
struct get_as {
   static const unsigned value = Nv;
};

template <typename T, unsigned Nv>
struct get_as<T __attribute__((address_space(Nv)))> {
  static const unsigned value = Nv;
};

template <typename T, unsigned Nv>
struct get_as<T const 	       __attribute__((address_space(Nv)))> {
  static const unsigned value = Nv;
};

template <typename T, unsigned Nv>
struct get_as<T 	  volatile __attribute__((address_space(Nv)))> {
  static const unsigned value = Nv;
};

template <typename T, unsigned Nv>
struct get_as<T const volatile __attribute__((address_space(Nv)))> {
  static const unsigned value = Nv;
};

template <typename T>
/*inline*/ constexpr auto get_as_v = get_as<T>::value;

/* -------------------------------------------------------------------------- */

namespace get_as_hpp_tests {

static_assert(0  == get_as_v<add_as_t<float,0>>,"");
static_assert(0  == get_as_v<float>,"");
static_assert(1  == get_as_v<add_as_t<float,1>>,"");
static_assert(1  == get_as_v<__attribute__((address_space(1))) float>,"");
static_assert(42 == get_as_v<add_as_t<float,42>>,"");
static_assert(42 == get_as_v<__attribute__((address_space(42))) float>,"");

} // namespace get_as_hpp_tests

#endif // __GET_AS_HPP__
