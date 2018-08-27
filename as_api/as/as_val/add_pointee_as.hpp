#ifndef __ADD_POINTEE_AS_HPP__
#define __ADD_POINTEE_AS_HPP__

template <typename T, unsigned Np>
struct add_pointee_as {
  using type  = as_val<T, Np, 0>;
};

template <typename T, unsigned Np, unsigned Nv, unsigned _Np>
struct add_pointee_as<as_val<T,Np,Nv>, _Np> {
  using type  = as_val<T, _Np, Nv>;
};

template <typename T, unsigned _Np>
using add_pointee_as_t = typename add_pointee_as<T, _Np>::type;

namespace add_pointee_as_hpp_tests {
/*
#define AS 42
using t1 = add_pointee_as_t<int  *,AS>;
using t2 = add_pointee_as_t<int **,AS>;
using t3    = add_pointee_as_t<int * volatile, AS>;
using t4    = add_pointee_as_t<int ** volatile, AS>;
using t5    = add_pointee_as_t<add_as_t<int ** volatile, 21>, AS>;
static_assert(std::is_same<t1, as_val<int *, AS, 0>>::value, "");
static_assert(std::is_same<t2, as_val<int **, AS, 0>>::value, "");
static_assert(std::is_same<t3, as_val<int * volatile, AS, 0>>::value, "");
static_assert(std::is_same<t4, as_val<int ** volatile, AS, 0>>::value, "");
static_assert(std::is_same<t5, as_val<int ** volatile, AS, 21>>::value, "");
*/
} // namespace add_pointee_as_hpp_tests

#endif // __ADD_POINTEE_AS_HPP__
