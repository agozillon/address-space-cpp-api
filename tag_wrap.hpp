#ifndef __WRAP_HPP__
#define __WRAP_HPP__

#include "basic.hpp"

template <typename T, typename U = void>
struct tag_wrap {
  tag_wrap(T x) : x(x) {}
  operator T() { return x; }
  T x;
};

#endif // __WRAP_HPP__
