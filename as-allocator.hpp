#ifndef __AS_ALLOCATOR_HPP__
#define __AS_ALLOCATOR_HPP__

template <typename T>
struct as-alloc {

  using value_type = typename T::type;

  as-alloc () { cout << "ctor\n"; }

  template <typename U> as-alloc(const as-alloc<U> &other) {
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
bool operator==(const as-alloc<T>&a, const as-alloc<U>&b) {
  return true; // possibly wrong
}

template <typename T, typename U>
bool operator!=(const as-alloc<T>&a, const as-alloc<U>&b) {
  return !a==b;
}

#endif // __AS_ALLOCATOR_HPP__
