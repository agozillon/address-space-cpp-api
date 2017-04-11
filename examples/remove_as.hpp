#ifndef __REMOVE_AS_HPP__
#define __REMOVE_AS_HPP__

template <typename T>
struct remove_as {
  using type = T;
};

template <typename T>
struct remove_as<T const> {
  using type = T;
};

template <typename T>
struct remove_as<T volatile> {
  using type = T;
};

template <typename T>
struct remove_as<T const volatile> {
  using type = T;
};

template <typename T>
using remove_as_t = typename remove_as<T>::type;

/* -------------------------------------------------------------------------- */

namespace remove_as_hpp_tests {

#define AS 42
#define ASN __attribute__((ext_address_space(AS)))
static_assert(std::is_same<remove_as_t<int>,int>::value);
//static_assert(std::is_same<remove_as_t<int ASN>,int ASN>::value); // wrong

} // namespace remove_as_hpp_tests

#endif // __REMOVE_AS_HPP__
