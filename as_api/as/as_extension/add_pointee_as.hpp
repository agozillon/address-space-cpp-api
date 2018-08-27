#ifndef __ADD_POINTEE_AS_HPP__
#define __ADD_POINTEE_AS_HPP__

#ifdef __CL_TRAITS__
#include "../trait_helpers/cl_pointer_traits.hpp"
using namespace cl_traits;
#else
#include <type_traits>
#include <memory> // std::pointer_traits
using namespace std;
#endif



namespace impl {

template <typename T, unsigned Np>
struct add_pointee_as {
  using e_type  = typename pointer_traits<T>::element_type;
  using as_type = __attribute__((address_space(Np))) e_type;
  using   type  = typename pointer_traits<T>::template rebind<as_type>;
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
#define ASN __attribute__((address_space(AS)))
using t1 = add_pointee_as_t<int  *,AS>;
using t2 = add_pointee_as_t<int **,AS>;
using t3    = add_pointee_as_t<int       * volatile,AS>;
using t4    = add_pointee_as_t<int *     * volatile,AS>;
static_assert(is_same<t1, int   ASN *>::value,"");
static_assert(is_same<t2, int * ASN *>::value,"");
static_assert(is_same<t3, int   ASN * volatile>::value,"");
static_assert(is_same<t4, int * ASN * volatile>::value,"");

#ifndef __CL_TRAITS__
using t5    = add_pointee_as_t<shared_ptr<int    >,AS>;
using t6    = add_pointee_as_t<shared_ptr<int     volatile>,AS>;
using t7    = add_pointee_as_t<shared_ptr<int    > volatile,AS>;
using t8    = add_pointee_as_t<shared_ptr<int *    >,AS>;
using t9    = add_pointee_as_t<shared_ptr<int *    > volatile,AS>;
static_assert(is_same<t5, shared_ptr<int ASN>>::value,"");
static_assert(is_same<t6, shared_ptr<int ASN volatile>>::value,"");
static_assert(is_same<t7, shared_ptr<int ASN> volatile>::value,"");
static_assert(is_same<t8, shared_ptr<int * ASN>>::value,"");
static_assert(is_same<t9, shared_ptr<int * ASN> volatile>::value,"");
#endif

} // namespace add_pointee_as_hpp_tests

#endif // __ADD_POINTEE_AS_HPP__
