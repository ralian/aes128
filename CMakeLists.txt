# Author: Will Bowers (willb0102@gmail.com)
# Date:   31/10/18

# This is sort of arbitrary for now
cmake_minimum_required(VERSION 3.6.0)

project(aes128)

# Source includes
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Build three executables: an encryption command line executable, a
# decryption executable, and a unit testing executable.
#add_executable(encrypt enc.cpp aes.cpp)
#add_executable(decrypt dec.cpp aes.cpp)
add_executable(run_tests tests.cpp aes.cpp) 
