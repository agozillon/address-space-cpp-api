#ifndef __AS_HPP__
#define __AS_HPP__

// this does not like being included within a namespace, so we must pre-incldue 
// it for all headers, this stops re-definition of the problem functions within
// the headers that actually use them (but still allows these files to include
// it on their own and subsequently be used seperately from this header with 
// little issue).
#include <memory> // std::pointer_traits

// Wrapping everything in this namespace mainly to stop conflicts with the libclcxx 
// remove_as function and other functions that could use similar names!
namespace as_api { 
#if __has_attribute(address_space)
#include "as_extension/add_as.hpp"
#include "as_extension/remove_as.hpp"
#include "as_extension/get_as.hpp"
#include "as_extension/add_pointee_as.hpp"
#include "as_extension/remove_pointee_as.hpp"
#include "as_extension/get_pointee_as.hpp"
#else
#include "as_val/as_val.hpp"
#include "as_val/add_as.hpp"
#include "as_val/remove_as.hpp"
#include "as_val/get_as.hpp"
#include "as_val/add_pointee_as.hpp"
#include "as_val/remove_pointee_as.hpp"
#include "as_val/get_pointee_as.hpp"
#endif
}
#endif // __AS_HPP__
