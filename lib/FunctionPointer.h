//!
//! \file FunctionPointer.h
//! 
//! \brief function pointer abstraction
//! 
//! \author Balan Narcis (balannarcis96@gmail.com)
//! 
#pragma once

#include "FunctionTraits.h"

namespace ASD
{
    //!
    //! Simple function pointer wrapper
    //!
    //! \details Usage: FnPtr<void(*)( int )> ptr = DoSmth;
    //! \details sizeof( FnPtr< ... > ) == sizeof( void * )
    //!
    template<typename TFnPtrSignature>
    class FnPtr : public FunctionTraits<TFnPtrSignature>
    {
    public:
        using TFunctionTraits   = FunctionTraits<TFnPtrSignature>;
        using TFunctionPointer  = typename TFunctionTraits::TPointer;
        using TReturnType       = typename TFunctionTraits::TReturnType;
        using TArgsTypes        = typename TFunctionTraits::TArgsTypes;
		using CallingConvention	= typename TFunctionTraits::CallingConvention;

		static constexpr std::size_t ArgsCount = TFunctionTraits::ArgsCount;
        constexpr static bool IsNoexcept = TFunctionTraits::IsNoexcept;
		constexpr static bool IsVariadic = TFunctionTraits::IsVariadic;
        
		static constexpr const char* GetCallingConventionName()
		{
			return TFunctionTraits::GetCallingConventionName();
		}

        FnPtr() : TFunctionTraits( nullptr ) {}
        FnPtr( TFunctionPointer Pointer ) :  TFunctionTraits( Pointer ) {}
        
        ASD_FORCEINLINE void operator =( TFunctionPointer InPointer )
        {
             this->Pointer = InPointer;
        }

	    ASD_FORCEINLINE bool operator==( TFunctionPointer InPointer ) const
	    {
	        return  this->Pointer == InPointer;
	    }

        ASD_FORCEINLINE explicit operator bool() const
        {
	        return false == IsNull();
        }

        ASD_NODISCARD bool IsNull() const
        {
	        return nullptr == this->Pointer;
        }

        static_assert( false == ASD::CallingConventions::HasThiscall || std::is_same_v<ASD::CallingConventions::Thiscall, CallingConvention>, "This call is unsupported!" );
    };
    
    static_assert( sizeof ( FnPtr<void( ASD_CDECL* )( void )> ) == sizeof( void * ) );
    static_assert( sizeof ( FnPtr<void( ASD_THISCALL* )( void )> ) == sizeof( void * ) );
    static_assert( sizeof ( FnPtr<void( ASD_FASTCALL* )( void )> ) == sizeof( void * ) );
    static_assert( sizeof ( FnPtr<void( ASD_VECTORCALL* )( void )> ) == sizeof( void * ) );
                                            
    static_assert( sizeof ( FnPtr<void( ASD_CDECL* )( void ) noexcept> ) == sizeof( void * ) );
    static_assert( sizeof ( FnPtr<void( ASD_THISCALL* )( void ) noexcept> ) == sizeof( void * ) );
    static_assert( sizeof ( FnPtr<void( ASD_FASTCALL* )( void ) noexcept> ) == sizeof( void * ) );
    static_assert( sizeof ( FnPtr<void( ASD_VECTORCALL* )( void ) noexcept> ) == sizeof( void * ) );
}
