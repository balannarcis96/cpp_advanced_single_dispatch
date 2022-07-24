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
        template<typename = std::enable_if<false == std::is_class_v<TInstancePointer>>>
        DelegateBase( TMethodPointer MethodPointer, TInstancePointer InInstancePointer ) : DelegateTraits() 
        {
            this->Pointer         = *reinterpret_cast<TFunctionPointer*>( &MethodPointer );
            this->InstancePointer = InInstancePointer;          
        }
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
        template<typename = std::enable_if<false == std::is_class_v<TInstancePointer>>>
        DelegateBase( TMethodPointer MethodPointer, TInstancePointer InInstancePointer ) : TDelegateTraits() 
        {
            this->Pointer         = *reinterpret_cast<TFunctionPointer*>( &MethodPointer );
            this->InstancePointer = InInstancePointer;          
        }
        DelegateBase( TMethodPointer MethodPointer, TInstancePointer&& InInstancePointer ) : TDelegateTraits() 
        {
            this->Pointer         = *reinterpret_cast<TFunctionPointer*>( &MethodPointer );
            this->InstancePointer = std::forward<TInstancePointer>( InInstancePointer );          
        }
#endif

        ASD_FORCEINLINE explicit operator bool() const
        {
	        return false == IsNull(  );
        }

        ASD_NODISCARD ASD_FORCEINLINE bool IsNull() const
        {
	        return nullptr == this->Pointer || nullptr == this->InstancePointer;
        }
        
        ASD_NODISCARD ASD_FORCEINLINE bool HasMethod() const
        {
	        return nullptr != this->Pointer;
        }
        
        ASD_NODISCARD ASD_FORCEINLINE bool HasInstance() const
        {
	        return nullptr != this->InstancePointer;
        }
        
        ASD_NODISCARD ASD_FORCEINLINE TMethodPointer GetMethod() const
        {
	        return this->Pointer;
        }
        
         ASD_NODISCARD ASD_FORCEINLINE TInstancePointer GetInstance() const
        {
	        return this->InstancePointer;
        }

        ASD_FORCEINLINE void SetInstance( TInstancePointer InInstancePointer )
        {
            this->InstancePointer = InInstancePointer;
        }

        ASD_NODISCARD TInstancePointer ResetInstance( TInstancePointer InInstancePtr )
        {
            TInstancePointer Temp = this->InstancePointer;
            this->InstancePointer = InInstancePtr;

            return Temp;
        }

        ASD_NODISCARD TInstancePointer ReleaseInstance()
        {
            TInstancePointer Temp = this->InstancePointer;
            this->InstancePointer = nullptr;

            return Temp;
        }

        ASD_FORCEINLINE void SetMethod( TMethodPointer InMethodPointer )
        {
            this->Pointer = *reinterpret_cast<TFunctionPointer*>( &InMethodPointer );
        }

        ASD_FORCEINLINE void SetMethodAndInstance( TMethodPointer InMethodPointer, TInstancePointer InInstancePointer )
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

        TRawPointerWrapper( const TRawPointerWrapper& Other ) = default;
        TRawPointerWrapper& operator=( const TRawPointerWrapper& Other ) = default;

        ASD_FORCEINLINE T* get() const 
        {
            return Pointer;
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

