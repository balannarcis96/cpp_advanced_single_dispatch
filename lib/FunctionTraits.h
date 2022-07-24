//!
//! \file FunctionTraits.h
//! 
//! \brief function traits abstraction
//! 
//! \remark Reference (The Old New Thing): https://devblogs.microsoft.com/oldnewthing/20200713-00/?p=103978
//!
//! \author Balan Narcis (balannarcis96@gmail.com)
//! 
#pragma once

#include <tuple>

#include "Utils.h"
#include "CallingConvention.h"

namespace ASD
{
	template<typename TCallingConvention, typename ReturnType, typename ...Args>
	struct FunctionTraitsBase
	{
		using TReturnType					   = ReturnType;
		using TArgsTypes					   = std::tuple< Args... >;
		template<std::size_t N> using TNthArg  = std::tuple_element_t< N, TArgsTypes >;
		using CallingConvention				   = TCallingConvention;

		static constexpr std::size_t ArgsCount  = sizeof...( Args );
		static constexpr bool		 IsMethod   = false;
		static constexpr bool		 IsDelegate = false;

		static constexpr const char* GetCallingConventionName()
		{
			if ( std::is_same<CallingConvention, CallingConventions::Vectorcall>() && CallingConventions::HasVectorcall ) { return "vectorcall"; }
			if ( std::is_same<CallingConvention, CallingConventions::Fastcall>()   && CallingConventions::HasFastcall ) { return "fastcall"; }
			if ( std::is_same<CallingConvention, CallingConventions::Thiscall>()   && CallingConventions::HasThiscall ) { return "thiscall"; }
			if ( std::is_same<CallingConvention, CallingConventions::Stdcall>()    && CallingConventions::HasStdcall ) { return "stdcall"; }
			
			return "cdecl";
		}
	};

	template<typename F, int = 0>
	struct FunctionTraits;

	template< typename ReturnType, typename ...Args >																			
	struct FunctionTraits< ReturnType( ASD_CDECL * )(Args...), 0 >																
		: FunctionTraitsBase< CallingConventions::Cdecl, ReturnType, Args... >													
	{																															
		using TBase						 = FunctionTraitsBase< CallingConventions::Cdecl, ReturnType, Args... >;				
		using TPointer		             = ReturnType ( ASD_CDECL * )(Args...);													
		constexpr static bool IsNoexcept = false;																				
		constexpr static bool IsVariadic = !std::is_same_v< void( ASD_CDECL * )(Args...), void( ASD_CDECL * )( Args... ) >;		
																																
		FunctionTraits() : Pointer{ nullptr } {}																				
		FunctionTraits( TPointer Pointer ) : Pointer{ Pointer } {}																
		FunctionTraits( const FunctionTraits& Other ) = default;																
																																
		ASD_FORCEINLINE ReturnType ASD_CDECL operator()( Args... args ) const													
		{																														
			if constexpr ( !std::is_void<ReturnType>() )																		
				return Pointer( std::forward<Args>( args )... );																
			else																												
				Pointer( std::forward<Args>( args )... );																		
		}																														
protected:																														
		TPointer Pointer;																										
	};																															
	
	template< typename ReturnType, typename ...Args >																			
	struct FunctionTraits< ReturnType( ASD_CDECL * )(Args...) noexcept, 0 >														
		: FunctionTraitsBase< CallingConventions::Cdecl, ReturnType, Args... >													
	{																															
		using TBase						 = FunctionTraitsBase< CallingConventions::Cdecl, ReturnType, Args... >;				
		using TPointer		             = ReturnType ( ASD_CDECL * )(Args...) noexcept;										
		constexpr static bool IsNoexcept = true;																				
		constexpr static bool IsVariadic = !std::is_same_v< void( ASD_CDECL * )(Args...), void( ASD_CDECL * )( Args... ) >;		
																																
		FunctionTraits() : Pointer{ nullptr } {}																				
		FunctionTraits( TPointer Pointer ) : Pointer{ Pointer } {}																
		FunctionTraits( const FunctionTraits& Other ) = default;																
																																
		ASD_FORCEINLINE ReturnType ASD_CDECL operator()( Args... args ) const noexcept											
		{																														
			if constexpr ( !std::is_void<ReturnType>() )																		
				return Pointer( std::forward<Args>( args )... );																
			else																												
				Pointer( std::forward<Args>( args )... );																		
		}																														
protected:																														
		TPointer Pointer;																										
	};

	//! As in some cases most calling conventions collapse to __cdecl we need to handle the type redefinition
#define ASD_MAKE_TRAITS( CallingConv, CallingConvType )																		    \
	template< typename ReturnType, typename ...Args >																			\
	struct FunctionTraits< ReturnType( CallingConv * )(Args...),																\
				std::is_same_v< CallingConventions::Cdecl, CallingConvType > ? __LINE__ : 0 >									\
		: FunctionTraitsBase< CallingConvType, ReturnType, Args... >															\
	{																															\
		using TBase						 = FunctionTraitsBase< CallingConvType, ReturnType, Args... >;							\
		using TPointer		             = ReturnType ( CallingConv * )(Args...);												\
		constexpr static bool IsNoexcept = false;																				\
		constexpr static bool IsVariadic = !std::is_same_v< void( CallingConv * )(Args...), void( CallingConv * )(Args...) >;	\
																																\
		FunctionTraits() : Pointer{ nullptr } {}																				\
		FunctionTraits( TPointer Pointer ) : Pointer{ Pointer } {}																\
		FunctionTraits( const FunctionTraits& Other ) = default;																\
																																\
		ASD_FORCEINLINE ReturnType CallingConv operator()( Args... args ) const													\
		{																														\
			if constexpr ( !std::is_void<ReturnType>() )																		\
				return Pointer( std::forward<Args>( args )... );																\
			else																												\
				Pointer( std::forward<Args>( args )... );																		\
		}																														\
protected:																														\
		TPointer Pointer;																										\
	};																															\
	template< typename ReturnType, typename ...Args >																			\
	struct FunctionTraits< ReturnType( CallingConv * )(Args...) noexcept,														\
				std::is_same_v< CallingConventions::Cdecl, CallingConvType > ? __LINE__ : 0 >									\
		: FunctionTraitsBase< CallingConvType, ReturnType, Args... >															\
	{																															\
		using TBase						 = FunctionTraitsBase< CallingConvType, ReturnType, Args... >;							\
		using TPointer		             = ReturnType ( CallingConv * )(Args...) noexcept;										\
		constexpr static bool IsNoexcept = true;																				\
		constexpr static bool IsVariadic = !std::is_same_v< void( CallingConv * )(Args...), void( CallingConv * )(Args...) >;	\
																																\
		FunctionTraits() : Pointer{ nullptr } {}																				\
		FunctionTraits( TPointer Pointer ) : Pointer{ Pointer } {}																\
		FunctionTraits( const FunctionTraits& Other ) = default;																\
																																\
		ASD_FORCEINLINE ReturnType CallingConv operator()( Args... args ) const	noexcept										\
		{																														\
			if constexpr ( !std::is_void<ReturnType>() )																		\
				return Pointer( std::forward<Args>( args )... );																\
			else																												\
				Pointer( std::forward<Args>( args )... );																		\
		}																														\
protected:																														\
		TPointer Pointer;																										\
	};

	// Function Traits (variadic functions not supported!)
	ASD_MAKE_TRAITS( ASD_STDCALL,	 CallingConventions::Stdcall );
	ASD_MAKE_TRAITS( ASD_THISCALL,   CallingConventions::Thiscall );
	ASD_MAKE_TRAITS( ASD_VECTORCALL, CallingConventions::Vectorcall );
	ASD_MAKE_TRAITS( ASD_FASTCALL,   CallingConventions::Fastcall );

#undef ASD_MAKE_TRAITS
}
