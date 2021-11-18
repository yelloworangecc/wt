#
# Global setup.
#

cmake_minimum_required(VERSION 2.8.12.1)

# Only generate Debug and Release configuration types.
set(CMAKE_CONFIGURATION_TYPES Debug Release)

# Project name.
project(wt)

# Use folders in the resulting project files.
set_property(GLOBAL PROPERTY OS_FOLDERS ON)


#
# CEF_ROOT setup.
# This variable must be set to locate the binary distribution.
#

# Example 1: The current directory contains both the complete binary
#            distribution and your project.
# A. Comment in these lines:
#
set(WT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(WT_TOOL "${CMAKE_CURRENT_SOURCE_DIR}/3rdtool")
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CEF_ROOT}/cmake")

# Example 2: The binary distribution is in a separate directory from your
#            project. Locate the binary distribution using the CEF_ROOT CMake
#            variable.
# A. Create a directory structure for your project like the following:
#    myproject/
#      CMakeLists.txt    <= top-level CMake configuration
#      mytarget/
#        CMakeLists.txt  <= CMake configuration for `mytarget`
#        ... other `mytarget` source files
# B. Copy this file to "myproject/CMakeLists.txt" as the top-level CMake
#    configuration.
# C. Create the target-specific "myproject/mytarget/CMakeLists.txt" file for
#    your application. See the included cefclient and cefsimple CMakeLists.txt
#    files as an example.
# D. Comment in these lines:
#
# set(CEF_ROOT "c:/path/to/cef_binary_3.2704.xxxx.gyyyyyyy_windows32")
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CEF_ROOT}/cmake")

# Example 3: The binary distribution is in a separate directory from your
#            project. Locate the binary distribution using the CEF_ROOT
#            environment variable.
# A. Create a directory structure for your project like the following:
#    myproject/
#      CMakeLists.txt    <= top-level CMake configuration
#      cmake/
#        FindCEF.cmake   <= CEF CMake configuration entry point
#      mytarget/
#        CMakeLists.txt  <= CMake configuration for `mytarget`
#        ... other `mytarget` source files
# B. Copy this file to "myproject/CMakeLists.txt" as the top-level CMake
#    configuration.
# C. Copy the cmake/FindCEF.cmake file to "myproject/cmake/FindCEF.cmake".
# D. Create the target-specific "myproject/mytarget/CMakeLists.txt" file for
#    your application. See the included cefclient and cefsimple CMakeLists.txt
#    files as an example.
# E. Set the CEF_ROOT environment variable before executing CMake. For example:
#    > set CEF_ROOT=c:\path\to\cef_binary_3.2704.xxxx.gyyyyyyy_windows32
# F. Comment in these lines:
#
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


#
# Load the CEF configuration.
#

# Execute FindCEF.cmake which must exist in CMAKE_MODULE_PATH.
# find_package(CEF REQUIRED)


#
# Define CEF-based targets.
#

# Include the libcef_dll_wrapper target.
# Comes from the libcef_dll/CMakeLists.txt file in the binary distribution
# directory.
add_subdirectory(${WT_ROOT}/wtbrowser wtbrowser)
add_subdirectory(${WT_ROOT}/wtcli wtcli)

# Include application targets.
# Comes from the <target>/CMakeLists.txt file in the current directory.
# TODO: Change these lines to match your project target when you copy this file.
# if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests")
#   add_subdirectory(tests/cefsimple)
#   add_subdirectory(tests/gtest)
#   add_subdirectory(tests/ceftests)
# endif()

# if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/cefclient")
#    add_subdirectory(tests/cefclient)
# endif()

# Display configuration settings.
# PRINT_CEF_CONFIG()
