#ifndef __SIMPLE_ALLOCATOR_HPP__
#define __SIMPLE_ALLOCATOR_HPP__

template <typename T>
struct SimpleAllocator {

  using value_type = T;

  SimpleAllocator() { cout << "ctor\n"; }

  template <typename U>
  SimpleAllocator(const SimpleAllocator<U> &other) {
    cout << "copy ctor\n";
  }

  value_type *allocate(std::size_t n) {
    cout << "allocate\n";
    return new value_type[n];
  }

  void deallocate(value_type *p, std::size_t n) {
    cout << "deallocate\n";
    delete [] p;
  }
};

template <typename T, typename U>
bool operator==(const SimpleAllocator<T> &a, const SimpleAllocator<U> &b) {
  return true; // possibly wrong
}

template <typename T, typename U>
bool operator!=(const SimpleAllocator<T> &a, const SimpleAllocator<U> &b) {
  return !a==b;
}

#endif // __SIMPLE_ALLOCATOR_HPP__
