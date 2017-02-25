#ifndef __WRAP_HPP__
#define __WRAP_HPP__

#include <type_traits>
#include <memory>

template <typename T, typename U = int>
struct tag_wrap {
  tag_wrap(T x, U y = 0) : x(x) {}
  operator T() { return x; }
  T x;
};

namespace static_asserts {

using std::is_same;
using std::pointer_traits;

using et1 = int;
using t1 = et1*;
et1 v1;
static_assert(is_same<pointer_traits<t1>::pointer,     int*>::value,"");
static_assert(is_same<pointer_traits<t1>::element_type,int >::value,"");
static_assert(is_same<
                pointer_traits<t1>::difference_type,
                std::ptrdiff_t
              >::value,"");
static_assert(is_same<pointer_traits<t1>::rebind<char>,char*>::value,"");
static_assert(is_same<
                decltype(pointer_traits<t1>::pointer_to(v1)),
                decltype(std::addressof(v1))
              >::value,"");

} // namespace static_asserts

#endif // __WRAP_HPP__
