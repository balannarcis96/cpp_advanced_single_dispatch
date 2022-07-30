cmake_minimum_required (VERSION 3.8)
project ("single_dispatch_repo" VERSION 1.0.0)

option(ASD_BUILD_TESTS "Build tests" ON) 
option(ASD_BUILD_HEADER_ONLY "Build header only library" ON) 

if(ASD_BUILD_TESTS)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		set(MSVC_COMPILE_OPTIONS "/MP /MT")
		set(MSVC_COMPILE_DEBUG_OPTIONS "${CMAKE_CXX_FLAGS_DEBUG} ${MSVC_COMPILE_OPTIONS} /ZI /Od")
		set(MSVC_COMPILE_RELEASE_OPTIONS "${CMAKE_CXX_FLAGS_RELEASE} ${MSVC_COMPILE_OPTIONS} /O2")
		set(CMAKE_CXX_FLAGS_DEBUG "${MSVC_COMPILE_DEBUG_OPTIONS}")
		set(CMAKE_CXX_FLAGS_RELEASE "${MSVC_COMPILE_RELEASE_OPTIONS}")
	endif()
endif()
	
if (ASD_BUILD_HEADER_ONLY)
	add_compile_definitions(ASD_HEADER_ONLY=1)
else()
	add_compile_definitions(ASD_HEADER_ONLY=0)
endif()

add_subdirectory ("lib")

if(ASD_BUILD_TESTS)
	# google test lib
	add_subdirectory("googletest")	
	
	# ASD tests 
	add_subdirectory ("tests")
endif()

