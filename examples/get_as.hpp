#ifndef __GET_AS_HPP__
#define __GET_AS_HPP__

#include <type_traits>

namespace impl {

template <typename T, unsigned N>
struct same_space {
  static const bool value =
    std::is_convertible<
      std::add_pointer_t<T>, // handles references
      __attribute__((ext_address_space(N))) void *
    >::value;
};

template <typename T, unsigned N>
inline constexpr auto same_space_v = same_space<T,N>::value;

template <typename T, unsigned N>
struct get_as {
  static const unsigned value = same_space_v<T,N> ? N : get_as<T,N-1>::value;
};

template <typename T>
constexpr unsigned is_zero_as() {
  static_assert(same_space_v<T,0>, "Address space not found!");
  return 0;
}

template <typename T>
struct get_as<T,0> {
  static const unsigned value = 0; // same_space_v<T,0> ? 0 : ???
};

template <typename T, unsigned N>
inline constexpr auto get_as_v = get_as<T,N>::value;

template <typename T, unsigned N, unsigned ...Ms>
struct get_as_hints {
  static const unsigned value = get_as_v<T,N>;
};

template <typename T, unsigned N, unsigned M>
struct get_as_hints<T,N,M> {
  static const auto value = same_space_v<T,M> ? M : get_as_v<T,N>;
};

template <typename T, unsigned N, unsigned M, unsigned ...Ms>
struct get_as_hints<T,N,M,Ms...> {
  static const auto value =
    same_space_v<T,M> ? M : get_as_hints<T,N,Ms...>::value;
};

} // namespace impl

// Max AS is 8388607
const unsigned MAX_AS = 10; // 8388607
// template <typename T> using get_as = impl::get_as<T,MAX_AS>;
template <typename T> using get_as =
  impl::get_as_hints<T,MAX_AS,8388352,8388353,8388354/*,8388355*/>;

template <typename T>
inline constexpr auto get_as_v = get_as<T>::value;

// 4 OpenCL Address Spaces. Private is 0.
//8388352 // global
//8388353 // local
//8388354 // constant
//8388355 // generic!!

namespace get_as_hpp_tests {

static_assert(impl::same_space_v<int,0>);
static_assert(impl::same_space_v<int,8388355>);
// static_assert(8388355  == get_as_v<int>); // unexpected. Hopefully a bug.
// ICE:
//using generic_int_t = __attribute__((ext_address_space(8388355))) int;
//static_assert(impl::same_space_v<generic_int_t,8388355>);

//static_assert(3  == get_as_v<__attribute__((ext_address_space(3))) int>);
//using i8388352_t = __attribute__((ext_address_space(8388352))) int;
//static_assert(8388352 == get_as_v<i8388352_t>);
//static_assert(43 == get_as_v<__attribute__((ext_address_space(43))) int>);

} // namespace get_as_hpp_tests

#endif // __GET_AS_HPP__
