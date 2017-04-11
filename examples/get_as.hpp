#ifndef __REMOVE_AS_HPP__
#define __REMOVE_AS_HPP__

#include <type_traits>
#include "add_pointee_const.hpp"
#include "add_pointee_as.hpp"

template <typename T>
struct remove_as {
  using type = T;
};

template <typename T>
struct remove_as<T const> {
  using type = T;
};

template <typename T>
struct remove_as<T volatile> {
  using type = T;
};

template <typename T>
struct remove_as<T const volatile> {
  using type = T;
};

template <typename T>
using remove_as_t = typename remove_as<T>::type;

/* -------------------------------------------------------------------------- */

namespace remove_as_hpp_tests {
//void zod(__attribute__((ext_address_space(0))) T *p) {
//void zod(T *p) {
template <int N>
void zod(         __attribute__((ext_address_space(N))) void *p) { }
template <int N>
void zod(const    __attribute__((ext_address_space(N))) void *p) { }
template <int N>
void zod(volatile __attribute__((ext_address_space(N))) void *p) { }

template <typename T>
void zod2(T &x) {
  zod<3>(&x);
}

static_assert(std::is_convertible<
                __attribute__((ext_address_space(3))) int *,
                __attribute__((ext_address_space(3))) void *
              >::value);
/*static_assert(std::is_convertible<
                __attribute__((ext_address_space(3))) int **,
                __attribute__((ext_address_space(3))) void *
              >::value);
*/

static_assert(!std::is_convertible<
                __attribute__((ext_address_space(3))) bool (*)(int),
                __attribute__((ext_address_space(3))) void *
              >::value);
static_assert( std::is_function<bool  (int,double)>::value);
static_assert(!std::is_function<bool(*)(int,double)>::value);

template <typename T, int N>
struct same_space {
  static const bool value =
    std::is_convertible<
//      __attribute__((ext_address_space(3))) int *,
      std::add_pointer_t<T>, // handles references
//      T *,
      __attribute__((ext_address_space(N))) void *
    >::value;
};

static_assert(same_space<__attribute__((ext_address_space(3))) int,3>::value);
static_assert(same_space<int*  __attribute__((ext_address_space(3))),3>::value);
static_assert(same_space<int** __attribute__((ext_address_space(3))),3>::value);
static_assert(same_space<__attribute__((ext_address_space(3))) int &,3>::value);
static_assert(std::is_same<bool(int),bool(int)>::value);
static_assert(std::is_same<
                std::add_pointer_t<bool(int)>,
                bool(*)(int)
              >::value);

namespace proto {

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

template <typename T>
constexpr unsigned err() {
  static_assert(std::is_same<T,T*>::value,"Address space not found!");
  return {};
}

// Max AS is 8388607
template <typename T, unsigned N>
struct get_as {
  static const unsigned value = same_space_v<T,N> ? N : get_as<T,N-1>::value;
};

template <typename T>
struct get_as<T,0> {
  static const unsigned value = same_space_v<T,0> ? 0 : 12345;//err<T>();
};

template <typename T, unsigned N>
inline constexpr auto get_as_v = get_as<T,N>::value;

template <typename T, unsigned N, unsigned ...Ms>
struct get_as_hints {
  static const unsigned value = impl::get_as_v<T,N>;
};

template <typename T, unsigned N, unsigned M>
struct get_as_hints<T,N,M> {
  static const auto value = impl::same_space_v<T,M> ? M : impl::get_as_v<T,N>;
};

template <typename T, unsigned N, unsigned M, unsigned ...Ms>
struct get_as_hints<T,N,M,Ms...> {
  static const auto value =
    impl::same_space_v<T,M> ? M : get_as_hints<T,N,Ms...>::value;
};

} // namespace impl

// Max AS is 8388607
const unsigned MAX_AS = 10; // 8388607
// template <typename T> using get_as = impl::get_as<T,MAX_AS>;
template <typename T> using get_as = impl::get_as_hints<T,MAX_AS,42,43>;

template <typename T>
inline constexpr auto get_as_v = get_as<T>::value;

// 4 OpenCL Address Spaces. Private is 0.
//8388352
//8388353
//8388354
//8388355

static_assert(0  == get_as_v<int>);
static_assert(3  == get_as_v<__attribute__((ext_address_space(3))) int>);
static_assert(42 == get_as_v<__attribute__((ext_address_space(42))) int>);
static_assert(43 == get_as_v<__attribute__((ext_address_space(43))) int>);
//static_assert(42 == get_as_hints<__attribute__((ext_address_space(42))) int,10,42>::value);
/*static_assert(43 == get_as_hints<__attribute__((ext_address_space(43))) int,10,42,43>::value);
*/
//static_assert(get_as<__attribute__((ext_address_space(3))) int,3,9,10>::value);
} // namespace proto 

template <typename T, unsigned L = 10> // Max AS in LLVM is 8388607
constexpr unsigned get_as_ce() {
  using p_type_from = std::add_pointer_t<T>;
  using p_type_to   = __attribute__((ext_address_space(L))) void *;
  constexpr bool b = std::is_convertible<p_type_from, p_type_to>::value;

  if constexpr (b) { return L; }
  else return get_as_ce<T,L-1>();
}

template <typename T, unsigned L = 10, unsigned N>
constexpr unsigned get_as_ce() {
  return N;
}

static_assert(get_as_ce<__attribute__((ext_address_space(3)))  int,3>() == 3);
static_assert(get_as_ce<__attribute__((ext_address_space(42))) int,42>() == 42);

__attribute__((ext_address_space(3))) int g = 0;
void foo() {
  const int i = 0;
  __attribute__((ext_address_space(3))) int &xr = g;
  int j;
  int *p;
  j = (int)i;
  j = (int)g;
//  p = (__attribute__((ext_address_space(0))) int *)&g; //ICE
//  zod(&g);
  zod<3>(&g); // good
  zod2(g);
}

#define AS 42
#define ASN __attribute__((ext_address_space(AS)))
static_assert(std::is_same<remove_as_t<int>,int>::value);
static_assert(std::is_same<remove_as_t<int ASN>,int ASN>::value); // wrong

/*using t1 = add_pointee_as_t<int  *,AS>;
using t2 = add_pointee_as_t<int **,AS>;
using t3    = add_pointee_as_t<int       * volatile,AS>;
using t4    = add_pointee_as_t<int *     * volatile,AS>;
static_assert(std::is_same<t1, int   AS7 *>::value);
static_assert(std::is_same<t2, int * AS7 *>::value);
static_assert(std::is_same<t3, int   AS7 * volatile>::value);
static_assert(std::is_same<t4, int * AS7 * volatile>::value);

using t5    = add_pointee_as_t<std::shared_ptr<int    >,AS>;
using t6    = add_pointee_as_t<std::shared_ptr<int     volatile>,AS>;
using t7    = add_pointee_as_t<std::shared_ptr<int    > volatile,AS>;
using t8    = add_pointee_as_t<std::shared_ptr<int *    >,AS>;
using t9    = add_pointee_as_t<std::shared_ptr<int *    > volatile,AS>;
static_assert(std::is_same<t5, std::shared_ptr<int AS7>>::value);
static_assert(std::is_same<t6, std::shared_ptr<int AS7 volatile>>::value);
static_assert(std::is_same<t7, std::shared_ptr<int AS7> volatile>::value);
static_assert(std::is_same<t8, std::shared_ptr<int * AS7>>::value);
static_assert(std::is_same<t9, std::shared_ptr<int * AS7> volatile>::value);
*/
} // namespace remove_as_hpp_tests

#endif // __REMOVE_AS_HPP__
