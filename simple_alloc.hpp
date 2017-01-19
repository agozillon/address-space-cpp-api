#ifndef __SIMPLE_ALLOCATOR_HPP__
#define __SIMPLE_ALLOCATOR_HPP__

#include <iostream>

template <typename T>
struct simple_alloc {

  using value_type = T;

  simple_alloc() { std::cout << "ctor\n"; }

  template <typename U>
  simple_alloc(const simple_alloc<U> &other) {
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
bool operator==(const simple_alloc<T> &a, const simple_alloc<U> &b) {
  return true; // possibly wrong
}

template <typename T, typename U>
bool operator!=(const simple_alloc<T> &a, const simple_alloc<U> &b) {
  return !a==b;
}

#endif // __SIMPLE_ALLOCATOR_HPP__
