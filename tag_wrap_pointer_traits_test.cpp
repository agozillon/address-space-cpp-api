#include <iostream>
#include <type_traits>
#include <memory>

#include "tag_wrap.hpp"

template <typename P1, typename P2>
void test_pointer_traits()
{
  using std::is_same;
  using std::pointer_traits;

  static_assert(is_same<
                  typename pointer_traits<P1>::pointer,
                  P1
                >::value,"");
  static_assert(is_same<
                  typename pointer_traits<P1>::element_type,
                  int
                >::value,"");
  static_assert(is_same<
                  typename pointer_traits<P1>::difference_type,
                  std::ptrdiff_t
                >::value,"");
  static_assert(is_same<
                  typename pointer_traits<P1>::template rebind<char>,
                  P2
                >::value,"");

  /*
  using etype = typename std::pointer_traits<P1>::element_type;
  etype x = 0;
  *(std::pointer_traits<P1>::pointer_to(x)) = 1;

  static_assert(is_same<
                  decltype(pointer_traits<P1>::pointer_to(x)),
                  decltype(std::addressof(x))
                >::value,"");
  return x;

    Unlike the Boost library version, calling pointer_to results in a compile
    error when P1::pointer_to doesn't exist. e.g. shared_ptr<int>::pointer_to
  */

}

int main(int argc, char *argv[])
{
  test_pointer_traits<int*,char*>();
  test_pointer_traits<std::shared_ptr<int>,std::shared_ptr<char>>();
  test_pointer_traits<tag_wrap<int*>,tag_wrap<char*>>();
  return 0;
}

