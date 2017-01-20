#ifndef __ID_ALLOCATOR_HPP__
#define __ID_ALLOCATOR_HPP__

#include <iostream>

template <typename T>
struct id_alloc {
  
  using value_type = T;//typename T::type;

  id_alloc () { std::cout << "ctor\n"; }

  template <typename U> id_alloc(const id_alloc<U> &other) {
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
bool operator==(const id_alloc<T>&a, const id_alloc<U>&b) {
  return true; // possibly wrong
}

template <typename T, typename U>
bool operator!=(const id_alloc<T>&a, const id_alloc<U>&b) {
  return !a==b;
}

#endif // __ID_ALLOCATOR_HPP__
