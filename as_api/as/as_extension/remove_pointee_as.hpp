#ifndef __REMOVE_POINTEE_AS_HPP__
#define __REMOVE_POINTEE_AS_HPP__

#include <memory> // std::pointer_traits
#include "remove_as.hpp"

namespace impl {

template <typename T>
struct remove_pointee_as {
  using e_type  = typename std::pointer_traits<T>::element_type;
  using as_type = remove_as_t<e_type>;
  using   type  = typename std::pointer_traits<T>::template rebind<as_type>;
};

template <typename T>
using remove_pointee_as_t = typename remove_pointee_as<T>::type;

} // namespace impl

// Handles fancy pointers  -   like std::pointer_traits.
// Handles const arguments - unlike std::pointer_traits!

template <typename T>
struct remove_pointee_as {
  using type = impl::remove_pointee_as_t<T>;
};

template <typename T>
struct remove_pointee_as<T const> {
  using type = impl::remove_pointee_as_t<T> const;
};

template <typename T>
struct remove_pointee_as<T volatile> {
  using type = impl::remove_pointee_as_t<T> volatile;
};

template <typename T>
struct remove_pointee_as<T const volatile> {
  using type = impl::remove_pointee_as_t<T> const volatile;
};

template <typename T>
using remove_pointee_as_t = typename remove_pointee_as<T>::type;

/* -------------------------------------------------------------------------- */

namespace remove_pointee_as_hpp_tests {

#define AS 42
#define ASN __attribute__((ext_address_space(AS)))
using t1 = add_pointee_as_t<int  *,AS>;
using t2 = add_pointee_as_t<int **,AS>;
using t3    = add_pointee_as_t<int       * volatile,AS>;
using t4    = add_pointee_as_t<int *     * volatile,AS>;
static_assert(std::is_same<remove_pointee_as_t<t1>, int *>::value);
static_assert(std::is_same<remove_pointee_as_t<t2>, int **>::value);
static_assert(std::is_same<remove_pointee_as_t<t3>, int * volatile>::value);
static_assert(std::is_same<remove_pointee_as_t<t4>, int ** volatile>::value);

using t5    = add_pointee_as_t<std::shared_ptr<int    >,AS>;
using t6    = add_pointee_as_t<std::shared_ptr<int     volatile>,AS>;
using t7    = add_pointee_as_t<std::shared_ptr<int    > volatile,AS>;
using t8    = add_pointee_as_t<std::shared_ptr<int *    >,AS>;
using t9    = add_pointee_as_t<std::shared_ptr<int *    > volatile,AS>;
static_assert(std::is_same<remove_pointee_as_t<t5>, std::shared_ptr<int>>::value);
static_assert(std::is_same<remove_pointee_as_t<t6>, std::shared_ptr<int volatile>>::value);
static_assert(std::is_same<remove_pointee_as_t<t7>, std::shared_ptr<int> volatile>::value);
static_assert(std::is_same<remove_pointee_as_t<t8>, std::shared_ptr<int *>>::value);
static_assert(std::is_same<remove_pointee_as_t<t9>, std::shared_ptr<int *> volatile>::value);

} // namespace remove_pointee_as_hpp_tests

#endif // __REMOVE_POINTEE_AS_HPP__
