#ifndef __AS_HPP__
#define __AS_HPP__

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
