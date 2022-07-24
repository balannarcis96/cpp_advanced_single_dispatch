//!
//! \file CallingConventions.h
//! 
//! \brief calling convention macros, copiletime constants and types
//! 
//! \remarks update this file as needed
//! 
//! \author Balan Narcis (balannarcis96@gmail.com)
//! 
#pragma once

#include <type_traits>

#if defined(__INTEL_COMPILER)
    #define ASD_COMPILER_NAME "intel"
    #error "Unsupported yet!"
#elif defined(__GNUC__) && !defined(__clang__)
    #define ASD_COMPILER_NAME "gcc"
    #define ASD_CDECL      /* __attribute__((cdecl))     */ // GCC DOESNT ALLOW TO SPECIFY THE CALLING CONVENTION?
    #define ASD_STDCALL    /* __attribute__((stdcall))   */ // GCC DOESNT ALLOW TO SPECIFY THE CALLING CONVENTION?
    #define ASD_THISCALL   /* __attribute__((thiscall))  */ // GCC DOESNT ALLOW TO SPECIFY THE CALLING CONVENTION?
    #define ASD_FASTCALL   /* __attribute__((fastcall))  */ // GCC DOESNT ALLOW TO SPECIFY THE CALLING CONVENTION?
    #define ASD_VECTORCALL /* __attribute__((vectorcall))*/ // GCC DOESNT ALLOW TO SPECIFY THE CALLING CONVENTION?
    #if defined(_WIN32)
        #error "Unsupported yet!"
    #endif
#elif defined(__clang__)
    #define ASD_COMPILER_NAME "clang"
    #define ASD_CDECL      __attribute__((cdecl))
    #define ASD_STDCALL    __attribute__((cdecl))
    #define ASD_THISCALL   __attribute__((cdecl))
    #define ASD_FASTCALL   __attribute__((cdecl))
    #define ASD_VECTORCALL __attribute__((vectorcall))
    #if defined(_WIN32)
        #error "Unsupported yet!"
    #endif
#elif defined(_MSC_VER)
    #define ASD_COMPILER_NAME "msvc"
    #define ASD_CDECL      __cdecl
    #define ASD_STDCALL    __stdcall
    #define ASD_THISCALL   __thiscall
    #define ASD_FASTCALL   __fastcall
    #define ASD_VECTORCALL __vectorcall
    #if !defined(_WIN32)
        #error "Unsupported yet!"
    #endif
#else
    #define ASD_COMPILER_NAME "unknown"
    #error "Unsupported yet!"
#endif

namespace ASD
{
	struct CallingConventions
	{
	    using Cdecl      = void( ASD_CDECL* )();
	    using Stdcall    = void( ASD_STDCALL* )();
	    using Thiscall   = void( ASD_THISCALL* )();
	    using Fastcall   = void( ASD_FASTCALL* )();
	    using Vectorcall = void( ASD_VECTORCALL* )();

		template<typename T>
	    static constexpr bool IsCdecl       = std::is_same_v<Cdecl, T>;
	    static constexpr bool HasStdcall    = !IsCdecl<Stdcall>;
	    static constexpr bool HasThiscall   = !IsCdecl<Thiscall>;
	    static constexpr bool HasFastcall   = !IsCdecl<Fastcall>;
	    static constexpr bool HasVectorcall = !IsCdecl<Vectorcall>;
	};
}