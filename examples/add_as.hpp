#ifndef __ADD_AS_HPP__
#define __ADD_AS_HPP__

#include "as_val.hpp"

// set, not add; certainly not like add_pointer; but even add_const...a user
// will not expect add_const<int const> to enable an "int const const".
// No, for a user of stock GCC, add_as implies a change; fair enough.

#if __has_attribute(ext_address_space)

template <typename T, unsigned Nv>
struct add_as {
  using type = T __attribute__((ext_address_space(Nv)));
};

#else

template <typename T, unsigned Nv>
struct add_as {
  using type = as_val<T,0,Nv>;
};

template <typename T, unsigned Np, unsigned Nv, unsigned Nv_>
struct add_as<as_val<T,Np,Nv>, Nv_> {
  using type = as_val<T,Np,Nv_>;
};

#endif

template <typename T, unsigned Nv>
using add_as_t = typename add_as<T,Nv>::type;

#endif // __ADD_AS_HPP__
