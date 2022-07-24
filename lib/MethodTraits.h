//!
//! \file MethodTraits.h
//! 
//! \brief class function(method) traits abstraction
//! 
//! \remark Reference (The Old New Thing): https://devblogs.microsoft.com/oldnewthing/20200713-00/?p=103978
//!
//! \author Balan Narcis (balannarcis96@gmail.com)
//! 
#pragma once

#include <tuple>
#include <type_traits>

#include "Utils.h"
#include "CallingConvention.h"

namespace ASD
{
	template<typename TCallingConvention, typename TClass, typename ReturnType, typename ...Args>
	struct MethodTraitsBase
	{
		using TReturnType					   = ReturnType;
		using TClassType					   = TClass;
		using TArgsTypes					   = std::tuple< Args... >;
		template<std::size_t N> using TNthArg  = std::tuple_element_t< N, TArgsTypes >;
		using CallingConvention				   = TCallingConvention;

		static constexpr std::size_t ArgsCount  = sizeof...( Args );
		static constexpr bool		 IsMethod   = true;
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
	struct MethodTraits;

	template<typename TClass, typename ReturnType, typename ...Args>															
	struct MethodTraits<ReturnType( ASD_CDECL TClass::* )( Args... ), 0>														
		: MethodTraitsBase<CallingConventions::Cdecl, TClass, ReturnType, Args...>													
	{																														
		using TBase						 = MethodTraitsBase< CallingConventions::Cdecl, TClass, ReturnType, Args... >;					
		using TPointer		             = ReturnType ( ASD_CDECL * )( void*, Args... );									
		using TMethodPointer		     = ReturnType ( ASD_CDECL TClass::* )( Args... );		
		constexpr static bool IsNoexcept = false;																			
		constexpr static bool IsVariadic = false;
																															
		MethodTraits() : Pointer{ nullptr } {}																				
		MethodTraits( TMethodPointer Pointer ) : Pointer{ *reinterpret_cast<TPointer>( &Pointer ) } {}															
		MethodTraits( const MethodTraits& Other ) = default;																
																															
		ASD_FORCEINLINE ReturnType ASD_CDECL operator()( TClass* Instance, Args... args ) const												
		{																													
			if constexpr ( !std::is_void<ReturnType>() )																	
				return Pointer( Instance, std::forward<Args>( args )... );															
			else																											
				Pointer( Instance, std::forward<Args>( args )... );																	
		}		

		ASD_FORCEINLINE ReturnType ASD_CDECL operator()( TClass& Instance, Args... args ) const												
		{																													
			if constexpr ( !std::is_void<ReturnType>() )																	
				return Pointer( &Instance, std::forward<Args>( args )... );															
			else																											
				Pointer( &Instance, std::forward<Args>( args )... );																	
		}	

protected:																													
		TPointer Pointer;																									
	};		
	
	template<typename TClass, typename ReturnType, typename ...Args>															
	struct MethodTraits<ReturnType( ASD_CDECL TClass::* )( Args... ) noexcept, 0>														
		: MethodTraitsBase<CallingConventions::Cdecl, TClass, ReturnType, Args...>													
	{																														
		using TBase						 = MethodTraitsBase<CallingConventions::Cdecl, TClass, ReturnType, Args...>;					
		using TPointer		             = ReturnType ( ASD_CDECL * )( void*, Args... ) noexcept;									
		using TMethodPointer		     = ReturnType ( ASD_CDECL TClass::* )( Args... ) noexcept;									
		constexpr static bool IsNoexcept = true;																			
		constexpr static bool IsVariadic = false;
																															
		MethodTraits() : Pointer{ nullptr } {}																				
		MethodTraits( TMethodPointer Pointer ) : Pointer{ *reinterpret_cast<TPointer>( &Pointer ) } {}															
		MethodTraits( const MethodTraits& Other ) = default;																
																															
		ASD_FORCEINLINE ReturnType ASD_CDECL operator()( TClass* Instance, Args... args ) const	noexcept											
		{																													
			if constexpr ( !std::is_void<ReturnType>() )																	
				return Pointer( Instance, std::forward<Args>( args )... );															
			else																											
				Pointer( Instance, std::forward<Args>( args )... );																	
		}		

		ASD_FORCEINLINE ReturnType ASD_CDECL operator()( TClass& Instance, Args... args ) const noexcept											
		{																													
			if constexpr ( !std::is_void<ReturnType>() )																	
				return Pointer( &Instance, std::forward<Args>( args )... );															
			else																											
				Pointer( &Instance, std::forward<Args>( args )... );																	
		}	

protected:																													
		TPointer Pointer;																									
	};

	//! As in some cases most calling conventions collapse to __cdecl we need to handle the type redefinition
#define ASD_MAKE_TRAITS( CallingConv, CallingConvType )																			\
	template<typename TClass, typename ReturnType, typename ...Args>															\
	struct MethodTraits<ReturnType( CallingConv TClass::* )( Args... ),															\
				std::is_same_v< CallingConventions::Cdecl, CallingConvType > ? __LINE__ : 0 >									\
		: MethodTraitsBase< CallingConventions::Cdecl, TClass, ReturnType, Args... >											\
	{																															\
		using TBase						 = MethodTraitsBase< CallingConvType, TClass, ReturnType, Args... >;					\
		using TPointer		             = ReturnType ( CallingConv * )( void*, Args... );										\
		using TMethodPointer		     = ReturnType ( CallingConv TClass::* )( Args... );										\
		constexpr static bool IsNoexcept = false;																				\
		constexpr static bool IsVariadic = false;																				\
																																\
		MethodTraits() : Pointer{ nullptr } {}																					\
		MethodTraits( TMethodPointer Pointer ) : Pointer{ *reinterpret_cast<TPointer>( &Pointer ) } {}							\
		MethodTraits( const MethodTraits& Other ) = default;																	\
																																\
		ASD_FORCEINLINE ReturnType CallingConv operator()( TClass* Instance, Args... args ) const								\
		{																														\
			if constexpr ( !std::is_void<ReturnType>() )																		\
				return Pointer( Instance, std::forward<Args>( args )... );														\
			else																												\
				Pointer( Instance, std::forward<Args>( args )... );																\
		}																														\
																																\
		ASD_FORCEINLINE ReturnType CallingConv operator()( TClass& Instance, Args... args ) const								\
		{																														\
			if constexpr ( !std::is_void<ReturnType>() )																		\
				return Pointer( &Instance, std::forward<Args>( args )... );														\
			else																												\
				Pointer( &Instance, std::forward<Args>( args )... );															\
		}																														\
																																\
protected:																														\
		TPointer Pointer;																										\
	};																															\
	template<typename TClass, typename ReturnType, typename ...Args>															\
	struct MethodTraits<ReturnType( CallingConv TClass::* )( Args... ) noexcept,												\
				std::is_same_v< CallingConventions::Cdecl, CallingConvType > ? __LINE__ + 50 : 0 >								\
		: MethodTraitsBase< CallingConventions::Cdecl, TClass, ReturnType, Args... >											\
	{																															\
		using TBase						 = MethodTraitsBase< CallingConventions::Cdecl, TClass, ReturnType, Args... >;			\
		using TPointer		             = ReturnType ( CallingConv * )( void*, Args... ) noexcept;								\
		using TMethodPointer		     = ReturnType ( CallingConv TClass::* )( Args... ) noexcept;							\
		constexpr static bool IsNoexcept = true;																				\
		constexpr static bool IsVariadic = false;																				\
																																\
		MethodTraits() : Pointer{ nullptr } {}																					\
		MethodTraits( TMethodPointer Pointer ) : Pointer{ *reinterpret_cast<TPointer>( &Pointer ) } {}							\
		MethodTraits( const MethodTraits& Other ) = default;																	\
																																\
		ASD_FORCEINLINE ReturnType CallingConv operator()( TClass* Instance, Args... args ) const	noexcept					\
		{																														\
			if constexpr ( !std::is_void<ReturnType>() )																		\
				return Pointer( Instance, std::forward<Args>( args )... );														\
			else																												\
				Pointer( Instance, std::forward<Args>( args )... );																\
		}																														\
																																\
		ASD_FORCEINLINE ReturnType CallingConv operator()( TClass& Instance, Args... args ) const noexcept						\
		{																														\
			if constexpr ( !std::is_void<ReturnType>() )																		\
				return Pointer( &Instance, std::forward<Args>( args )... );														\
			else																												\
				Pointer( &Instance, std::forward<Args>( args )... );															\
		}																														\
																																\
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
