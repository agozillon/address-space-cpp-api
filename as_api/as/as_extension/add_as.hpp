#ifndef __ADD_AS_HPP__
#define __ADD_AS_HPP__

template <typename T, unsigned Nv>
struct add_as {
  using type = T __attribute__((address_space(Nv)));
};

template <typename T, unsigned Nv>
using add_as_t = typename add_as<T,Nv>::type;

#endif // __ADD_AS_HPP__
