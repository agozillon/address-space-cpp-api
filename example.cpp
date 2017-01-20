#include <iostream>
#include <vector>

#include "id.hpp"
#include "as_wrap.hpp"
#include "simple_alloc.hpp"
#include "id_alloc.hpp"
#include "as_alloc.hpp"

auto print(const auto &v) {
  for (auto i : v) { std::cout << i << ' '; }
  std::cout << '\n';
}

auto print(const auto &v, const auto &...vs) {
  for (auto i : v) { std::cout << i << ' '; }
  std::cout << '\n';
  print(vs...);
}

int main(int argc, char *argv[])
{
  std::vector<int> v1 = {3,2,1};
  std::vector<int> v2{3,2,1};
  std::vector<int> v3(3,2); // n.b. Three 2s

  print(v1,v2,v3);

  {
    std::vector<int,simple_alloc<int>> v4{3,2,1};
    print(v1,v2,v3);
  }
  std::cout << '\n';
  {
    std::vector<int,id_alloc<id<int>>> v5{3,2,1};
    print(v1,v2,v3);
  }
  return 0;
}
