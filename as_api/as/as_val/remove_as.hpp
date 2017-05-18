#ifndef __REMOVE_AS_HPP__
#define __REMOVE_AS_HPP__

#include "add_as.hpp"
#include "add_pointee_as.hpp"

template <typename>
  struct remove_as;

// You can't just return the type here, as that would remove any address spaces 
// tied to the pointee held in Np
template <typename T, unsigned Np, unsigned Nv>
struct remove_as<as_val<T,Np,Nv>> {
   using type = as_val<T,Np,0>;
};

template <typename T>
struct remove_as<as_val<T, 0, 0>> {
   using type = T;
};

template <typename T>
using remove_as_t = typename remove_as<T>::type;

namespace remove_as_hpp_tests {

static_assert(std::is_same<remove_as_t<add_as_t<float, 0>>, float>::value, "");
static_assert(std::is_same<remove_as_t<add_as_t<float, 1>>, as_val<float, 0, 0>>::value, "");
static_assert(std::is_same<remove_as_t<add_pointee_as_t<int *, 2>>, as_val<int *, 2, 0>>::value, ""); 

} // namespace remove_as_hpp_tests

#endif // __REMOVE_AS_HPP__
