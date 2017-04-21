#ifndef __BASIC_HPP__
#define __BASIC_HPP__

#include <utility>

using uint = unsigned;

template <uint ...Is>
using u_seq = std::integer_sequence<uint,Is...>;

template <typename T>
struct id {
  using type = T;
};

#endif // __BASIC_HPP__
