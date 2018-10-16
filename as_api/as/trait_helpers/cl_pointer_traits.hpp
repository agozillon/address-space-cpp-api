#ifndef __CL_POINTER_TRAITS_HPP__
#define __CL_POINTER_TRAITS_HPP__


#include <__ocl_type_traits.h>
using namespace cl;


namespace impl {
// element_type related helpers
template <typename T>
struct ptr_first;

template <template<typename, typename...> class T, typename U, typename... Args>
struct ptr_first<T<U, Args...> > {
    using type = U;
};

template <typename T, typename = void_t<> >
struct ptr_element {
    using type = typename ptr_first<T>::type;
};

template <typename T>
struct ptr_element<T, void_t<typename T::element_type>> {
    using type = typename T::element_type;
};

// difference_type helpers
template <typename, typename = void_t<> >
struct ptr_difference {
    using type = ptrdiff_t;
};

template <typename T>
struct ptr_difference<T, void_t<typename T::difference_type>> {
    using type = typename T::difference_type;
};

// rebind helpers
template <typename T, typename V>
struct ptr_transform;

template <template<typename, typename...> class T, typename U, typename... Args, typename V>
struct ptr_transform<T<U, Args...>, V> {
    using type = T<V, Args...>;
};

template <typename T, typename U, typename = void_t<> >
struct ptr_rebind {
    using type = typename ptr_transform<T, U>::type;
};

template <typename T, typename U>
struct ptr_rebind<T, U, void_t<typename T::template rebind<U>> > {
    using type = typename T::template rebind<U>;
};

// pointer_to helper
template <typename T>
struct ptr_value {
    using type = T;
};

template <>
struct ptr_value<void> {
    using type = struct { };
};

} // impl

namespace cl_traits {

// pointer_traits implementation
template <typename T>
struct pointer_traits {
    using pointer = T;
    using element_type = typename impl::ptr_element<T>::type;
    using difference_type = typename impl::ptr_difference<T>::type;
    
    template<class U>
    using rebind = typename impl::ptr_rebind<T, U>::type;

    static pointer pointer_to(typename impl::ptr_value<element_type>::type& v) {
        return pointer::pointer_to(v);
    }
};

template<typename T>
struct pointer_traits<T*> {
    using pointer = T*;
    using element_type = T;
    using difference_type = ptrdiff_t;

    template<class U>
    using rebind = U*;

    static T* pointer_to(typename impl::ptr_value<T>::type& v) {
        return addressof(v);
    }
};

} // cl_traits

#endif // __CL_POINTER_TRAITS_HPP__
