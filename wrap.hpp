#ifndef __AS_WRAP_HPP__
#define __AS_WRAP_HPP__

template <typename T, typename I>
struct as_wrap {
  using type = T;
  static constexpr typename T::value_type value = I::value;
};

// static_assert

#endif // __AS_WRAP_HPP__
