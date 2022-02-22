#ifndef __GET_POINTEE_AS_HPP__
#define __GET_POINTEE_AS_HPP__

#include "remove_as.hpp"

namespace impl {
template <typename T>
struct get_pointee_as {
  using e_type  = typename pointer_traits<T>::element_type;
  static const auto value = get_as_v<e_type>;
};

template <typename T>
constexpr auto get_pointee_as_v = impl::get_pointee_as<T>::value;
}

template<typename T, unsigned Nv = 0>
struct get_pointee_as {
   static const unsigned value = impl::get_pointee_as_v<T>;
};

template <typename T, unsigned Nv>
struct get_pointee_as<T __attribute__((address_space(Nv)))> {
  static const unsigned value = impl::get_pointee_as_v<T>;
};

template <typename T>
struct get_pointee_as<T const, 0> {
  static const unsigned value = impl::get_pointee_as_v<T>;
};

template <typename T>
struct get_pointee_as<T volatile, 0> {
  static const unsigned value = impl::get_pointee_as_v<T>;
};

template <typename T>
struct get_pointee_as<T const volatile, 0> {
  static const unsigned value = impl::get_pointee_as_v<T>;
};

template <typename T, unsigned Nv>
struct get_pointee_as<T const __attribute__((address_space(Nv)))> {
  static const unsigned value = impl::get_pointee_as_v<T>;
};

template <typename T, unsigned Nv>
struct get_pointee_as<T volatile __attribute__((address_space(Nv)))> {
  static const unsigned value = impl::get_pointee_as_v<T>;
};

template <typename T, unsigned Nv>
struct get_pointee_as<T const volatile __attribute__((address_space(Nv)))> {
  static const unsigned value = impl::get_pointee_as_v<T>;
};

template <typename T>
constexpr auto get_pointee_as_v = get_pointee_as<T>::value;

/* -------------------------------------------------------------------------- */

namespace get_pointee_as_hpp_tests {

static_assert(0  == get_pointee_as_v<float**>, "");
static_assert(7  == get_pointee_as_v<add_pointee_as_t<double**,7>>, "");
static_assert(42 == get_pointee_as_v<add_pointee_as_t<int**,42>>, "");
static_assert(0 == get_pointee_as_v<add_pointee_as_t<float*,42>*>, "");
static_assert(1  == get_pointee_as_v<float * __attribute__((address_space(1))) *>, "");
} // namespace get_pointee_as_hpp_tests


#endif // __GET_POINTEE_AS_HPP__
