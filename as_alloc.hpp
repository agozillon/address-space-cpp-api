#ifndef __AS_ALLOCATOR_HPP__
#define __AS_ALLOCATOR_HPP__

#include <iostream>

template <typename T>
struct as_alloc {

  using value_type = typename T::type;

  as_alloc() { std::cout << "ctor\n"; }

  template <typename U> as_alloc(const as_alloc<U> &other) {
    std::cout << "copy ctor\n";
  }

  value_type *allocate(std::size_t n) {
    std::cout << "allocate\n";
    return new value_type[n];
  }

  void deallocate(value_type *p, std::size_t n) {
    std::cout << "deallocate\n";
    delete [] p;
  }
};

template <typename T, typename U>
bool operator==(const as_alloc<T>&a, const as_alloc<U>&b) {
  return true; // possibly wrong
}

template <typename T, typename U>
bool operator!=(const as_alloc<T>&a, const as_alloc<U>&b) {
  return !a==b;
}

#endif // __AS_ALLOCATOR_HPP__
