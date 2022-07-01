//!
//! Advanced Single Dispatch
//!
//! \author Narcis Balan (balannarcis96@gmail.com)
//!
#pragma once

#include <type_traits>
#include <utility>
#include <memory>

#define ASD_NODISCARD [[nodiscard]]

#ifdef _MSC_VER 
#define ASD_FORCEINLINE __forceinline
#else
#define ASD_FORCEINLINE 
#endif

namespace ASD::Utils
{
    // Most reliable way (i found + edit) to check if T is a functor with a specific signature
    namespace functor
    {
        template< typename T >
        struct identity
        {
            using type = T;
        };

        template< typename... >
        using void_t = void;

        template< typename F >
        struct call_operator;

        template< typename C, typename R, typename... A >
        struct call_operator< R ( C::* )( A... ) >: identity< R( A... ) >
        {
        };

        template< typename C, typename R, typename... A >
        struct call_operator< R ( C::* )( A... ) const >: identity< R( A... ) >
        {
        };

        template< typename C, typename R, typename... A >
        struct call_operator< R ( C::* )( A... ) noexcept >: identity< R( A... ) >
        {
        };

        template< typename C, typename R, typename... A >
        struct call_operator< R ( C::* )( A... ) const noexcept >: identity< R( A... ) >
        {
        };

        template< typename F >
        using call_operator_t = typename call_operator< F >::type;

        template< typename, typename, typename = void_t<> >
        struct is_convertible_to_function
            : std::false_type
        {
        };

        template< typename L, typename TSignature >
        struct is_convertible_to_function< L, TSignature, void_t< decltype( &L::operator( ) ) > >
            : std::is_assignable< call_operator_t< decltype( &L::operator( ) ) > *&, TSignature >
        {
        };
    } // namespace lambda_ex
    
    template< typename L, typename TSignature >
    using is_functor = functor::is_convertible_to_function< L, TSignature >;

    template< typename L, typename TReturnType, typename... TArgs >
    using is_functor_f = functor::is_convertible_to_function< L, TReturnType( TArgs... ) >;

    template< typename L, typename TSignature >
    using is_lambda = is_functor< L, TSignature >;

    template< typename L, typename TReturnType, typename... TArgs >
    using is_lambda_f = is_functor_f< L, TReturnType, TArgs... >;

    class TDummy {};
}

namespace ASD
{
    template< typename TFnSignature >
    class FnPtr;

    template< typename TClass, typename TFnSignature >
    class MethodPtr;

    template< typename TClass, typename TClassPtr, typename TFnSignature >
    class DelegateBase;

    template< typename TClass, typename TFnSignature >
    class RawDelegate;

    template< typename TClass, typename TFnSignature >
    class UniqueDelegate;

    template< typename TClass, typename TFnSignature >
    class SharedDelegate;
}

namespace ASD
{
    //!
    //! Simple function pointer wrapper
    //!
    //! \details Usage: FnPtr<void( int )> ptr = DoSmth;
    //! \details sizeof( FnPtr< ... > ) == sizeof( void * )
    //!
    template< typename TReturnType, typename... TArgs >
	class FnPtr< TReturnType( TArgs... )>
	{
    public:
        using TFunctionPointer = TReturnType ( * )( TArgs... );

        FnPtr() : Pointer { nullptr } {}
        FnPtr( TFunctionPointer Pointer ) : Pointer { Pointer } {}
        
        ASD_FORCEINLINE void operator =( TFunctionPointer InPointer )
        {
            Pointer = InPointer;
        }

        ASD_FORCEINLINE TReturnType operator()( TArgs ... Args ) const
        {
			return Pointer( std::forward<TArgs>( Args )... );
        }

        ASD_FORCEINLINE explicit operator bool() const
        {
	        return false == IsNull(  );
        }

        ASD_NODISCARD bool IsNull() const
        {
	        return nullptr == Pointer;
        }
        
    private:
        TFunctionPointer Pointer;
	};
    static_assert( sizeof ( FnPtr<void(void)> ) == sizeof( void * ) );
    
    //!
    //! Simple class function pointer(method) wrapper
    //!
    //! \details Usage: MethodPtr<void( int )> ptr = &TClass::DoSmth; ptr( Instance, ... )
    //! \details sizeof( MethodPtr< ... > ) == sizeof( void * )
    //!
    template< typename TClass, typename TReturnType, typename... TArgs >
    class MethodPtr< TClass, TReturnType( TArgs ... )>
    {
    public:
        using TMethodPointer = TReturnType ( TClass::* )( TArgs ... );
        using TFunctionPointer = FnPtr< TReturnType( void*, TArgs... ) >;
	    
        MethodPtr() : Pointer { nullptr } {}
        MethodPtr( TMethodPointer Pointer ) : Pointer { *reinterpret_cast<TFunctionPointer*>( &Pointer ) } {}
	        
	    ASD_FORCEINLINE TReturnType operator()( TClass* Instance, TArgs... Args ) const
	    {
	        return Pointer( Instance, std::forward<TArgs>( Args )... );
	    }

	    ASD_FORCEINLINE TReturnType operator()( TClass& Instance, TArgs... Args ) const
	    {
	        return Pointer( &Instance, std::forward<TArgs>( Args )... );
	    }

	    ASD_FORCEINLINE void operator+=( TMethodPointer InPointer )
	    {
	        Pointer = *reinterpret_cast<TFunctionPointer*>( &InPointer );
	    }

        ASD_FORCEINLINE explicit operator bool() const
        {
	        return false == IsNull(  );
        }

        ASD_NODISCARD bool IsNull() const
        {
	        return nullptr == Pointer;
        }
        
    private:
        TFunctionPointer Pointer;
    };
    static_assert( sizeof ( MethodPtr< Utils::TDummy, void( void )> ) == sizeof( void * ) );
    
    //!
    //! Base class for all delegate types
    //!
    //! \details See RawDelegate< ... >, UniqueDelegate< ... >, SharedDelegate< ... >
    //! \details sizeof( DelegateBase< ... > ) == sizeof( void * ) * 2
    //!
    template< typename TClass, typename TClassPtr, typename TReturnType, typename... TArgs >
    class DelegateBase< TClass, TClassPtr, TReturnType( TArgs ... )>
    {
    public:
	    using TMethodPtr = MethodPtr< TClass, TReturnType( TArgs ... )>;
	    using TMethodFunctionPtr = typename TMethodPtr::TMethodPointer;
        using TPtr = TClassPtr;

        DelegateBase() : MethodPointer{ nullptr }, InstancePointer{ nullptr } {}
        DelegateBase( TMethodFunctionPtr MethodPointer ) : MethodPointer{ MethodPointer }, InstancePointer{ nullptr } {}
        DelegateBase( TMethodFunctionPtr MethodPointer, TPtr InstancePointer ) : MethodPointer{ MethodPointer }, InstancePointer{ InstancePointer } {}
        DelegateBase( TMethodFunctionPtr MethodPointer, TPtr&& InstancePointer, bool bMoveDummy ) : MethodPointer{ MethodPointer }, InstancePointer{ std::forward<TPtr>( InstancePointer ) } {}

        ASD_FORCEINLINE TReturnType operator()( TArgs ... Args ) const
        {
	        return MethodPointer( *InstancePointer, std::forward<TArgs>( Args )... );
        }
        
        ASD_FORCEINLINE TReturnType Dispatch( TArgs ... Args ) const
        {
	        return MethodPointer( *InstancePointer, std::forward<TArgs>( Args )... );
        }
        
        ASD_FORCEINLINE TReturnType Dispatch( TClass* TargetInstance, TArgs ... Args ) const
        {
	        return MethodPointer( TargetInstance, std::forward<TArgs>( Args )... );
        }
        
        ASD_FORCEINLINE TReturnType Dispatch( TClass& TargetInstance, TArgs ... Args ) const
        {
	        return MethodPointer( TargetInstance, std::forward<TArgs>( Args )... );
        }
        
        ASD_FORCEINLINE explicit operator bool() const
        {
	        return false == IsNull(  );
        }

        ASD_FORCEINLINE ASD_NODISCARD bool IsNull() const
        {
	        return nullptr == MethodPointer || nullptr == InstancePointer;
        }
        
        ASD_FORCEINLINE ASD_NODISCARD bool HasMethod() const
        {
	        return nullptr != MethodPointer;
        }
        
        ASD_FORCEINLINE ASD_NODISCARD bool HasInstance() const
        {
	        return nullptr != InstancePointer;
        }
        
        ASD_FORCEINLINE ASD_NODISCARD TMethodPtr GetMethod() const
        {
	        return MethodPointer;
        }
        
        ASD_FORCEINLINE ASD_NODISCARD TPtr GetInstance() const
        {
	        return InstancePointer;
        }

        ASD_FORCEINLINE void SetInstance( TPtr InInstancePointer )
        {
            InstancePointer = InInstancePointer;
        }

        TPtr ResetInstance( TPtr InInstancePtr )
        {
            TPtr Temp       = InstancePointer;
            InstancePointer = InInstancePtr;

            return Temp;
        }

        TPtr ReleaseInstance()
        {
            TPtr Temp       = InstancePointer;
            InstancePointer = nullptr;

            return Temp;
        }

        ASD_FORCEINLINE void SetMethod( TMethodFunctionPtr InMethodPointer )
        {
            MethodPointer = InMethodPointer;
        }

        ASD_FORCEINLINE void SetMethodAndInstance( TMethodFunctionPtr InMethodPointer, TPtr InInstancePointer )
        {
            SetMethod( InMethodPointer );
            SetInstance( InInstancePointer );
        }

    protected:
        TMethodPtr MethodPointer;
        TPtr       InstancePointer; 
    };
    static_assert( sizeof ( DelegateBase< Utils::TDummy, Utils::TDummy*, void( void )> ) == sizeof( void * ) * 2 );

    //!
    //! Raw pointer delegate. It holds a raw pointer to the instance
    //!
    //! \details RawDelegate( DelegateBase< ... > ) == sizeof( void * ) * 2
    //!
    template< typename TClass, typename TReturnType, typename... TArgs >
    class RawDelegate<TClass, TReturnType( TArgs ... )>  
        : public DelegateBase<TClass, TClass*, TReturnType( TArgs ... )>
    {
        using TBase = DelegateBase<TClass, TClass*, TReturnType( TArgs ... )>;
        using TMethodFunctionPtr = typename TBase::TMethodFunctionPtr;
        using TPtr = typename TBase::TPtr;

    public:
        RawDelegate() = default;
        RawDelegate( TMethodFunctionPtr MethodPointer ) : TBase{ MethodPointer } {}
        RawDelegate( TMethodFunctionPtr MethodPointer, TPtr InstancePointer ) : TBase{ MethodPointer, InstancePointer } {}
    };
    
    //!
    //! Unique pointer delegate. It holds an std::unique_ptr to the instance
    //!
    //! \details UniqueDelegate( DelegateBase< ... > ) == sizeof( void * ) * 2
    //!
    template< typename TClass, typename TReturnType, typename... TArgs >
    class UniqueDelegate<TClass, TReturnType( TArgs ... )>  
        : public DelegateBase<TClass, std::unique_ptr<TClass>, TReturnType( TArgs ... )>
    {
        using TBase = DelegateBase<TClass, std::unique_ptr<TClass>, TReturnType( TArgs ... )>;
        using TMethodFunctionPtr = typename TBase::TMethodFunctionPtr;
        using TPtr = typename TBase::TPtr;

    public:
        UniqueDelegate() = default;
        UniqueDelegate( TMethodFunctionPtr MethodPointer ) : TBase( MethodPointer ) {}
        UniqueDelegate( TMethodFunctionPtr MethodPointer, TClass* InstancePointer ) : TBase( MethodPointer, TPtr{ InstancePointer }, false ) {}
        UniqueDelegate( TMethodFunctionPtr MethodPointer, TPtr&& InstancePointer ) : TBase( MethodPointer, std::forward<TPtr>( InstancePointer ), false ) {}

        ASD_FORCEINLINE void SetInstance( TPtr&& InInstancePointer )
        {
            this->InstancePointer = std::forward<TPtr>( InInstancePointer );
        }

        ASD_FORCEINLINE void SetMethodAndInstance( TMethodFunctionPtr InMethodPointer, TClass* InInstancePointer )
        {
            this->SetMethod( InMethodPointer );
            SetInstance( InInstancePointer );
        }

        ASD_FORCEINLINE void SetInstance( TClass* InInstancePointer )
        {
            if( this->InstancePointer.get() != InInstancePointer )
            {
                this->InstancePointer.reset( InInstancePointer );
            }
        }

    private:
        ASD_FORCEINLINE void SetMethodAndInstance( TMethodFunctionPtr InMethodPointer, TPtr InInstancePointer )
        {
            //@TODO maybe assert(false) ?
        }
        ASD_FORCEINLINE void SetInstance( TPtr InInstancePointer )
        {
            //@TODO maybe assert(false) ?
        }
    };
    
    //!
    //! Shared pointer delegate. It holds an std::shared_ptr to the instance
    //!
    //! \details SharedDelegate( DelegateBase< ... > ) == sizeof( void * ) * 2
    //!
    template< typename TClass, typename TReturnType, typename... TArgs >
    class SharedDelegate<TClass, TReturnType( TArgs ... )>  
        : public DelegateBase<TClass, std::shared_ptr<TClass>, TReturnType( TArgs ... )>
    {
        using TBase = DelegateBase<TClass, std::shared_ptr<TClass>, TReturnType( TArgs ... )>;
        using TMethodFunctionPtr = typename TBase::TMethodFunctionPtr;
        using TPtr = typename TBase::TPtr;

    public:
        SharedDelegate() = default;
        SharedDelegate( TMethodFunctionPtr MethodPointer ) : TBase( MethodPointer ) {}
        SharedDelegate( TMethodFunctionPtr MethodPointer, TClass* InstancePointer ) : TBase( MethodPointer, TPtr{ InstancePointer }, false ) {}
        SharedDelegate( TMethodFunctionPtr MethodPointer, TPtr&& InstancePointer ) : TBase( MethodPointer, std::forward<TPtr>( InstancePointer ), false ) {}

        ASD_FORCEINLINE void SetInstance( TPtr&& InInstancePointer )
        {
            this->InstancePointer = std::forward<TPtr>( InInstancePointer );
        }

        ASD_FORCEINLINE void SetMethodAndInstancePointers( TMethodFunctionPtr InMethodPointer, const TPtr& InInstancePointer )
        {
            this->SetMethod( InMethodPointer );
            
            if( this->InstancePointer != InInstancePointer )
            {
                this->InstancePointer = InInstancePointer;
            }
        }

        ASD_FORCEINLINE void SetMethodAndInstancePointers( TMethodFunctionPtr InMethodPointer, TPtr&& InInstancePointer )
        {
            this->SetMethod( InMethodPointer );
            
            if( this->InstancePointer != InInstancePointer )
            {
                this->InstancePointer = std::forward<TPtr>( InInstancePointer );
            }
        }

    private:
        void SetMethodAndInstance( TMethodFunctionPtr InMethodPointer, TPtr InInstancePointer )
        {
            //@TODO maybe assert(false) ?
        }
    };
} //ASD