//!
//! \file MethodPointer.h
//! 
//! \brief class function(method) pointer abstraction
//! 
//! \author Balan Narcis (balannarcis96@gmail.com)
//! 
#pragma once

#include "MethodTraits.h"

namespace ASD
{
    class DummyClass;

    //!
    //! Simple class function pointer(method) wrapper
    //!
    //! \details Usage: MethodPtr<void(TClass::*)( int )> ptr = &TClass::DoSmth; ptr( Instance, ... )
    //! \details sizeof( MethodPtr< ... > ) == sizeof( void * )
    //!
    template<typename TFnPtrSignature>
    class MethodPtr : public MethodTraits<TFnPtrSignature>
    {
    public:
        using TMethodTraits     = MethodTraits<TFnPtrSignature>;
        using TFunctionPointer  = typename TMethodTraits::TPointer;
        using TMethodPointer    = typename TMethodTraits::TMethodPointer;
        using TReturnType       = typename TMethodTraits::TReturnType;
        using TArgsTypes        = typename TMethodTraits::TArgsTypes;
		using CallingConvention	= typename TMethodTraits::CallingConvention;
        using TClass            = typename TMethodTraits::TClassType;

		static constexpr std::size_t ArgsCount = TMethodTraits::ArgsCount;
        constexpr static bool IsNoexcept       = TMethodTraits::IsNoexcept;
		constexpr static bool IsVariadic       = TMethodTraits::IsVariadic;
        
		static constexpr const char* GetCallingConventionName()
		{
			return TMethodTraits::GetCallingConventionName();
		}

        MethodPtr() : TMethodTraits() {}
        MethodPtr( TMethodPointer Pointer ) : TMethodTraits( Pointer ) {}
	        
	    ASD_FORCEINLINE void operator=( TMethodPointer InPointer )
	    {
	        this->Pointer = *reinterpret_cast<TFunctionPointer*>( &InPointer );
	    }
        
	    ASD_FORCEINLINE bool operator==( TMethodPointer InPointer ) const
	    {
	        return this->Pointer == *reinterpret_cast<TFunctionPointer*>( &InPointer );
	    }

        ASD_FORCEINLINE explicit operator bool() const
        {
	        return false == IsNull(  );
        }

        ASD_NODISCARD bool IsNull() const
        {
	        return this->Pointer == nullptr;
        }
    };

    static_assert( sizeof ( MethodPtr<void( DummyClass::*)( void )> ) == sizeof( void * ) );
    static_assert( sizeof ( MethodPtr<void( ASD_CDECL DummyClass::* )( void )> ) == sizeof( void * ) );
    static_assert( sizeof ( MethodPtr<void( ASD_THISCALL DummyClass::* )( void )> ) == sizeof( void * ) );
    static_assert( sizeof ( MethodPtr<void( ASD_STDCALL DummyClass::* )( void )> ) == sizeof( void * ) );
    static_assert( sizeof ( MethodPtr<void( ASD_FASTCALL DummyClass::* )( void )> ) == sizeof( void * ) );
    static_assert( sizeof ( MethodPtr<void( ASD_VECTORCALL DummyClass::* )( void )> ) == sizeof( void * ) );

    static_assert( sizeof ( MethodPtr<void( DummyClass::* )( void ) noexcept> ) == sizeof( void * ) );
    static_assert( sizeof ( MethodPtr<void( ASD_CDECL DummyClass::* )( void ) noexcept> ) == sizeof( void * ) );
    static_assert( sizeof ( MethodPtr<void( ASD_THISCALL DummyClass::* )( void ) noexcept> ) == sizeof( void * ) );
    static_assert( sizeof ( MethodPtr<void( ASD_STDCALL DummyClass::* )( void ) noexcept> ) == sizeof( void * ) );
    static_assert( sizeof ( MethodPtr<void( ASD_FASTCALL DummyClass::* )( void ) noexcept> ) == sizeof( void * ) );
    static_assert( sizeof ( MethodPtr<void( ASD_VECTORCALL DummyClass::* )( void ) noexcept> ) == sizeof( void * ) );
}
