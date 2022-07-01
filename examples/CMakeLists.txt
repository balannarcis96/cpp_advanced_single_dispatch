cmake_minimum_required (VERSION 3.8)
project ("single_dispatch_examples" VERSION 1.0.0)

set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(Examples main.cpp)
target_link_libraries(Examples PUBLIC AdvancedSingleDispatch)

# Set C++17
set_property(TARGET Examples PROPERTY CXX_STANDARD 17)

