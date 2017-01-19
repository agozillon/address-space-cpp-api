#ifndef __id_allocATOR_HPP__
#define __id_allocATOR_HPP__

template <typename T>
struct id_alloc {

  using value_type = typename T::type;

  id_alloc () { cout << "ctor\n"; }

  template <typename U> id_alloc(const id_alloc<U> &other) {
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
bool operator==(const id_alloc<T>&a, const id_alloc<U>&b) {
  return true; // possibly wrong
}

template <typename T, typename U>
bool operator!=(const id_alloc<T>&a, const id_alloc<U>&b) {
  return !a==b;
}

#endif // __id_allocATOR_HPP__
