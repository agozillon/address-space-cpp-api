#ifndef __WRAP_HPP__
#define __WRAP_HPP__

template <typename T, typename U = int>
struct tag_wrap {
  tag_wrap(T x, U y = 0) : x(x) {}
  operator T() { return x; }
  T x;
};

#endif // __WRAP_HPP__
