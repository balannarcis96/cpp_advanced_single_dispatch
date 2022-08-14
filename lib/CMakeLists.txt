cmake_minimum_required (VERSION 3.8)
project ("single_dispatch" VERSION 1.0.0)

set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}/")

if (ASD_BUILD_HEADER_ONLY)
	add_library(AdvancedSingleDispatch STATIC HeaderOnly/AdvancedSingleDispatch.h SingleDispatch.cpp)
else()
	add_library(AdvancedSingleDispatch STATIC Utils.h CallingConvention.h FunctionTraits.h MethodTraits.h DelegateTraits.h FunctionPointer.h MethodPointer.h Delegate.h FunctorTraits.h FunctorWrapper.h Task.h SingleDispatch.h SingleDispatch.cpp)
endif()

target_include_directories(AdvancedSingleDispatch PUBLIC "${_src_root_path}/")

# Set C++17
set_property(TARGET AdvancedSingleDispatch PROPERTY CXX_STANDARD 17)

