#ifndef __ADD_POINTEE_AS_HPP__
#define __ADD_POINTEE_AS_HPP__

namespace impl {

template <typename T, unsigned Np>
struct add_pointee_as {
  using e_type  = typename std::pointer_traits<T>::element_type;
  using as_type = __attribute__((ext_address_space(Np))) e_type;
  using   type  = typename std::pointer_traits<T>::template rebind<as_type>;
};

template <typename T, unsigned Np>
using add_pointee_as_t = typename add_pointee_as<T,Np>::type;

} // namespace impl

// Handles fancy pointers  -   like std::pointer_traits.
// Handles const arguments - unlike std::pointer_traits!
template <typename T, unsigned Np>
struct add_pointee_as {
  using type = impl::add_pointee_as_t<T,Np>;
};

template <typename T, unsigned Np>
struct add_pointee_as<T const,Np> {
  using type = impl::add_pointee_as_t<T,Np> const;
};

template <typename T, unsigned Np>
struct add_pointee_as<T volatile,Np> {
  using type = impl::add_pointee_as_t<T,Np> volatile;
};

template <typename T, unsigned Np>
struct add_pointee_as<T const volatile,Np> {
  using type = impl::add_pointee_as_t<T,Np> const volatile;
};

template <typename T, unsigned Np>
using add_pointee_as_t = typename add_pointee_as<T,Np>::type;

/* -------------------------------------------------------------------------- */

namespace add_pointee_as_hpp_tests {

#define AS 42
#define AS7 __attribute__((ext_address_space(AS)))
using t1 = add_pointee_as_t<int  *,AS>;
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

} // namespace add_pointee_as_hpp_tests

#endif // __ADD_POINTEE_AS_HPP__
