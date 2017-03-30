#ifndef __TAG_WRAP_HPP__
#define __TAG_WRAP_HPP__

#include <memory>

template <typename T, typename U = int>
struct tag_wrap {
  tag_wrap(T x, U = 0) : x(x) {}
  operator T() { return x; }
  T x;
};

static_assert(!std::is_pod<tag_wrap<int>>::value);
static_assert( std::is_standard_layout<tag_wrap<int>>::value);

// C++17 aggregate deduction guide. tag_wrap isn't POD due to the ctor.
// Not yet support in Clang (March 29th 2017)
template <typename T> tag_wrap(T x) -> tag_wrap<T,int>;

// #define __clang_version__ "5.0.0 (trunk 292878) (llvm/trunk 292881)"

template <typename T, unsigned N>
struct tag_wrap<T*,u_seq<N>> {
  tag_wrap(T *p, u_seq<N> = {}) : p(p) {}
#if __has_attribute(ext_address_space)
  operator T __attribute__((ext_address_space(N))) *() { return p; }
           T __attribute__((ext_address_space(N))) *p;
#else
  operator T *() { return p; }
           T *p;
#endif
};

// std::pointer_traits specialisation for tag_wrap
namespace std {
  template <typename T, typename U>
  struct pointer_traits<tag_wrap<T,U>> {
    struct impl {
      using pointer         = typename pointer_traits<T>::pointer;
      using element_type    = typename pointer_traits<T>::element_type;
      using difference_type = typename pointer_traits<T>::difference_type;
      template <typename T2>
      using rebind = typename pointer_traits<T>::template rebind<T2>;
    };
    using pointer         = tag_wrap<typename impl::pointer,U>;
    using element_type    =          typename impl::element_type;
    using difference_type =          typename impl::difference_type;
    template <typename T2>
    using rebind = tag_wrap<typename impl::template rebind<T2>,U>;
  };
};

// A cooler name for tag_wrap.
// This doesn't seem to work with class template deduction; e.g. as_ptr w(9);
// template <typename T, typename U = int>
// using as_ptr = tag_wrap<T,U>;
// Note that as_ptr w{9} should work (with tag_wrap too). (*Aggregate* init.)

#endif // __TAG_WRAP_HPP__
