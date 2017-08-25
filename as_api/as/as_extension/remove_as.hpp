#ifndef __REMOVE_AS_HPP__
#define __REMOVE_AS_HPP__

#include <type_traits>

template <typename T, unsigned Nv = 0>
struct remove_as {
  using type =   T;
};

template <typename T, unsigned Nv>
struct remove_as<T                __attribute__((ext_address_space(Nv)))> {
  using type   = T;
};

template <typename T, unsigned Nv>
struct remove_as<T const          __attribute__((ext_address_space(Nv)))> {
  using type =   T const;
};

template <typename T, unsigned Nv>
struct remove_as<T       volatile __attribute__((ext_address_space(Nv)))> {
  using type =   T       volatile;
};

template <typename T, unsigned Nv>
struct remove_as<T const volatile __attribute__((ext_address_space(Nv)))> {
  using type =   T const volatile;
};

template <typename T>
using remove_as_t = typename remove_as<T>::type;

/* -------------------------------------------------------------------------- */

namespace remove_as_hpp_tests {

#define AS 42
#define ASN __attribute__((ext_address_space(AS)))

static_assert(std::is_same<
                remove_as_t<int const volatile ASN>,
                            int const volatile
              >::value);
static_assert(std::is_same<remove_as_t<int const ASN>,int const>::value);
static_assert(std::is_same<remove_as_t<int volatile ASN>,int volatile>::value);
static_assert(std::is_same<remove_as_t<int ASN>,int>::value);


static_assert(std::is_same<
                remove_as_t<int * const volatile ASN>,
                            int * const volatile
              >::value);
static_assert(std::is_same<remove_as_t<int * const ASN>,int * const>::value);
static_assert(std::is_same<
                remove_as_t<int * volatile ASN>,
                            int * volatile
              >::value);
static_assert(std::is_same<remove_as_t<int * ASN>,int *>::value);

static_assert(std::is_same<
                remove_as_t<int ** const volatile ASN>,
                            int ** const volatile
              >::value);
static_assert(std::is_same<
                remove_as_t<int ** const ASN>,
                            int ** const
              >::value);
static_assert(std::is_same<
                remove_as_t<int ** volatile ASN>,
                            int ** volatile
              >::value);
static_assert(std::is_same<remove_as_t<int ** ASN>,int **>::value);

// it should only remove the top level address space qualifier
static_assert(std::is_same<
                remove_as_t<int * const volatile ASN *>,
                            int * const volatile ASN *
              >::value);
static_assert(std::is_same<
                remove_as_t<int * const ASN *>,
                            int * const ASN *
              >::value);
static_assert(std::is_same<
                remove_as_t<int * volatile ASN *>,
                            int * volatile ASN *
              >::value);
static_assert(std::is_same<remove_as_t<int * ASN *>,int * ASN *>::value);

static_assert(std::is_same<
                remove_as_t<int const volatile ASN>,
                            int const volatile
              >::value);
static_assert(std::is_same<remove_as_t<int const ASN>,int const>::value);
static_assert(std::is_same<remove_as_t<int volatile ASN>,int volatile>::value);
static_assert(std::is_same<remove_as_t<int ASN>,int>::value);

} // namespace remove_as_hpp_tests

#endif // __REMOVE_AS_HPP__
