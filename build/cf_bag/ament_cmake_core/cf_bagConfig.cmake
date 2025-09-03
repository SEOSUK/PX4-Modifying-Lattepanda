# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_cf_bag_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED cf_bag_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(cf_bag_FOUND FALSE)
  elseif(NOT cf_bag_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(cf_bag_FOUND FALSE)
  endif()
  return()
endif()
set(_cf_bag_CONFIG_INCLUDED TRUE)

# output package information
if(NOT cf_bag_FIND_QUIETLY)
  message(STATUS "Found cf_bag: 0.0.0 (${cf_bag_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'cf_bag' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${cf_bag_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(cf_bag_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${cf_bag_DIR}/${_extra}")
endforeach()
