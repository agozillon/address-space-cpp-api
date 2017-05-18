#ifndef __REMOVE_POINTEE_AS_HPP__
#define __REMOVE_POINTEE_AS_HPP__

#include <memory> // std::pointer_traits

template <typename>
  struct remove_pointee_as;

template <typename T, unsigned Np, unsigned Nv>
struct remove_pointee_as<as_val<T,Np,Nv>> {
   using type = as_val<T,0,Nv>;
};

template <typename T>
struct remove_pointee_as<as_val<T, 0, 0>> {
   using type = T;
};

template <typename T>
using remove_pointee_as_t = typename remove_pointee_as<T>::type;

namespace remove_pointee_as_hpp_tests {

#define AS 42
using t1 = add_pointee_as_t<int  *,AS>;
using t2 = add_pointee_as_t<int **,AS>;
using t3    = add_pointee_as_t<int * volatile, AS>;
using t4    = add_pointee_as_t<int ** volatile, AS>;
using t5    = add_pointee_as_t<add_as_t<int ** volatile, 21>, AS>;
static_assert(std::is_same<remove_pointee_as_t<t1>, as_val<int *, 0, 0>>::value, "");
static_assert(std::is_same<remove_pointee_as_t<t2>, as_val<int **, 0, 0>>::value, "");
static_assert(std::is_same<remove_pointee_as_t<t3>, as_val<int * volatile, 0, 0>>::value, "");
static_assert(std::is_same<remove_pointee_as_t<t4>, as_val<int ** volatile, 0, 0>>::value, "");
static_assert(std::is_same<remove_pointee_as_t<t5>, as_val<int ** volatile, 0, 21>>::value, "");

static_assert(std::is_same<remove_pointee_as_t<add_pointee_as_t<float, 0>>, float>::value, "");
static_assert(std::is_same<remove_pointee_as_t<add_pointee_as_t<float, 1>>, as_val<float, 0, 0>>::value, "");
static_assert(std::is_same<remove_pointee_as_t<add_as_t<add_pointee_as_t<int *, 2>, 2>>, as_val<int *, 0, 2>>::value, ""); 
} // namespace remove_pointee_as_hpp_tests

#endif // __REMOVE_POINTEE_AS_HPP__
