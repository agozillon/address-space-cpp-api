#ifndef __AS_TESTS_HPP__
#define __AS_TESTS_HPP__

#include <type_traits>
using namespace std;

#include "as/as.hpp"
using namespace as_api;

#define AS 42
#define ASN __attribute__((address_space(AS)))

namespace add_as_tests_hpp {
  using t1 = add_as_t<int  *,AS>;
  using t2 = add_as_t<int **,AS>;
  using t3    = add_as_t<int * volatile,AS>;
  using t4    = add_as_t<int ** volatile,AS>;

  static_assert(is_same<t1, int * ASN>::value,"");
  static_assert(is_same<t2, int ** ASN>::value,"");
  static_assert(is_same<t3, int * ASN volatile>::value,"");
  static_assert(is_same<t4, int ** ASN volatile>::value,"");
} // namespace add_as_tests_hpp

namespace get_as_tests_hpp {
  using t1 = float;
  using t2 = float *;
  using t3 = const volatile float;
  using t4 = const volatile float *;
  using t5 = float * const volatile;
  using t6 = const float;
  using t7 = volatile float;
  
  static_assert(0  == get_as_v<add_as_t<t1, 0>>,"");
  static_assert(0  == get_as_v<t1>,"");
  static_assert(1  == get_as_v<add_as_t<t1, 1>>,"");
  static_assert(1  == get_as_v<__attribute__((address_space(1))) t1>,"");
  static_assert(42 == get_as_v<add_as_t<t1, 42>>,"");
  static_assert(42 == get_as_v<ASN t1>,"");

  static_assert(0  == get_as_v<add_as_t<t2, 0>>,"");
  static_assert(0  == get_as_v<t2>,"");
  static_assert(1  == get_as_v<add_as_t<t2, 1>>,"");
  static_assert(1  == get_as_v<t2 __attribute__((address_space(1)))>,"");
  static_assert(0  == get_as_v<__attribute__((address_space(1))) float *>,"");
  static_assert(42 == get_as_v<add_as_t<t2, 42>>,"");
  static_assert(0 == get_as_v<ASN float *>,"");
  static_assert(42 == get_as_v<t2 ASN>,"");

  static_assert(0  == get_as_v<add_as_t<t3, 0>>,"");
  static_assert(0  == get_as_v<t3>,"");
  static_assert(1  == get_as_v<add_as_t<t3, 1>>,"");
  static_assert(1  == get_as_v<t3 __attribute__((address_space(1)))>,"");
  static_assert(0  == get_as_v<__attribute__((address_space(1))) const float *>,"");
  static_assert(42 == get_as_v<add_as_t<t3, 42>>,"");
  static_assert(0 == get_as_v<ASN volatile float *>,"");
  static_assert(42 == get_as_v<t3 ASN>,"");
  
  static_assert(0  == get_as_v<add_as_t<t4, 0>>,"");
  static_assert(0  == get_as_v<t4>,"");
  static_assert(1  == get_as_v<add_as_t<t4, 1>>,"");
  static_assert(1  == get_as_v<t4 __attribute__((address_space(1)))>,"");
  static_assert(42 == get_as_v<add_as_t<t4, 42>>,"");
  static_assert(42 == get_as_v<t4 ASN>,"");
  
  static_assert(0  == get_as_v<add_as_t<t5, 0>>,"");
  static_assert(0  == get_as_v<t5>,"");
  static_assert(1  == get_as_v<add_as_t<t5, 1>>,"");
  static_assert(1  == get_as_v<t5 __attribute__((address_space(1)))>,"");
  static_assert(42 == get_as_v<add_as_t<t5, 42>>,"");
  static_assert(42 == get_as_v<t5 ASN>,"");
  
  static_assert(0  == get_as_v<add_as_t<t6, 0>>,"");
  static_assert(0  == get_as_v<t6>,"");
  static_assert(1  == get_as_v<add_as_t<t6, 1>>,"");
  static_assert(1  == get_as_v<t6 __attribute__((address_space(1)))>,"");
  static_assert(42 == get_as_v<add_as_t<t6, 42>>,"");
  static_assert(42 == get_as_v<t6 ASN>,"");
  
  static_assert(0  == get_as_v<add_as_t<t7, 0>>,"");
  static_assert(0  == get_as_v<t7>,"");
  static_assert(1  == get_as_v<add_as_t<t7, 1>>,"");
  static_assert(1  == get_as_v<t7 __attribute__((address_space(1)))>,"");
  static_assert(42 == get_as_v<add_as_t<t7, 42>>,"");
  static_assert(42 == get_as_v<t7 ASN>,"");
} // namespace get_as_tests_hpp

namespace remove_as_tests_hpp {
  // the ones without pointers are technically "illegal" types when 
  // instantiated/used with an actual variable in most languages, but the type 
  // system allows them.
  using t1 = int const volatile ASN;
  using t2 = int volatile ASN;
  using t3 = int const ASN;
  using t4 = int ASN;
  using t5 = int * const volatile ASN;
  using t6 = int * const ASN;
  using t7 = int * volatile ASN;
  using t8 = int * ASN;
  using t9 = int ** const volatile ASN;
  using t10 = int ** const ASN;
  using t11 = int ** volatile ASN;
  using t12 = int ** ASN;
  using t13 = int * const volatile ASN *;
  using t14 = int * const ASN *;
  using t15 = int * volatile ASN *;
  using t16 = int * ASN *;
  using t17 = int const ASN;

  static_assert(is_same<remove_as_t<t1>, int const volatile>::value, "");
  static_assert(is_same<remove_as_t<t2>, int volatile>::value,"");
  static_assert(is_same<remove_as_t<t3>, int const>::value,"");
  static_assert(is_same<remove_const_t<remove_as_t<t3>>, int>::value,"");
  static_assert(is_same<remove_as_t<t4>, int>::value,"");
  static_assert(is_same<remove_as_t<t5>, int * const volatile>::value,"");
  static_assert(is_same<remove_as_t<t6>, int * const>::value,"");
  static_assert(is_same<remove_as_t<t7>, int * volatile>::value,"");
  static_assert(is_same<remove_as_t<t8>,int *>::value,"");
  static_assert(is_same<remove_as_t<t9>, int ** const volatile>::value,"");
  static_assert(is_same<remove_as_t<t10>, int ** const>::value,"");
  static_assert(is_same<remove_as_t<t11>, int ** volatile>::value,"");
  static_assert(is_same<remove_as_t<t12>, int **>::value,"");
  static_assert(is_same<remove_as_t<t13>, t13>::value, "");
  static_assert(is_same<remove_as_t<t14>, t14>::value, "");
  static_assert(is_same<remove_as_t<t15>, t15>::value, "");
  static_assert(is_same<remove_as_t<t16>, t16>::value, "");
  static_assert(is_same<remove_as_t<t17>, int const>::value, "");
} // namespace remove_as_tests_hpp

namespace add_pointee_as_tests_hpp {
  using t1 = add_pointee_as_t<int  *,AS>;
  using t2 = add_pointee_as_t<int **,AS>;
  using t3    = add_pointee_as_t<int       * volatile,AS>;
  using t4    = add_pointee_as_t<int *     * volatile,AS>;
  using t5    = add_pointee_as_t<int *     * const volatile,AS>;
  using t6    = add_pointee_as_t<int *     * const volatile ASN,AS>;
  using t7    = add_pointee_as_t<int *  const volatile * const volatile ASN ,AS>;
  using t8    = add_pointee_as_t<int * const volatile *  const volatile  * const volatile ASN,AS>;

  static_assert(is_same<t1, int   ASN *>::value,"");
  static_assert(is_same<t2, int * ASN *>::value,"");
  static_assert(is_same<t3, int   ASN * volatile>::value,"");
  static_assert(is_same<t4, int * ASN * volatile>::value,"");
  static_assert(is_same<t5, int * ASN * const volatile>::value,"");
  static_assert(is_same<t6, int * ASN * const volatile ASN>::value,"");
  static_assert(is_same<t7, int * const volatile ASN * const volatile ASN>::value,"");
  static_assert(is_same<t8, int * const volatile *  ASN const volatile  * const volatile ASN>::value,"");

} // namespace add_pointee_as_tests_hpp

namespace get_pointee_as_tests_hpp {
  // do tests with const volatile on all layers, these are buggy in mainline but 
  // I have a patch for it (it is imperfect but there is an LLVM phabricator 
  // review up about it)
  using t1 = float**;
  using t2 = double**;
  using t3 = int**;
  using t4 = float*;
  using t5 = float * ASN *;
  using t6 = float * ASN * const volatile;
  using t7 = float * ASN * const volatile ASN;
  using t8 = float * ASN const volatile *;
  using t9 = float * const volatile * const volatile;
  using t10 = float * const volatile * ASN;
  using t11 = float ** const volatile * ASN;
  using t12 = float ** const volatile ASN * const volatile ASN;
    
  static_assert(0  == get_pointee_as_v<t1>, "");
  static_assert(7  == get_pointee_as_v<add_pointee_as_t<t2, 7>>, "");
  static_assert(42 == get_pointee_as_v<add_pointee_as_t<t3, 42>>, "");
  static_assert(0 == get_pointee_as_v<add_pointee_as_t<t4, 42>*>, "");
  static_assert(42 == get_pointee_as_v<t5>, "");
  static_assert(42 == get_pointee_as_v<t6>, "");
  static_assert(42 == get_pointee_as_v<t7>, "");
  static_assert(42 == get_pointee_as_v<t8>, "");
  static_assert(0 == get_pointee_as_v<t9>, "");
  static_assert(0 == get_pointee_as_v<t10>, "");
  static_assert(0 == get_pointee_as_v<t11>, "");
  static_assert(42 == get_pointee_as_v<t12>, "");
  
} // namespace get_pointee_as_tests_hpp

namespace remove_pointee_as_tests_hpp {
  using t1 = add_pointee_as_t<int  *, AS>;
  using t2 = add_pointee_as_t<int **, AS>;
  using t3 = add_pointee_as_t<int * volatile, AS>;
  using t4 = add_pointee_as_t<int ** volatile,AS>;
  using t5 = int ASN * ASN *; 
  using t6 = add_pointee_as_t<int const volatile *, AS>;
  using t7 = add_pointee_as_t<int const volatile * const volatile *, AS>;
  using t8 = ASN float * ASN;
  using t9 = float  * ASN  * const volatile;
  using t10 = float  * ASN  * ASN const volatile;
  using t11 = float  * ASN const volatile * ASN const volatile;
  using t12 = float * ASN * ASN const volatile * ASN const volatile;
  
  static_assert(is_same<remove_pointee_as_t<t1>, int *>::value, "");
  static_assert(is_same<remove_pointee_as_t<t2>, int **>::value, "");
  static_assert(is_same<remove_pointee_as_t<t3>, int * volatile>::value, "");
  static_assert(is_same<remove_pointee_as_t<t4>, int ** volatile>::value, "");
  static_assert(is_same<remove_pointee_as_t<t5>, int ASN * *>::value, "");
  static_assert(is_same<remove_pointee_as_t<t6>, int const volatile *>::value, "");
  static_assert(is_same<remove_pointee_as_t<t7>, int const volatile * const volatile *
                >::value, "");
  static_assert(is_same<remove_pointee_as_t<t8>, float * ASN>::value, "");
  static_assert(is_same<remove_pointee_as_t<t9>, float  ** const volatile>::value, "");
  static_assert(is_same<remove_pointee_as_t<t10>, float  ** ASN const volatile>::value, "");
  static_assert(is_same<remove_pointee_as_t<t11>, float  * const volatile * ASN const volatile>::value, "");
  static_assert(is_same<remove_pointee_as_t<t12>, float  * ASN * const volatile * ASN const volatile>::value, "");

} // namespace remove_pointee_as_tests_hpp

#endif // __AS_TESTS_HPP__

