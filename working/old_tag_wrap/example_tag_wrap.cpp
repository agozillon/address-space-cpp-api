#include <iostream>
#include "basic.hpp"
#include "tag_wrap.hpp"

void grab(int x) {}
void grabp(int *p) { std::cout << p << ' '; }
template <typename T>
void grabpT(T *p) { std::cout << p << ' '; }
struct Foo {};
void jim(Foo o) {}

static_assert(__cplusplus > 201402L,""); // C++17 class template deductions
// For now only GCC has this (Feb 2017); Clang may have it on tip

int main(int argc, char *argv[])
{
  int i = 123;
  tag_wrap w(9);
  grab(w);
  std::cout << w << '\n';
  tag_wrap w2(9.3);
  std::cout << w2 << '\n';
  tag_wrap p(&i);
  std::cout << *p << '\n';
  std::cout << &i << ' ';
  grabp(&i);
  grabp(p);
  std::cout << '\n';
  grabpT(&i);
  // grabpT(p); // error
  std::cout << '\n';

  Foo o;
  tag_wrap w3(o);
  jim(w3);

  std::cout << w << '\n';
  w=w+w;
  std::cout << w << '\n';
  double bob[2][3] = {0,1,2,3,4,5};
  std::cout << bob[1][2] << '\n';
  tag_wrap w4(bob);
  std::cout << w4[1][2] << '\n';

  tag_wrap w5(bob,u_seq<3,4>{});
  std::cout << w5[1][2] << '\n';
  
  return 0;
}

