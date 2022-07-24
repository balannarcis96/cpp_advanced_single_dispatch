//!
//! \file DelegateTraits.h
//! 
//! \brief delegate traits abstraction
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
	template<template<typename ...> typename PointerWrapper, typename TCallingConvention, typename TClass, typename ReturnType, typename ...Args>
	struct DelegateTraitsBase
	{
		using TReturnType					   = ReturnType;
		using TClassType					   = TClass;
		using TArgsTypes					   = std::tuple< Args... >;
		template<std::size_t N> using TNthArg  = std::tuple_element_t< N, TArgsTypes >;
		using CallingConvention				   = TCallingConvention;
		template<typename ...TArgs>
		using TPointerWrapper                  = std::conditional_t<std::is_void_v<PointerWrapper<TArgs...>>, TClass*, PointerWrapper<TArgs...>>;
		using TInstancePointer                 = TPointerWrapper<TClass>;

		static constexpr std::size_t ArgsCount  = sizeof...( Args );
		static constexpr bool		 IsMethod   = true;
		static constexpr bool		 IsDelegate = true;

		static constexpr const char* GetCallingConventionName()
		{
			if ( std::is_same<CallingConvention, CallingConventions::Vectorcall>() && CallingConventions::HasVectorcall ) { return "vectorcall"; }
			if ( std::is_same<CallingConvention, CallingConventions::Fastcall>()   && CallingConventions::HasFastcall ) { return "fastcall"; }
			if ( std::is_same<CallingConvention, CallingConventions::Thiscall>()   && CallingConventions::HasThiscall ) { return "thiscall"; }
			if ( std::is_same<CallingConvention, CallingConventions::Stdcall>()    && CallingConventions::HasStdcall ) { return "stdcall"; }
			
			return "cdecl";
		}
	};

	template<template<typename ...> typename TPointerWrapper, typename F, int = 0>
	struct DelegateTraits;

	template<template<typename ...> typename TPointerWrapper, typename TClass, typename ReturnType, typename ...Args>															
	struct DelegateTraits<TPointerWrapper, ReturnType( ASD_CDECL TClass::* )( Args... ), 0>														
		: DelegateTraitsBase<TPointerWrapper, CallingConventions::Cdecl, TClass, ReturnType, Args...>													
	{																														
		using TBase						 = DelegateTraitsBase<TPointerWrapper, CallingConventions::Cdecl, TClass, ReturnType, Args...>;					
		using TPointer		             = ReturnType ( ASD_CDECL * )( void*, Args... );									
		using TMethodPointer		     = ReturnType ( ASD_CDECL TClass::* )( Args... );		
		using TInstancePointer           = typename TBase::TInstancePointer;
		constexpr static bool IsNoexcept = false;																			
		constexpr static bool IsVariadic = false;
																													
		ASD_FORCEINLINE ReturnType ASD_CDECL operator()( Args... args ) const									
		{																											
			if constexpr ( !std::is_void<ReturnType>() )																	
                if constexpr( std::is_class<TInstancePointer>() )
				    return Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer.get() ) ), std::forward<Args>( args )... );															
                else
				    return Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer ) ), std::forward<Args>( args )... );															
			else																											
				Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer ) ), std::forward<Args>( args )... );																	
		}		
																																
		ASD_FORCEINLINE ReturnType ASD_CDECL Dispatch( Args... args ) const								
		{																											
			if constexpr ( !std::is_void<ReturnType>() )																	
                if constexpr( std::is_class<TInstancePointer>() )
				    return Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer.get() ) ), std::forward<Args>( args )... );															
                else
				    return Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer ) ), std::forward<Args>( args )... );															
			else																											
				Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer ) ), std::forward<Args>( args )... );																	
		}		
																														
		ASD_FORCEINLINE ReturnType ASD_CDECL Dispatch( TClass* OtherInstancePointer, Args... args ) const										
		{																													
			if constexpr ( !std::is_void<ReturnType>() )																	
				return Pointer( OtherInstancePointer, std::forward<Args>( args )... );															
			else																											
				Pointer( OtherInstancePointer, std::forward<Args>( args )... );																	
		}		
																													
		ASD_FORCEINLINE ReturnType ASD_CDECL Dispatch( TClass& OtherInstance, Args... args ) const								
		{																													
			if constexpr ( !std::is_void<ReturnType>() )																	
				return Pointer( &OtherInstance, std::forward<Args>( args )... );															
			else																											
				Pointer( &OtherInstance, std::forward<Args>( args )... );																	
		}		

protected:																													
		TPointer		 Pointer;	
		TInstancePointer InstancePointer;
	};		
	
	template<template<typename ...> typename TPointerWrapper, typename TClass, typename ReturnType, typename ...Args>															
	struct DelegateTraits<TPointerWrapper, ReturnType( ASD_CDECL TClass::* )( Args... ) noexcept, 0>														
		: DelegateTraitsBase<TPointerWrapper, CallingConventions::Cdecl, TClass, ReturnType, Args...>													
	{																														
		using TBase						 = DelegateTraitsBase<TPointerWrapper, CallingConventions::Cdecl, TClass, ReturnType, Args...>;					
		using TPointer		             = ReturnType ( ASD_CDECL * )( void*, Args... ) noexcept;									
		using TMethodPointer		     = ReturnType ( ASD_CDECL TClass::* )( Args... ) noexcept;									
		using TInstancePointer           = typename TBase::TInstancePointer;
		constexpr static bool IsNoexcept = true;																			
		constexpr static bool IsVariadic = false;
																																		
		ASD_FORCEINLINE ReturnType ASD_CDECL operator()( Args... args ) const noexcept											
		{																											
			if constexpr ( !std::is_void<ReturnType>() )																	
                if constexpr( std::is_class<TInstancePointer>() )
				    return Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer.get() ) ), std::forward<Args>( args )... );															
                else
				    return Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer ) ), std::forward<Args>( args )... );															
			else																											
				Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer ) ), std::forward<Args>( args )... );																	
		}		
																																
		ASD_FORCEINLINE ReturnType ASD_CDECL Dispatch( Args... args ) const	noexcept											
		{																											
			if constexpr ( !std::is_void<ReturnType>() )																	
                if constexpr( std::is_class<TInstancePointer>() )
				    return Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer.get() ) ), std::forward<Args>( args )... );															
                else
				    return Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer ) ), std::forward<Args>( args )... );															
			else																											
				Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer ) ), std::forward<Args>( args )... );																	
		}		
																														
		ASD_FORCEINLINE ReturnType ASD_CDECL Dispatch( TClass* OtherInstancePointer, Args... args ) const noexcept											
		{																													
			if constexpr ( !std::is_void<ReturnType>() )																	
				return Pointer( OtherInstancePointer, std::forward<Args>( args )... );															
			else																											
				Pointer( OtherInstancePointer, std::forward<Args>( args )... );																	
		}		
																													
		ASD_FORCEINLINE ReturnType ASD_CDECL Dispatch( TClass& OtherInstance, Args... args ) const	noexcept											
		{																													
			if constexpr ( !std::is_void<ReturnType>() )																	
				return Pointer( &OtherInstance, std::forward<Args>( args )... );															
			else																											
				Pointer( &OtherInstance, std::forward<Args>( args )... );																	
		}		

protected:																													
		TPointer		 Pointer;	
		TInstancePointer InstancePointer;																									
	};

	//! As in some cases most calling conventions collapse to __cdecl we need to handle the type redefinition
#define ASD_MAKE_TRAITS( CallingConv, CallingConvType )																																															  \
																																																												  \
	template<template<typename ...> typename TPointerWrapper, typename TClass, typename ReturnType, typename ...Args>																															  \
	struct DelegateTraits<TPointerWrapper, ReturnType( CallingConv TClass::* )( Args... ), 																																					      \
				std::is_same_v< CallingConventions::Cdecl, CallingConvType > ? __LINE__ : 0 >																																					  \
		: DelegateTraitsBase<TPointerWrapper, CallingConvType, TClass, ReturnType, Args...>																																						  \
	{																																																											  \
		using TBase						 = DelegateTraitsBase<TPointerWrapper, CallingConvType, TClass, ReturnType, Args...>;																											          \
		using TPointer		             = ReturnType ( CallingConv * )( void*, Args... );																																						  \
		using TMethodPointer		     = ReturnType ( CallingConv TClass::* )( Args... );																																						  \
		using TInstancePointer           = typename TBase::TInstancePointer;																																									  \
		constexpr static bool IsNoexcept = false;																																																  \
		constexpr static bool IsVariadic = false;																																																  \
																																																												  \
		ASD_FORCEINLINE ReturnType ASD_CDECL operator()( Args... args ) const noexcept																																						      \
		{																																																										  \
			if constexpr ( !std::is_void<ReturnType>() )																																														  \
                if constexpr( std::is_class<TInstancePointer>() )																																												  \
				    return Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer.get() ) ), std::forward<Args>( args )... );																										  \
                else																																																							  \
				    return Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer ) ), std::forward<Args>( args )... );																											  \
			else																																																								  \
				Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer ) ), std::forward<Args>( args )... );																														  \
		}																																																										  \
																																																												  \
		ASD_FORCEINLINE ReturnType ASD_CDECL Dispatch( Args... args ) const	noexcept																																							  \
		{																																																										  \
			if constexpr ( !std::is_void<ReturnType>() )																																														  \
                if constexpr( std::is_class<TInstancePointer>() )																																												  \
				    return Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer.get() ) ), std::forward<Args>( args )... );																										  \
                else																																																							  \
				    return Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer ) ), std::forward<Args>( args )... );																											  \
			else																																																								  \
				Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer ) ), std::forward<Args>( args )... );																														  \
		}																																																										  \
																																																											  	  \
		ASD_FORCEINLINE ReturnType CallingConv Dispatch( TClass* OtherInstancePointer, Args... args ) const																																		  \
		{																																																										  \
			if constexpr ( !std::is_void<ReturnType>() )																																														  \
				return Pointer( OtherInstancePointer, std::forward<Args>( args )... );																																							  \
			else																																																								  \
				Pointer( OtherInstancePointer, std::forward<Args>( args )... );																																									  \
		}																																																										  \
																																																												  \
		ASD_FORCEINLINE ReturnType CallingConv Dispatch( TClass& OtherInstance, Args... args ) const																																			  \
		{																																																										  \
			if constexpr ( !std::is_void<ReturnType>() )																																														  \
				return Pointer( &OtherInstance, std::forward<Args>( args )... );																																								  \
			else																																																								  \
				Pointer( &OtherInstance, std::forward<Args>( args )... );																																										  \
		}																																																										  \
																																																												  \
protected:																																																										  \
		TPointer		 Pointer;																																																				  \
		TInstancePointer InstancePointer;																																																		  \
	};																																																											  \
	template<template<typename ...> typename TPointerWrapper, typename TClass, typename ReturnType, typename ...Args>																															  \
	struct DelegateTraits<TPointerWrapper, ReturnType( CallingConv TClass::* )( Args... ) noexcept, 																																			  \
				std::is_same_v< CallingConventions::Cdecl, CallingConvType > ? __LINE__ + 50 : 0 >																																		          \
		: DelegateTraitsBase<TPointerWrapper, CallingConvType, TClass, ReturnType, Args...>																																						  \
	{																																																											  \
		using TBase						 = DelegateTraitsBase<TPointerWrapper, CallingConvType, TClass, ReturnType, Args...>;																													  \
		using TPointer		             = ReturnType ( CallingConv * )( void*, Args... ) noexcept;																																				  \
		using TMethodPointer		     = ReturnType ( CallingConv TClass::* )( Args... ) noexcept;																																		      \
		using TInstancePointer           = typename TBase::TInstancePointer;																																									  \
		constexpr static bool IsNoexcept = true;																																																  \
		constexpr static bool IsVariadic = false;																																																  \
																																																												  \
		ASD_FORCEINLINE ReturnType ASD_CDECL operator()( Args... args ) const noexcept																																						      \
		{																																																										  \
			if constexpr ( !std::is_void<ReturnType>() )																																														  \
                if constexpr( std::is_class<TInstancePointer>() )																																												  \
				    return Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer.get() ) ), std::forward<Args>( args )... );																										  \
                else																																																							  \
				    return Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer ) ), std::forward<Args>( args )... );																											  \
			else																																																								  \
				Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer ) ), std::forward<Args>( args )... );																														  \
		}																																																										  \
																																																												  \
		ASD_FORCEINLINE ReturnType ASD_CDECL Dispatch( Args... args ) const	noexcept																																							  \
		{																																																										  \
			if constexpr ( !std::is_void<ReturnType>() )																																														  \
                if constexpr( std::is_class<TInstancePointer>() )																																												  \
				    return Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer.get() ) ), std::forward<Args>( args )... );																										  \
                else																																																							  \
				    return Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer ) ), std::forward<Args>( args )... );																											  \
			else																																																								  \
				Pointer( const_cast<void*>(static_cast<const void*>( InstancePointer ) ), std::forward<Args>( args )... );																														  \
		}																																																										  \
																																																												  \
		ASD_FORCEINLINE ReturnType CallingConv Dispatch( TClass* OtherInstancePointer, Args... args ) const	noexcept																															  \
		{																																																										  \
			if constexpr ( !std::is_void<ReturnType>() )																																														  \
				return Pointer( OtherInstancePointer, std::forward<Args>( args )... );																																							  \
			else																																																								  \
				Pointer( OtherInstancePointer, std::forward<Args>( args )... );																																									  \
		}																																																										  \
																																																												  \
		ASD_FORCEINLINE ReturnType CallingConv Dispatch( TClass& OtherInstance, Args... args ) const noexcept																																	  \
		{																																																										  \
			if constexpr ( !std::is_void<ReturnType>() )																																														  \
				return Pointer( &OtherInstance, std::forward<Args>( args )... );																																								  \
			else																																																								  \
				Pointer( &OtherInstance, std::forward<Args>( args )... );																																										  \
		}																																																										  \
																																																												  \
protected:																																																										  \
		TPointer		 Pointer;																																																				  \
		TInstancePointer InstancePointer;																																																		  \
	};																																																											  
																																																												  
	// Function Traits (variadic functions not supported!)
	ASD_MAKE_TRAITS( ASD_STDCALL,	 CallingConventions::Stdcall );
	ASD_MAKE_TRAITS( ASD_THISCALL,   CallingConventions::Thiscall );
	ASD_MAKE_TRAITS( ASD_VECTORCALL, CallingConventions::Vectorcall );
	ASD_MAKE_TRAITS( ASD_FASTCALL,   CallingConventions::Fastcall );

#undef ASD_MAKE_TRAITS
}
