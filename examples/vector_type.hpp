#ifndef __VECTOR_TYPE_HPP__
#define __VECTOR_TYPE_HPP__

template <typename>
struct vector_size {
  static const int value = 0;
};

template <typename T, int N>
struct vector_size<__attribute__((ext_vector_type(N))) T> {
  static const int value = N;
};

using float1 = __attribute__((ext_vector_type(1))) float;
using float2 = __attribute__((ext_vector_type(2))) float;
using float3 = __attribute__((ext_vector_type(3))) float;
using float4 = __attribute__((ext_vector_type(4))) float;
using float5 = __attribute__((ext_vector_type(5))) float;
using float6 = __attribute__((ext_vector_type(6))) float;
using float2047 = __attribute__((ext_vector_type(2047))) float; // largest

template <typename T>
inline constexpr auto vector_size_v = vector_size<T>::value;

static_assert(vector_size_v<float>     == 0,"");
static_assert(vector_size_v<float1>    == 1,"");
static_assert(vector_size_v<float2>    == 2,"");
static_assert(vector_size_v<float3>    == 3,"");
static_assert(vector_size_v<float2047> == 2047,"");

#endif // __VECTOR_TYPE_HPP__
