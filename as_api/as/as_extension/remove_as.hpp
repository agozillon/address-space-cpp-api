#ifndef __REMOVE_AS_HPP__
#define __REMOVE_AS_HPP__

#ifdef __CL_TRAITS__
#include <__ocl_type_traits.h>
using namespace cl;
#else
#include <type_traits>
#include <memory> // std::pointer_traits
using namespace std;
#endif

template <typename T, unsigned Nv = 0>
struct remove_ass {
  using type =   T;
};

template <typename T, unsigned Nv>
struct remove_ass<T                __attribute__((address_space(Nv)))> {
  using type   = T;
};

template <typename T, unsigned Nv>
struct remove_ass<T const          __attribute__((address_space(Nv)))> {
  using type =   T const;
};

template <typename T, unsigned Nv>
struct remove_ass<T       volatile __attribute__((address_space(Nv)))> {
  using type =   T       volatile;
};

template <typename T, unsigned Nv>
struct remove_ass<T const volatile __attribute__((address_space(Nv)))> {
  using type =   T const volatile;
};

template <typename T>
using remove_ass_t = typename remove_ass<T>::type;

/* -------------------------------------------------------------------------- */

namespace remove_as_hpp_tests {
#define AS 42
#define ASN __attribute__((address_space(AS)))

static_assert(is_same<
              remove_ass_t<int const volatile ASN>,
                           int const volatile
              >::value, "");
static_assert(is_same<remove_ass_t<int volatile ASN>,int volatile>::value,"");
static_assert(is_same<remove_ass_t<int const ASN>,int const>::value,"");
static_assert(is_same<remove_const_t<remove_ass_t<int const ASN>>,int>::value,"");
static_assert(is_same<remove_ass_t<int ASN>,int>::value,"");

static_assert(is_same<
              remove_ass_t<int * const volatile ASN>,
                          int * const volatile
              >::value,"");
static_assert(is_same<remove_ass_t<int * const ASN>,int * const>::value,"");
static_assert(is_same<
              remove_ass_t<int * volatile ASN>,
                          int * volatile
              >::value,"");
static_assert(is_same<remove_ass_t<int * ASN>,int *>::value,"");

static_assert(is_same<
              remove_ass_t<int ** const volatile ASN>,
                          int ** const volatile
              >::value,"");
static_assert(is_same<
              remove_ass_t<int ** const ASN>,
                          int ** const
              >::value,"");
static_assert(is_same<
              remove_ass_t<int ** volatile ASN>,
                          int ** volatile
              >::value,"");
static_assert(is_same<remove_ass_t<int ** ASN>,int **>::value,"");

// it should only remove the top level address space qualifier
static_assert(is_same<
              remove_ass_t<int * const volatile ASN *>,
                          int * const volatile ASN *
              >::value, "");

static_assert(is_same<
              remove_ass_t<int * const ASN *>,
                          int * const ASN *
              >::value, "");

static_assert(is_same<
              remove_ass_t<int * volatile ASN *>,
                          int * volatile ASN *
              >::value, "");

static_assert(is_same<remove_ass_t<int * ASN *>,int * ASN *>::value, "");

static_assert(is_same<
              remove_ass_t<int const volatile ASN>,
                          int const volatile
              >::value, "");
static_assert(is_same<remove_ass_t<int const ASN>,int const>::value, "");
static_assert(is_same<remove_ass_t<int volatile ASN>,int volatile>::value, "");
static_assert(is_same<remove_ass_t<int ASN>,int>::value, "");

} // namespace remove_as_hpp_tests

#endif // __REMOVE_AS_HPP__
