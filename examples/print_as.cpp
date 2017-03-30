#include <iostream>
#include <utility>

template <typename T, unsigned N = 0>
struct as_ptr {
#if __has_attribute(ext_address_space)
  using element_type = T __attribute__((ext_address_space(N)));
  operator T __attribute__((ext_address_space(N))) *() { return p; }
           T __attribute__((ext_address_space(N))) *p;
#else
  using element_type = T;
  operator T *() { return p; }
           T *p;
#endif
};

// C++17 template deduction for aggregates
template <typename T> as_ptr(T *p) -> as_ptr<T,0>;

template <typename>
  struct as_trait;

template <typename T, unsigned N>
struct as_trait<as_ptr<T,N>> {
  using type = T;
  static constexpr unsigned value = N;
};

// This doesn't work?
template <typename T, unsigned N>
struct as_trait<T __attribute__((ext_address_space(N))) *> {
  using type = T;
  static constexpr unsigned value = N;
};

static_assert(std::is_standard_layout<as_ptr<int>>::value,"");
static_assert(std::is_pod<as_ptr<int>>::value,"");

template <typename T>
void print(T p) {
  std::cout << *p << ": address space " << as_trait<T>::value << '\n';
}

int main(int argc, char *argv[])
{
  int i = 42;
  static typename as_ptr<int,1>::element_type l;

  as_ptr p1{&i};
  int __attribute__((ext_address_space(1))) *p2 = &l;

  print(p1);
  //print(p2);

  return 0;
}
