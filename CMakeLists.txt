cmake_minimum_required(VERSION 3.10)
project(cx_util_lib VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include the directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add source files
add_library(cx_util STATIC
   src/temp.cpp)

# Specify where the installed libraries should go
install(TARGETS cx_util
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   RUNTIME DESTINATION bin)

# Install the header files
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)

# Export the package to let other projects find and use the library
export(PACKAGE cx_util_lib)

include(CMakePackageConfigHelpers)

# Set up a configuration file so other projects can use it using `find_package()`
configure_package_config_file(
   ${CMAKE_CURRENT_SOURCE_DIR}/cx_utilConfig.cmake.in
   ${CMAKE_CURRENT_BINARY_DIR}/cx_utilConfig.cmake
   INSTALL_DESTINATION lib/cmake/cx_util)

# Specify the version to check compatibility
write_basic_package_version_file(
   ${CMAKE_CURRENT_BINARY_DIR}/cx_utilConfigVersion.cmake
   VERSION ${PROJECT_VERSION}
   COMPATIBILITY SameMajorVersion)

# Install the config files to provide information about the library
install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/cx_utilConfig.cmake
   ${CMAKE_CURRENT_BINARY_DIR}/cx_utilConfigVersion.cmake
   DESTINATION lib/cmake/cx_util)
