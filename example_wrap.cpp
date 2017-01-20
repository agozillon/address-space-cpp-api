#include <iostream>
#include "tag_wrap.hpp"

void grab(int x) {}
struct Foo {};
void jim(Foo o) {}

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

  Foo o;
  tag_wrap w3(o);
  jim(w3);

  std::cout << w << '\n';
  w=w+w;
  std::cout << w << '\n';
  double bob[2][3] = {1,2,3,4,5,6};
  std::cout << bob[1][2] << '\n';
  tag_wrap w4(bob);
  std::cout << w4[1][2] << '\n';
  
  return 0;
}

