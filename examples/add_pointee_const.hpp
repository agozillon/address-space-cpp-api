#ifndef __ADD_POINTEE_CONST_HPP__
#define __ADD_POINTEE_CONST_HPP__

namespace impl {

template <typename T>
struct add_pointee_const {
  using e_type = typename std::pointer_traits<T>::element_type;
  using   type = typename std::pointer_traits<T>::template rebind<const e_type>;
};

template <typename T>
using add_pointee_const_t = typename add_pointee_const<T>::type;

} // namespace impl

// Handles fancy pointers  -   like std::pointer_traits.
// Handles const arguments - unlike std::pointer_traits!
template <typename T>
struct add_pointee_const {
  using type = impl::add_pointee_const_t<T>;
};

template <typename T>
struct add_pointee_const<T const> {
  using type = impl::add_pointee_const_t<T> const;
};

template <typename T>
struct add_pointee_const<T volatile> {
  using type = impl::add_pointee_const_t<T> volatile;
};

template <typename T>
struct add_pointee_const<T const volatile> {
  using type = impl::add_pointee_const_t<T> const volatile;
};

template <typename T>
using add_pointee_const_t = typename add_pointee_const<T>::type;

/* -------------------------------------------------------------------------- */

static_assert(std::is_same<add_pointee_const_t<int  *>, int   const *>::value);
static_assert(std::is_same<add_pointee_const_t<int **>, int * const *>::value);
static_assert(std::is_same<
                add_pointee_const_t<std::shared_ptr<int>>,
                std::shared_ptr<const int>
              >::value,"");
static_assert(std::is_same<
                add_pointee_const_t<std::shared_ptr<int *>>,
                std::shared_ptr<int * const>
              >::value,"");

#endif // __ADD_POINTEE_CONST_HPP__
