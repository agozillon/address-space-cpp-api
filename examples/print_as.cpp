#include <iostream>
#include <memory>
#include <utility>
#include "add_pointee_const.hpp"
#include "add_pointee_as.hpp"
#include "get_as.hpp"

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

// See http://en.cppreference.com/w/cpp/language/implicit_conversion
template <typename T, unsigned Np = 0, unsigned Nv = 0>
struct as_val {

  as_val(   )        {}      // Allows as_val<int> x;
  as_val(T x) : x(x) {}      // Allows x = y;
  operator T() { return x; } // Allows *x;

  T x;
};
//template <typename T> as_val(T x) -> as_val<T,0,0>;

// C++17 template deduction for aggregates
template <typename T> as_ptr(T *p) -> as_ptr<T,0>;

template <typename>
  struct as_trait;

template <typename T, unsigned N>
struct as_trait<as_ptr<T,N>> {
  using type = T;
  static constexpr unsigned value = N;
};


// set, not add; certainly not like add_pointer; but even add_const...a user
// will not expect add_const<int const> to enable an "int const const".
// No, for a user of stock GCC, add_as implies a change; fair enough.
#if __has_attribute(ext_address_space)

template <typename T, unsigned Nv>
struct add_as {
  using type = T __attribute__((ext_address_space(Nv)));
};

template <typename T, unsigned Np>
struct add_pointee_as0 {
  using type =   __attribute__((ext_address_space(Np))) T;
};

#else

template <typename T, unsigned Nv>
struct add_as {
  using type = as_val<T,0,Nv>;
};

template <typename T, unsigned Np, unsigned Nv, unsigned Nv_>
struct add_as<as_val<T,Np,Nv>, Nv_> {
  using type = as_val<T,Np,Nv_>;
};

template <typename T, unsigned Np>
struct add_pointee_as0 {
  using type = as_val<T,Np,0>;
};

template <typename T, unsigned Np, unsigned Nv, unsigned Np_>
struct add_pointee_as0<as_val<T,Np,Nv>, Np_> {
  using type = as_val<T,Np_,Nv>;
};

#endif

template <typename T, unsigned Nv>
using add_as_t         = typename add_as<T,Nv>::type;
template <typename T, unsigned Np>
using add_pointee_as0_t = typename add_pointee_as0<T,Np>::type;


static_assert( std::is_same<const int,int const>::value,"");
static_assert(!std::is_same<const int *,int * const>::value,"");
static_assert( std::is_const<int * const>::value,"");
static_assert(!std::is_const<const int *>::value,"");

// This doesn't work?
template <typename T, unsigned N>
struct as_trait<T __attribute__((ext_address_space(N))) *> {
  using type = T;
  static constexpr unsigned value = N;
};

static_assert(std::is_standard_layout<as_ptr<int>>::value,"");
static_assert(std::is_pod<as_ptr<int>>::value,"");
static_assert(sizeof(std::shared_ptr<int>)==16);
static_assert(sizeof(std::shared_ptr<int[3]>)==16);
static_assert(sizeof(int*)==8);
static_assert(sizeof(int)==4);
static_assert(sizeof(int[3])==4*3);

template <typename T>
void print(T p) {
  std::cout << *p << ": address space " << as_trait<T>::value << '\n';
}

template <typename T>
struct a_const {
  using type =   const T;
};

template <typename T>
using a_const_t = typename a_const<T>::type;

int main(int argc, char *argv[])
{
  int i = 42;
  int *p = &i;
  static typename as_ptr<int,1>::element_type l;

  as_ptr p1{&i};
  int __attribute__((ext_address_space(1))) *p2 = &l;

  print(p1);
  //print(p2);
  std::cout << sizeof(std::shared_ptr<int>) << '\n';

  // a_const_t<int *> hh = &hh; // int * const
  //a_const_t<int> kk = &kk; // const int
  static_assert(std::is_same<const int, int const>::value,""); // This is true
  //static_assert(std::is_same<a_const_t<int *>,const int *>::value,"");

//  as_val<int,0,0> kk{i};
//  as_val<int> kk{i};
  /*static_assert(std::is_same<
                  add_pointee_as0_t<int *,42>,
                  __attribute__((ext_address_space(42))) int *
                >::value,"");
*/
  as_val kk0{i};
  as_val<int> kk;
  kk = i;
  as_val<int *,0,0> kk2{p};
  // add_as_t<int,42> k; // error: good
  kk.x = 8;
  *kk2.x = 8;
  std::cout << "*kk2: " << *kk2 << '\n';
  *kk2 = 9;
  std::cout << "*kk2: " << *kk2 << '\n';
  std::cout << &i << ' ' << &(kk.x) << '\n';
  int &ir = i;
  int &&irr = std::move(i);
  std::cout << &i << ' ' << &ir << '\n';
  std::cout << &i << ' ' << &irr << '\n';

  return 0;
}
