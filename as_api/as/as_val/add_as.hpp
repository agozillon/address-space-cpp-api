#ifndef __ADD_AS_HPP__
#define __ADD_AS_HPP__

#include "as_val.hpp"

template <typename T, unsigned Nv>
struct add_as {
  using type = as_val<T,0,Nv>;
};

template <typename T, unsigned Np, unsigned Nv, unsigned Nv_>
struct add_as<as_val<T,Np,Nv>, Nv_> {
  using type = as_val<T,Np,Nv_>;
};

template <typename T, unsigned Nv>
using add_as_t = typename add_as<T,Nv>::type;

#endif // __ADD_AS_HPP__
