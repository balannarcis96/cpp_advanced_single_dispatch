cmake_minimum_required (VERSION 3.8)
project ("single_dispatch_repo" VERSION 1.0.0)

option(ASD_BUILD_TESTS "Build tests" ON) 

add_subdirectory ("lib")
add_subdirectory ("examples")

if(ASD_BUILD_TESTS)
	# google test lib
	add_subdirectory("googletest")	
	
	# ASD tests 
	add_subdirectory ("tests")
endif()

