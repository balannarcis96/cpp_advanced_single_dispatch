cmake_minimum_required (VERSION 3.8)
project ("single_dispatch" VERSION 1.0.0)

set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}/")

add_library(AdvancedSingleDispatch STATIC SingleDispatch.h SingleDispatch.cpp)
target_include_directories(AdvancedSingleDispatch PUBLIC "${_src_root_path}/")

# Set C++17
set_property(TARGET AdvancedSingleDispatch PROPERTY CXX_STANDARD 17)

