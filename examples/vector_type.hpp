#ifndef __VECTOR_TYPE_HPP__
#define __VECTOR_TYPE_HPP__

template <typename>
struct vector_components {
  static const int value = 0;
};

template <typename T, int N>
struct vector_components<__attribute__((ext_vector_type(N))) T> {
  static const int value = N;
  using type = T;
};

using float1    = __attribute__((ext_vector_type(1))) float;
using float2    = __attribute__((ext_vector_type(2))) float;
using float3    = __attribute__((ext_vector_type(3))) float;
using double3   = __attribute__((ext_vector_type(3))) double;
using float4    = __attribute__((ext_vector_type(4))) float;
using float5    = __attribute__((ext_vector_type(5))) float;
using float6    = __attribute__((ext_vector_type(6))) float;
using float2047 = __attribute__((ext_vector_type(2047))) float; // largest

template <typename T>
/*inline*/
constexpr auto vector_size_v = vector_components<std::remove_cv_t<T>>::value;

template <typename T>
using vector_type_t = typename vector_components<std::remove_cv_t<T>>::type;

static_assert(vector_size_v<float>     == 0,"");
static_assert(vector_size_v<float1>    == 1,"");
static_assert(vector_size_v<float2>    == 2,"");
static_assert(vector_size_v<float3>    == 3,"");
static_assert(std::is_same<vector_type_t<float3>,float>::value,"");
static_assert(std::is_same<vector_type_t<const float3>,float>::value,"");
static_assert(vector_size_v<double3>   == 3,"");
static_assert(std::is_same<
                vector_type_t<const volatile double3>,
                double
              >::value,"");
static_assert(vector_size_v<float2047> == 2047,"");

#endif // __VECTOR_TYPE_HPP__
