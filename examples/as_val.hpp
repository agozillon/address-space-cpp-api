#ifndef __AS_VAL_HPP__
#define __AS_VAL_HPP__

// See http://en.cppreference.com/w/cpp/language/implicit_conversion
template <typename T, unsigned Np = 0, unsigned Nv = 0>
struct as_val {

  as_val(   )        {}      // Allows as_val<int> x;
  as_val(T x) : x(x) {}      // Allows x = y;
  operator T() { return x; } // Allows *x;

  T x;
};
//template <typename T> as_val(T x) -> as_val<T,0,0>;

#endif // __AS_VAL_HPP__
