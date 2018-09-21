#ifndef __REMOVE_POINTEE_AS_HPP__
#define __REMOVE_POINTEE_AS_HPP__

#ifdef __CL_TRAITS__
#include "../trait_helpers/cl_pointer_traits.hpp"
using namespace cl_traits;
using namespace cl;
#else
#include <memory> // std::pointer_traits
using namespace std;
#endif

#include "remove_as.hpp"

namespace impl {

template <typename T>
struct remove_pointee_as {
  using e_type  = typename pointer_traits<T>::element_type;
  using as_type = remove_as_t<e_type>;
  using   type  = typename pointer_traits<T>::template rebind<as_type>;
};

template <typename T>
using remove_pointee_as_t = typename remove_pointee_as<T>::type;

} // namespace impl

// Handles fancy pointers  -   like std::pointer_traits.
// Handles qualifier arguments - unlike std::pointer_traits! 
// Perhaps it's possible to make this implementation a little more concise? A.G
template <typename T, unsigned Nv = 0>
struct remove_pointee_as {
  using type = impl::remove_pointee_as_t<T>;
};

template <typename T, unsigned Nv>
struct remove_pointee_as<T const, Nv> {
  using type = impl::remove_pointee_as_t<T> const;
};

template <typename T, unsigned Nv>
struct remove_pointee_as<T volatile, Nv> {
  using type = impl::remove_pointee_as_t<T> volatile;
};

template <typename T, unsigned Nv>
struct remove_pointee_as<T __attribute__((address_space(Nv)))> {
  using type = impl::remove_pointee_as_t<T> __attribute__((address_space(Nv)));
};

template <typename T, unsigned Nv>
struct remove_pointee_as<T const volatile, Nv> {
  using type = impl::remove_pointee_as_t<T> const volatile;
};

template <typename T, unsigned Nv>
struct remove_pointee_as<T const __attribute__((address_space(Nv)))> {
  using type = impl::remove_pointee_as_t<T> const __attribute__((address_space(Nv)));
};

template <typename T, unsigned Nv>
struct remove_pointee_as<T volatile __attribute__((address_space(Nv)))> {
  using type = impl::remove_pointee_as_t<T> volatile __attribute__((address_space(Nv)));
};

template <typename T, unsigned Nv>
struct remove_pointee_as<T const volatile __attribute__((address_space(Nv)))> {
  using type = impl::remove_pointee_as_t<T> const volatile __attribute__((address_space(Nv)));
};

template <typename T>
using remove_pointee_as_t = typename remove_pointee_as<T>::type;

/* -------------------------------------------------------------------------- */

namespace remove_pointee_as_hpp_tests {
#define AS 42
#define ASN __attribute__((address_space(AS)))

using t1 = add_pointee_as_t<int  *,AS>;
using t2 = add_pointee_as_t<int **,AS>;
using t3 = add_pointee_as_t<int       * volatile,AS>;
using t4 = add_pointee_as_t<int *     * volatile,AS>;
using t5 = int ASN * ASN *; //int ASN * ASN * ASN * const ASN;  
using t6 = add_pointee_as_t<int const volatile *,AS>;
using t7 = add_pointee_as_t<int const volatile * const volatile *,AS>;
using t8 = ASN float * ASN;

static_assert(is_same<remove_pointee_as_t<t1>, int *>::value, "");
static_assert(is_same<remove_pointee_as_t<t2>, int **>::value, "");
static_assert(is_same<remove_pointee_as_t<t3>, int * volatile>::value, "");
static_assert(is_same<remove_pointee_as_t<t4>, int ** volatile>::value, "");
static_assert(is_same<remove_pointee_as_t<t5>,int ASN * *>::value, "");
static_assert(is_same<remove_pointee_as_t<t6>, int const volatile *>::value, "");
static_assert(is_same<remove_pointee_as_t<t7>, int const volatile * const volatile *>::value, "");
static_assert(is_same<remove_pointee_as_t<t8>, float * ASN>::value, "");

#ifndef __CL_TRAITS__
using t9     = add_pointee_as_t<shared_ptr<int    >,AS>;
using t10     = add_pointee_as_t<shared_ptr<int     volatile>,AS>;
using t11    = add_pointee_as_t<shared_ptr<int    > volatile,AS>;
using t12    = add_pointee_as_t<shared_ptr<int *    >,AS>;
using t13    = add_pointee_as_t<shared_ptr<int *    > volatile,AS>;
static_assert(is_same<remove_pointee_as_t<t9>, shared_ptr<int>>::value,"");
static_assert(is_same<remove_pointee_as_t<t10>, shared_ptr<int volatile>>::value,"");
static_assert(is_same<remove_pointee_as_t<t11>, shared_ptr<int> volatile>::value,"");
static_assert(is_same<remove_pointee_as_t<t12>, shared_ptr<int *>>::value,"");
static_assert(is_same<remove_pointee_as_t<t13>, shared_ptr<int *> volatile>::value,"");
#endif

} // namespace remove_pointee_as_hpp_tests


#endif // __REMOVE_POINTEE_AS_HPP__
