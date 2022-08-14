cmake_minimum_required (VERSION 3.8)
project ("single_dispatch_repo" VERSION 1.0.0)

set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}")

file( GLOB_RECURSE _test_files LIST_DIRECTORIES false "${_src_root_path}/tests/*.h" )

add_executable(SingleDispatchTests main.cpp ${_test_files})
target_link_libraries(SingleDispatchTests PUBLIC AdvancedSingleDispatch)

# Link Google Test
target_link_libraries(SingleDispatchTests PUBLIC gtest_main)
#target_link_libraries(SingleDispatchTests PUBLIC GTest::gmock)

# Set C++17
set_property(TARGET SingleDispatchTests PROPERTY CXX_STANDARD 17)
