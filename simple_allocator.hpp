#ifndef __SIMPLE_ALLOCATOR_HPP__
#define __SIMPLE_ALLOCATOR_HPP__

template <typename T>
struct simple_allocator {

  using value_type = T;

  simple_allocator() { cout << "ctor\n"; }

  template <typename U>
  simple_allocator(const simple_allocator<U> &other) {
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
bool operator==(const simple_allocator<T> &a, const simple_allocator<U> &b) {
  return true; // possibly wrong
}

template <typename T, typename U>
bool operator!=(const simple_allocator<T> &a, const simple_allocator<U> &b) {
  return !a==b;
}

#endif // __SIMPLE_ALLOCATOR_HPP__
