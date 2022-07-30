//!
//! \file Delegate.h
//! 
//! \brief delegate abstraction
//! 
//! \author Balan Narcis (balannarcis96@gmail.com)
//! 
#pragma once

#include <memory>

#include "DelegateTraits.h"

namespace ASD
{
	//!
    //! Base class for all delegate types
    //!
    //! \details See RawDelegate< ... >, UniqueDelegate< ... >, SharedDelegate< ... >
    //! \details sizeof( DelegateBase< ... > ) == sizeof( void * ) * 2
    //!
    template<template<typename ...> typename TPointerWrapper, typename TFnPtrSignature>
    class DelegateBase : public DelegateTraits<TPointerWrapper, TFnPtrSignature>
    {
    public:
        using TDelegateTraits    = DelegateTraits<TPointerWrapper, TFnPtrSignature>;
        using TFunctionPointer   = typename TDelegateTraits::TPointer;
        using TMethodPointer     = typename TDelegateTraits::TMethodPointer;
        using TReturnType        = typename TDelegateTraits::TReturnType;
        using TArgsTypes         = typename TDelegateTraits::TArgsTypes;
		using CallingConvention	 = typename TDelegateTraits::CallingConvention;
        using TClass             = typename TDelegateTraits::TClassType;
		using TInstancePointer   = typename TDelegateTraits::TInstancePointer;
        
		static constexpr std::size_t ArgsCount = TDelegateTraits::ArgsCount;
        constexpr static bool IsNoexcept       = TDelegateTraits::IsNoexcept;
		constexpr static bool IsVariadic       = TDelegateTraits::IsVariadic;
                
#if defined(_MSC_VER)
        DelegateBase() : DelegateTraits() {}
        DelegateBase( TMethodPointer MethodPointer ) : DelegateTraits() 
        {
            this->Pointer         = *reinterpret_cast<TFunctionPointer*>( &MethodPointer );
            this->InstancePointer = nullptr;          
        }
        template<typename = std::enable_if_t<true == std::is_copy_assignable_v<TInstancePointer>>>
        DelegateBase( TMethodPointer MethodPointer, const TInstancePointer& InInstancePointer ) : DelegateTraits() 
        {
            this->Pointer         = *reinterpret_cast<TFunctionPointer*>( &MethodPointer );
            this->InstancePointer = InInstancePointer;          
        }
        template<typename = std::enable_if_t<true == std::is_move_assignable_v<TInstancePointer>>>
        DelegateBase( TMethodPointer MethodPointer, TInstancePointer&& InInstancePointer ) : DelegateTraits() 
        {
            this->Pointer         = *reinterpret_cast<TFunctionPointer*>( &MethodPointer );
            this->InstancePointer = std::forward<TInstancePointer>( InInstancePointer );          
        }

#else
        DelegateBase() : TDelegateTraits() {}
        DelegateBase( TMethodPointer MethodPointer ) : TDelegateTraits() 
        {
            this->Pointer         = *reinterpret_cast<TFunctionPointer*>( &MethodPointer );
            this->InstancePointer = nullptr;          
        }
        template<typename = std::enable_if_t<true == std::is_copy_assignable_v<TInstancePointer>>>
        DelegateBase( TMethodPointer MethodPointer, const TInstancePointer& InInstancePointer ) : TDelegateTraits() 
        {
            this->Pointer         = *reinterpret_cast<TFunctionPointer*>( &MethodPointer );
            this->InstancePointer = InInstancePointer;          
        }
        template<typename = std::enable_if_t<true == std::is_move_assignable_v<TInstancePointer>>>
        DelegateBase( TMethodPointer MethodPointer, TInstancePointer&& InInstancePointer ) : TDelegateTraits() 
        {
            this->Pointer         = *reinterpret_cast<TFunctionPointer*>( &MethodPointer );
            this->InstancePointer = std::forward<TInstancePointer>( InInstancePointer );          
        }
#endif
        //copy ctor
        template<typename = std::enable_if_t<true == std::is_copy_constructible_v<TInstancePointer>>>
        DelegateBase( const DelegateBase& Other )
        {
            this->Pointer         = Other.Pointer;
            this->InstancePointer = Other.InstancePointer;
        }
        //move ctor
        template<typename = std::enable_if_t<true == std::is_move_constructible_v<TInstancePointer>>>
        DelegateBase( DelegateBase&& Other ) noexcept
        {
            this->Pointer         = Other.Pointer;
            this->InstancePointer = std::move( Other.InstancePointer );

            Other.Pointer = nullptr;
        }
        //copy assignment operator
        template<typename = std::enable_if_t<true == std::is_copy_assignable_v<TInstancePointer>>>
        DelegateBase& operator=( const DelegateBase& Other )
        {
            if( this == &Other ) ASD_UNLIKELY
            {
                return *this;
            }

            this->Pointer         = Other.Pointer;
            this->InstancePointer = Other.InstancePointer;

            return *this;
        }
        //move assignment operator
        template<typename = std::enable_if_t<true == std::is_move_assignable_v<TInstancePointer>>>
        DelegateBase& operator=( DelegateBase&& Other ) noexcept
        {
            if( this == &Other ) ASD_UNLIKELY
            {
                return *this;
            }

            this->Pointer         = Other.Pointer;
            this->InstancePointer = std::move( Other.InstancePointer );

            Other.Pointer = nullptr;

            return *this;
        }

        ASD_FORCEINLINE explicit operator bool() const
        {
	        return false == IsNull(  );
        }

        ASD_NODISCARD ASD_FORCEINLINE bool IsNull() const
        {
	        return this->Pointer == nullptr || this->InstancePointer == nullptr;
        }
        
        ASD_NODISCARD ASD_FORCEINLINE bool HasMethod() const
        {
	        return this->Pointer != nullptr;
        }
        
        ASD_NODISCARD ASD_FORCEINLINE bool HasInstance() const
        {
	        return false == ( this->InstancePointer == nullptr );
        }
        
        ASD_NODISCARD ASD_FORCEINLINE TMethodPointer GetMethod() const
        {
            union TMethodPtrBuilder
            {
                TFunctionPointer FnPtr;
                TMethodPointer   MethodPtr;
            };

            TMethodPtrBuilder Builder;
            memset( &Builder, 0, sizeof( Builder ) );

            Builder.FnPtr = this->Pointer;

	        return Builder.MethodPtr;;
        }
        
        ASD_NODISCARD ASD_FORCEINLINE TClass* GetInstance() const
        {
            if constexpr( std::is_class_v<TInstancePointer> )
            {
	           return this->InstancePointer.get();
            }
            else
            {
	           return this->InstancePointer;
            }
        }
        
        template<typename = std::enable_if_t<true == std::is_copy_constructible_v<TInstancePointer>>>
        ASD_NODISCARD ASD_FORCEINLINE TInstancePointer GetInstancePtr() const
        {
	        return this->InstancePointer;
        }

        template<typename = std::enable_if_t<true == std::is_copy_assignable_v<TInstancePointer>>>
        ASD_FORCEINLINE void SetInstance( const TInstancePointer& InInstancePointer )
        {
            this->InstancePointer = InInstancePointer;
        }
        
        template<typename = std::enable_if_t<true == std::is_move_assignable_v<TInstancePointer>>>
        ASD_FORCEINLINE void SetInstance( TInstancePointer&& InInstancePointer )
        {
            this->InstancePointer = std::forward<TInstancePointer>( InInstancePointer );
        }

        template<typename = std::enable_if_t<true == std::is_copy_assignable_v<TInstancePointer>>>
        ASD_NODISCARD TInstancePointer ResetInstance( const TInstancePointer& InInstancePtr )
        {
            TInstancePointer Temp = this->InstancePointer;
            this->InstancePointer = InInstancePtr;

            return Temp;
        }
        
        template<typename = std::enable_if_t<true == std::is_move_assignable_v<TInstancePointer>>>
        ASD_NODISCARD TInstancePointer ResetInstance( TInstancePointer&& InInstancePtr )
        {
            TInstancePointer Temp = std::move( this->InstancePointer );
            this->InstancePointer = std::forward<TInstancePointer> ( InInstancePtr );

            return Temp;
        }

        ASD_NODISCARD TInstancePointer ReleaseInstance()
        {
            TInstancePointer Temp = std::move ( this->InstancePointer );
            this->InstancePointer = nullptr;

            return Temp;
        }

        ASD_FORCEINLINE void SetMethod( TMethodPointer InMethodPointer )
        {
            this->Pointer = *reinterpret_cast<TFunctionPointer*>( &InMethodPointer );
        }
        
        template<typename = std::enable_if_t<true == std::is_move_assignable_v<TInstancePointer>>>
        ASD_FORCEINLINE void SetMethodAndInstance( TMethodPointer InMethodPointer, TInstancePointer&& InInstancePointer )
        {
            SetMethod( InMethodPointer );
            SetInstance( std::forward<TInstancePointer>( InInstancePointer ) );
        }

        template<typename = std::enable_if_t<true == std::is_copy_assignable_v<TInstancePointer>>>
        ASD_FORCEINLINE void SetMethodAndInstance( TMethodPointer InMethodPointer, const TInstancePointer& InInstancePointer )
        {
            SetMethod( InMethodPointer );
            SetInstance( InInstancePointer );
        }
    };
}

namespace ASD
{
    template<typename T>
    struct TRawPointerWrapper
    {
        TRawPointerWrapper() : Pointer{ nullptr }{}
        TRawPointerWrapper( T* Pointer ) : Pointer{ Pointer }{}

        TRawPointerWrapper( const TRawPointerWrapper& Other ) : Pointer{ Other.Pointer } {}
        TRawPointerWrapper& operator=( const TRawPointerWrapper& Other ) 
        {
            Pointer = Other.Pointer;
            return *this;
        }

        TRawPointerWrapper( TRawPointerWrapper&& Other ) noexcept : Pointer{ Other.Pointer } 
        {
            Other.Pointer = nullptr;
        }

        TRawPointerWrapper& operator=( TRawPointerWrapper&& Other ) noexcept
        {
            if( this == &Other ) ASD_UNLIKELY
            {
                return *this;
            }

            Pointer = Other.Pointer;
            Other.Pointer = nullptr;

            return *this;
        }

        ASD_FORCEINLINE T* get() const 
        {
            return Pointer;
        }
        
        ASD_FORCEINLINE bool operator==( const TRawPointerWrapper& Other ) const 
        {
            return Pointer == Other.Pointer;
        }

        ASD_FORCEINLINE bool operator==( T const * Other ) const 
        {
            return Pointer == Other;
        }

        ASD_FORCEINLINE bool operator!=( T const * Other ) const 
        {
            return Pointer != Other;
        }

        T* Pointer;
    };

    template<typename TFnPtrSignature>
    using RawDelegate = DelegateBase<TRawPointerWrapper, TFnPtrSignature>;
    
    template<typename TFnPtrSignature>
    using UniqueDelegate = DelegateBase<std::unique_ptr, TFnPtrSignature>;
    
    template<typename TFnPtrSignature>
    using SharedDelegate = DelegateBase<std::shared_ptr, TFnPtrSignature>;
    
    template<typename TFnPtrSignature>
    using Delegate = RawDelegate<TFnPtrSignature>;
}

