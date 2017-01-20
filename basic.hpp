#ifndef __BASIC_HPP__
#define __BASIC_HPP__

using uint = unsigned;

template <unsigned ...Is>
using u_seq = std::integer_sequence<uint,Is...>;

#endif // __BASIC_HPP__
