//!
//! \file Utils.h
//! 
//! \brief macros, utility functions and types
//! 
//! \author Balan Narcis (balannarcis96@gmail.com)
//! 
#pragma once

#include <type_traits>

#if defined(__GNUC__) || defined(__clang__)
	#define ASD_FORCEINLINE __attribute__((always_inline))
#elif defined(_MSC_VER) || defined(__INTEL_COMPILER)
	#define ASD_FORCEINLINE __forceinline
#else
	#define ASD_FORCEINLINE 
#endif

//c++17 and latter
#define ASD_NODISCARD [[nodiscard]]

#if __cplusplus > 201703 
#define ASD_UNLIKELY [[unlikely]]
#define ASD_LIKELY [[likely]]
#else
#define ASD_UNLIKELY 
#define ASD_LIKELY
#endif
