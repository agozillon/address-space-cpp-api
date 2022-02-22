#include <iostream>
#include "as/as.hpp"

int main(int argc, char *argv[])
{
  static as_api::add_as_t<int,42> i42 = 12345;
  std::cout << "i42 is in address space " << as_api::get_as_v<decltype(i42)>;
  std::cout << " with a value of " << i42 << ".\n";
 
  return 0;
}
