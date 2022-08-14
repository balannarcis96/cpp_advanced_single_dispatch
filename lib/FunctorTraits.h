//!
//! \file FuctorTraits.h
//! 
//! \brief Functor class traits abstractions
//! 
//! \author Balan Narcis (balannarcis96@gmail.com)
//! 
#pragma once

#include <tuple>

#include "Utils.h"
#include "CallingConvention.h"

namespace ASD
{
    template<size_t TFunctorSize, typename TCallingConvention, typename ReturnType, typename ...Args>
    struct FuctorTraitsBase
    {
        using TReturnType                      = ReturnType;
        using TArgsTypes                       = std::tuple< Args... >;
        template<std::size_t N> using TNthArg  = std::tuple_element_t< N, TArgsTypes >;
        using CallingConvention                = TCallingConvention;

        static constexpr std::size_t ArgsCount      = sizeof...( Args );
        static constexpr std::size_t FunctorSize    = TFunctorSize;
        static constexpr bool         IsMethod      = true;
        static constexpr bool         IsDelegate    = true;

        static constexpr const char* GetCallingConventionName()
        {
            if ( std::is_same<CallingConvention, CallingConventions::Vectorcall>() && CallingConventions::HasVectorcall ) { return "vectorcall"; }
            if ( std::is_same<CallingConvention, CallingConventions::Fastcall>()   && CallingConventions::HasFastcall ) { return "fastcall"; }
            if ( std::is_same<CallingConvention, CallingConventions::Thiscall>()   && CallingConventions::HasThiscall ) { return "thiscall"; }
            if ( std::is_same<CallingConvention, CallingConventions::Stdcall>()    && CallingConventions::HasStdcall ) { return "stdcall"; }
            
            return "cdecl";
        }
    };

    //!
    //! \brief Trivial functor traits class
    //!                - performs raw copy
    //!                - does not allow move
    //!                - does not handle destruction
    //! \required The functor type must be trivial
    //! \tparam FunctorSize maximumAllowed functor size
    //!
    template<size_t FunctorSize, typename F>
    struct TrivialFuctorTraits;

    //!
    //! \brief Unique Functor traits class
    //!                - does not allow copy
    //!                - does not allow move
    //!                - handles correct destruction (calls destructor of non trivial types captured in the functor body)
    //! \tparam FunctorSize maximumAllowed functor size
    //! \tparam bStrict if true, it will not accept trivial functors
    //!
    template<size_t FunctorSize, typename F, bool bStrict>
    struct UniqueFuctorTraits;

    //!
    //! \brief Copyable Functor traits class
    //!                - allows only copy
    //!                - does not allow move
    //!                - handles correct destruction
    //! \required Copy construct/assign must be possible on the functor type
    //! \tparam FunctorSize maximumAllowed functor size
    //! \tparam bStrict if true, it will not accept trivial functors
    //!
    template<size_t FunctorSize, typename F, bool bStrict>
    struct CopyFuctorTraits;

    //!
    //! \brief Moveable Functor traits class
    //!                - does not allow copy
    //!                - allows only move
    //!                - handles correct destruction
    //! \required Move construct/assign must be possible on the functor type
    //! \tparam FunctorSize maximumAllowed functor size
    //! \tparam bStrict if true, it will not accept trivial functors
    //!
    template<size_t FunctorSize, typename F, bool bStrict>
    struct MoveFuctorTraits;
                                                                                                                                                                                                    \
#define TRIVIAL_FUNCTOR_TRAITS( NOEXCEPT_VALUE, NOEXCEPT_BOOL_VALUE )                                                                                                                               \
    template<size_t FunctorSize, typename ReturnType, typename ...Args>                                                                                                                             \
    struct TrivialFuctorTraits<FunctorSize, ReturnType( ASD_CDECL * )( Args... ) NOEXCEPT_VALUE>                                                                                                    \
        : FuctorTraitsBase<FunctorSize, CallingConventions::Cdecl, ReturnType, Args...>                                                                                                             \
    {                                                                                                                                                                                               \
        using TBase                      = FuctorTraitsBase<FunctorSize, CallingConventions::Cdecl, ReturnType, Args...>;                                                                           \
        using TPointer                   = ReturnType ( ASD_CDECL * )( void*, Args... ) NOEXCEPT_VALUE;                                                                                             \
        constexpr static bool IsNoexcept = NOEXCEPT_BOOL_VALUE;                                                                                                                                     \
        constexpr static bool IsVariadic = false;                                                                                                                                                   \
                                                                                                                                                                                                    \
        TrivialFuctorTraits() NOEXCEPT_VALUE : Pointer{ nullptr }, BodyBuffer{ 0 } {}                                                                                                               \
        TrivialFuctorTraits( const TrivialFuctorTraits& Other ) NOEXCEPT_VALUE : Pointer { Other.Pointer }                                                                                          \
        {                                                                                                                                                                                           \
            memcpy( BodyBuffer, Other.BodyBuffer, FunctorSize );                                                                                                                                    \
        }                                                                                                                                                                                           \
        TrivialFuctorTraits& operator=( const TrivialFuctorTraits& Other ) NOEXCEPT_VALUE                                                                                                           \
        {                                                                                                                                                                                           \
            Pointer = Other.Pointer;                                                                                                                                                                \
            memcpy( BodyBuffer, Other.BodyBuffer, FunctorSize );                                                                                                                                    \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        ASD_FORCEINLINE ReturnType ASD_CDECL operator()( Args... args ) const NOEXCEPT_VALUE                                                                                                        \
        {                                                                                                                                                                                           \
            if constexpr ( !std::is_void<ReturnType>() )                                                                                                                                            \
                return Pointer( BodyBuffer, std::forward<Args>( args )... );                                                                                                                        \
            else                                                                                                                                                                                    \
                Pointer( BodyBuffer, std::forward<Args>( args )... );                                                                                                                               \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        ASD_FORCEINLINE ReturnType ASD_CDECL Dispatch( Args... args ) const NOEXCEPT_VALUE                                                                                                          \
        {                                                                                                                                                                                           \
            if constexpr ( !std::is_void<ReturnType>() )                                                                                                                                            \
                return Pointer( BodyBuffer, std::forward<Args>( args )... );                                                                                                                        \
            else                                                                                                                                                                                    \
                Pointer( BodyBuffer, std::forward<Args>( args )... );                                                                                                                               \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        template<typename TFunctor>                                                                                                                                                                 \
        ASD_FORCEINLINE void operator+=( TFunctor&& lambda ) NOEXCEPT_VALUE                                                                                                                         \
        {                                                                                                                                                                                           \
            static_assert(ASD::is_functor_v<TFunctor, ReturnType( Args... ) NOEXCEPT_VALUE>, "The givent type must be a functor of the required type!");                                            \
            BuildHandler( std::forward<TFunctor>( lambda ) );                                                                                                                                       \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        template<typename TFunctor>                                                                                                                                                                 \
        ASD_FORCEINLINE void SetFunctor( TFunctor&& lambda ) NOEXCEPT_VALUE                                                                                                                         \
        {                                                                                                                                                                                           \
            static_assert(ASD::is_functor_v<TFunctor, ReturnType( Args... ) NOEXCEPT_VALUE>, "The givent type must be a functor of the required type!");                                            \
            BuildHandler( std::forward<TFunctor>( lambda ) );                                                                                                                                       \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        ASD_FORCEINLINE void Destroy() NOEXCEPT_VALUE                                                                                                                                               \
        {                                                                                                                                                                                           \
            /*no destructor to call, this is trivial object*/                                                                                                                                       \
            Pointer = nullptr;                                                                                                                                                                      \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        ASD_FORCEINLINE bool IsNull() const NOEXCEPT_VALUE                                                                                                                                          \
        {                                                                                                                                                                                           \
            return Pointer == nullptr;                                                                                                                                                              \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
    private:                                                                                                                                                                                        \
        template<typename TFunctor>                                                                                                                                                                 \
        void BuildHandler( TFunctor&& lambda ) NOEXCEPT_VALUE                                                                                                                                       \
        {                                                                                                                                                                                           \
            static_assert( asd_is_trivial_v<TFunctor>, "The provided functor (TFunctor) must be trivial copyable!" );                                                                               \
            static_assert( sizeof( TFunctor ) <= FunctorSize, "The given functor's size must be smaller or equal to FunctorSize" );                                                                 \
            static_assert( !NOEXCEPT_BOOL_VALUE || std::is_nothrow_invocable_v<TFunctor, Args...> , "The given functor's call operator must be noexexcept" );                                       \
                                                                                                                                                                                                    \
            /*Set the functor method pointer*/                                                                                                                                                      \
            auto MethodPointer = &TFunctor::operator( );                                                                                                                                            \
            Pointer = *reinterpret_cast<TPointer*>( &MethodPointer );                                                                                                                               \
                                                                                                                                                                                                    \
            /*Perform a trivial copy of the functor body*/                                                                                                                                          \
            memcpy( BodyBuffer, &lambda, sizeof( TFunctor ) );                                                                                                                                      \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
    protected:                                                                                                                                                                                      \
        TPointer        Pointer;                                                                                                                                                                    \
        mutable uint8_t BodyBuffer[FunctorSize];                                                                                                                                                    \
    };                                                                                                                            

#define UNIQUE_FUNCTOR_TRAITS( NOEXCEPT_VALUE, NOEXCEPT_BOOL_VALUE )                                                                                                                                \
    template<size_t FunctorSize, bool bStrict, typename ReturnType, typename ...Args>                                                                                                               \
    struct UniqueFuctorTraits<FunctorSize, ReturnType( ASD_CDECL * )( Args... ) NOEXCEPT_VALUE, bStrict>                                                                                            \
        : FuctorTraitsBase<FunctorSize, CallingConventions::Cdecl, ReturnType, Args...>                                                                                                             \
    {                                                                                                                                                                                               \
        using TBase                      = FuctorTraitsBase<FunctorSize, CallingConventions::Cdecl, ReturnType, Args...>;                                                                           \
        using TPointer                   = ReturnType ( ASD_CDECL * )( void*, Args... ) NOEXCEPT_VALUE;                                                                                             \
        using TDestroyHandler            = void  ( ASD_CDECL* )( void* ) NOEXCEPT_VALUE;                                                                                                            \
        constexpr static bool IsNoexcept = NOEXCEPT_BOOL_VALUE;                                                                                                                                     \
        constexpr static bool IsVariadic = false;                                                                                                                                                   \
                                                                                                                                                                                                    \
        UniqueFuctorTraits() NOEXCEPT_VALUE : Pointer{ nullptr }, DestroyPointer{ nullptr } {}                                                                                                      \
                                                                                                                                                                                                    \
        UniqueFuctorTraits( const UniqueFuctorTraits& ) = delete;                                                                                                                                   \
        UniqueFuctorTraits& operator=( const UniqueFuctorTraits& ) = delete;                                                                                                                        \
                                                                                                                                                                                                    \
        UniqueFuctorTraits( UniqueFuctorTraits&& ) = delete;                                                                                                                                        \
        UniqueFuctorTraits& operator=( UniqueFuctorTraits&& ) = delete;                                                                                                                             \
                                                                                                                                                                                                    \
        ~UniqueFuctorTraits() NOEXCEPT_VALUE                                                                                                                                                        \
        {                                                                                                                                                                                           \
            Destroy();                                                                                                                                                                              \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        ASD_FORCEINLINE ReturnType ASD_CDECL operator()( Args... args ) const NOEXCEPT_VALUE                                                                                                        \
        {                                                                                                                                                                                           \
            if constexpr ( !std::is_void<ReturnType>() )                                                                                                                                            \
                return Pointer( BodyBuffer, std::forward<Args>( args )... );                                                                                                                        \
            else                                                                                                                                                                                    \
                Pointer( BodyBuffer, std::forward<Args>( args )... );                                                                                                                               \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        ASD_FORCEINLINE ReturnType ASD_CDECL Dispatch( Args... args ) const NOEXCEPT_VALUE                                                                                                          \
        {                                                                                                                                                                                           \
            if constexpr ( !std::is_void<ReturnType>() )                                                                                                                                            \
                return Pointer( BodyBuffer, std::forward<Args>( args )... );                                                                                                                        \
            else                                                                                                                                                                                    \
                Pointer( BodyBuffer, std::forward<Args>( args )... );                                                                                                                               \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        template<typename TFunctor>                                                                                                                                                                 \
        ASD_FORCEINLINE void operator+=( TFunctor&& lambda ) NOEXCEPT_VALUE                                                                                                                         \
        {                                                                                                                                                                                           \
            static_assert(ASD::is_functor_v<TFunctor, ReturnType( Args... ) NOEXCEPT_VALUE>, "The givent type must be a functor of the required type!");                                            \
            BuildHandler( std::forward<TFunctor>( lambda ) );                                                                                                                                       \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        template<typename TFunctor>                                                                                                                                                                 \
        ASD_FORCEINLINE void SetFunctor( TFunctor&& lambda ) NOEXCEPT_VALUE                                                                                                                         \
        {                                                                                                                                                                                           \
            static_assert(ASD::is_functor_v<TFunctor, ReturnType( Args... ) NOEXCEPT_VALUE>, "The givent type must be a functor of the required type!");                                            \
            BuildHandler( std::forward<TFunctor>( lambda ) );                                                                                                                                       \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        template<typename TFunctor>                                                                                                                                                                 \
        ASD_FORCEINLINE void operator+=( const TFunctor& lambda ) NOEXCEPT_VALUE                                                                                                                    \
        {                                                                                                                                                                                           \
            static_assert(ASD::is_functor_v<std::decay_t<TFunctor>, ReturnType( Args... ) const NOEXCEPT_VALUE>, "The givent type must be a functor of the required type!");                        \
            BuildHandler( lambda );                                                                                                                                                                 \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        template<typename TFunctor>                                                                                                                                                                 \
        ASD_FORCEINLINE void SetFunctor( const TFunctor& lambda ) NOEXCEPT_VALUE                                                                                                                    \
        {                                                                                                                                                                                           \
            static_assert(ASD::is_functor_v<TFunctor, ReturnType( Args... ) NOEXCEPT_VALUE>, "The givent type must be a functor of the required type!");                                            \
            BuildHandler( lambda );                                                                                                                                                                 \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        ASD_FORCEINLINE void Destroy() NOEXCEPT_VALUE                                                                                                                                               \
        {                                                                                                                                                                                           \
            if( false == IsNull() )                                                                                                                                                                 \
            {                                                                                                                                                                                       \
                if( nullptr != DestroyPointer )                                                                                                                                                     \
                    DestroyPointer( BodyBuffer );                                                                                                                                                   \
                                                                                                                                                                                                    \
                Pointer = nullptr;                                                                                                                                                                  \
            }                                                                                                                                                                                       \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        ASD_FORCEINLINE bool IsNull() const NOEXCEPT_VALUE                                                                                                                                          \
        {                                                                                                                                                                                           \
            return Pointer == nullptr;                                                                                                                                                              \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        ASD_FORCEINLINE constexpr bool IsTrivial() const NOEXCEPT_VALUE                                                                                                                             \
        {                                                                                                                                                                                           \
            if constexpr ( true == bStrict )                                                                                                                                                        \
            {                                                                                                                                                                                       \
                return false;                                                                                                                                                                       \
            }                                                                                                                                                                                       \
            else                                                                                                                                                                                    \
            {                                                                                                                                                                                       \
                return false == IsNull() && nullptr == DestroyPointer;                                                                                                                              \
            }                                                                                                                                                                                       \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
    private:                                                                                                                                                                                        \
        template<typename TFunctor>                                                                                                                                                                 \
        void BuildHandler( TFunctor&& lambda ) NOEXCEPT_VALUE                                                                                                                                       \
        {                                                                                                                                                                                           \
            static_assert( sizeof( TFunctor ) <= FunctorSize, "The given functor's size must be smaller or equal to FunctorSize" );                                                                 \
            static_assert( !bStrict || !asd_is_trivial_v<TFunctor>, "The provided functor (TFunctor) must not be trivial, use TrivialFuctorTraits instead!" );                                      \
            static_assert( std::is_move_constructible_v<TFunctor>, "The provided Functor must be move-constructible" );                                                                             \
            static_assert( !NOEXCEPT_BOOL_VALUE || std::is_nothrow_invocable_v<TFunctor, Args...> , "The given functor's call operator must be noexexcept" );                                       \
                                                                                                                                                                                                    \
            /*Set the functor method pointer*/                                                                                                                                                      \
            auto MethodPointer = &TFunctor::operator( );                                                                                                                                            \
            Pointer = *reinterpret_cast<TPointer*>( &MethodPointer );                                                                                                                               \
                                                                                                                                                                                                    \
            if constexpr( asd_is_trivial_v<TFunctor> )                                                                                                                                              \
            {                                                                                                                                                                                       \
                /*No destructor needed, type is trivial*/                                                                                                                                           \
                DestroyPointer = nullptr;                                                                                                                                                           \
                                                                                                                                                                                                    \
                /*Perform a trivial copy of the functor body*/                                                                                                                                      \
                memcpy( BodyBuffer, &lambda, sizeof( TFunctor ) );                                                                                                                                  \
            }                                                                                                                                                                                       \
            else                                                                                                                                                                                    \
            {                                                                                                                                                                                       \
                /*Set destructor pointer (not single dispatch, but only for destruction, can't take pointer of destructor T_T)*/                                                                    \
                DestroyPointer = &DestroyStubFunction<TFunctor>;                                                                                                                                    \
                                                                                                                                                                                                    \
                /*Move construct*/                                                                                                                                                                  \
                new( BodyBuffer ) TFunctor( std::forward<TFunctor>( lambda ) );                                                                                                                     \
            }                                                                                                                                                                                       \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        template<typename TFunctor>                                                                                                                                                                 \
        void BuildHandler( const TFunctor& lambda ) NOEXCEPT_VALUE                                                                                                                                  \
        {                                                                                                                                                                                           \
            static_assert( sizeof( TFunctor ) <= FunctorSize, "The given functor's size must be smaller or equal to FunctorSize" );                                                                 \
            static_assert( !bStrict || !asd_is_trivial_v<TFunctor>, "The provided functor (TFunctor) must not be trivial, use TrivialFuctorTraits instead!" );                                      \
            static_assert( std::is_copy_constructible_v<TFunctor>, "The provided Functor must be copy-constructible" );                                                                             \
            static_assert( !NOEXCEPT_BOOL_VALUE || std::is_nothrow_destructible_v<TFunctor>, "The provided Functor must be noexcept destructible" );                                                \
            static_assert( !NOEXCEPT_BOOL_VALUE || std::is_nothrow_invocable_v<TFunctor, Args...> , "The given functor's call operator must be noexexcept" );                                       \
                                                                                                                                                                                                    \
            /*Set the functor method pointer*/                                                                                                                                                      \
            auto MethodPointer = &TFunctor::operator( );                                                                                                                                            \
            Pointer            = *reinterpret_cast<TPointer*>( &MethodPointer );                                                                                                                    \
                                                                                                                                                                                                    \
            if constexpr( asd_is_trivial_v<TFunctor> )                                                                                                                                              \
            {                                                                                                                                                                                       \
                /*No destructor needed, type is trivial*/                                                                                                                                           \
                DestroyPointer = nullptr;                                                                                                                                                           \
                                                                                                                                                                                                    \
                /*Perform a trivial copy of the functor body*/                                                                                                                                      \
                memcpy( BodyBuffer, &lambda, sizeof( TFunctor ) );                                                                                                                                  \
            }                                                                                                                                                                                       \
            else                                                                                                                                                                                    \
            {                                                                                                                                                                                       \
                /*Set destructor pointer (not single dispatch, but only for destruction, can't take pointer of destructor T_T)*/                                                                    \
                DestroyPointer = &DestroyStubFunction<TFunctor>;                                                                                                                                    \
                                                                                                                                                                                                    \
                /*Copy construct*/                                                                                                                                                                  \
                new( BodyBuffer ) TFunctor( lambda );                                                                                                                                               \
            }                                                                                                                                                                                       \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        template<typename TFunctor>                                                                                                                                                                 \
        static void DestroyStubFunction( void* Body ) NOEXCEPT_VALUE                                                                                                                                \
        {                                                                                                                                                                                           \
            reinterpret_cast<TFunctor*>( Body )->~TFunctor( );                                                                                                                                      \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
protected:                                                                                                                                                                                          \
        TPointer        Pointer;                                                                                                                                                                    \
        TDestroyHandler DestroyPointer;                                                                                                                                                             \
        mutable uint8_t BodyBuffer[FunctorSize];                                                                                                                                                    \
    };            

#define COPY_FUNCTOR_TRAITS( NOEXCEPT_VALUE, NOEXCEPT_BOOL_VALUE )                                                                                                                                  \
    template<size_t FunctorSize, bool bStrict, typename ReturnType, typename ...Args>                                                                                                               \
    struct CopyFuctorTraits<FunctorSize, ReturnType( ASD_CDECL * )( Args... ) NOEXCEPT_VALUE, bStrict>                                                                                              \
        : FuctorTraitsBase<FunctorSize, CallingConventions::Cdecl, ReturnType, Args...>                                                                                                             \
    {                                                                                                                                                                                               \
        using TBase                      = FuctorTraitsBase<FunctorSize, CallingConventions::Cdecl, ReturnType, Args...>;                                                                           \
        using TPointer                   = ReturnType ( ASD_CDECL * )( void*, Args... ) NOEXCEPT_VALUE;                                                                                             \
        using TCopyMethodPointer         = void ( ASD_CDECL* )( void*, const void* ) NOEXCEPT_VALUE;                                                                                                \
        using TDestroyHandler            = void ( ASD_CDECL* )( void* ) NOEXCEPT_VALUE;                                                                                                             \
        constexpr static bool IsNoexcept = NOEXCEPT_BOOL_VALUE;                                                                                                                                     \
        constexpr static bool IsVariadic = false;                                                                                                                                                   \
                                                                                                                                                                                                    \
        CopyFuctorTraits() NOEXCEPT_VALUE : Pointer{ nullptr }, DestroyPointer{ nullptr }, CopyMethodPointer{ nullptr } {}                                                                          \
                                                                                                                                                                                                    \
        CopyFuctorTraits( const CopyFuctorTraits& Other ) NOEXCEPT_VALUE : Pointer{ Other.Pointer }                                                                                                 \
        {                                                                                                                                                                                           \
            if( Other.IsTrivial() )                                                                                                                                                                 \
            {                                                                                                                                                                                       \
                /*no need for destroy and copy pointers*/                                                                                                                                           \
                DestroyPointer    = nullptr;                                                                                                                                                        \
                CopyMethodPointer = nullptr;                                                                                                                                                        \
                                                                                                                                                                                                    \
                /*Perform a trivial copy of the functor body*/                                                                                                                                      \
                memcpy( BodyBuffer, &Other.BodyBuffer, FunctorSize );                                                                                                                               \
            }                                                                                                                                                                                       \
            else                                                                                                                                                                                    \
            {                                                                                                                                                                                       \
                /*copy destroy and copy pointers*/                                                                                                                                                  \
                DestroyPointer    = Other.DestroyPointer;                                                                                                                                           \
                CopyMethodPointer = Other.CopyMethodPointer;                                                                                                                                        \
                                                                                                                                                                                                    \
                /*zero the body buffer*/                                                                                                                                                            \
                memset( BodyBuffer, 0, FunctorSize );                                                                                                                                               \
                                                                                                                                                                                                    \
                /*NOTE: we copy into zero initialized memory*/                                                                                                                                      \
                Other.CopyMethodPointer( BodyBuffer, Other.BodyBuffer );                                                                                                                            \
            }                                                                                                                                                                                       \
        }                                                                                                                                                                                           \
        CopyFuctorTraits& operator=( const CopyFuctorTraits& Other ) NOEXCEPT_VALUE                                                                                                                 \
        {                                                                                                                                                                                           \
            if( this == &Other )                                                                                                                                                                    \
            {                                                                                                                                                                                       \
                return *this;                                                                                                                                                                       \
            }                                                                                                                                                                                       \
                                                                                                                                                                                                    \
            /*destroy potential valid functor*/                                                                                                                                                     \
            Destroy();                                                                                                                                                                              \
                                                                                                                                                                                                    \
            /*copy pointer*/                                                                                                                                                                        \
            Pointer = Other.Pointer;                                                                                                                                                                \
                                                                                                                                                                                                    \
            if( Other.IsTrivial() )                                                                                                                                                                 \
            {                                                                                                                                                                                       \
                /*no need for destroy and copy pointers*/                                                                                                                                           \
                DestroyPointer    = nullptr;                                                                                                                                                        \
                CopyMethodPointer = nullptr;                                                                                                                                                        \
                                                                                                                                                                                                    \
                /*Perform a trivial copy of the functor body*/                                                                                                                                      \
                memcpy( BodyBuffer, &Other.BodyBuffer, FunctorSize );                                                                                                                               \
            }                                                                                                                                                                                       \
            else                                                                                                                                                                                    \
            {                                                                                                                                                                                       \
                /*copy destroy and copy pointers*/                                                                                                                                                  \
                DestroyPointer    = Other.DestroyPointer;                                                                                                                                           \
                CopyMethodPointer = Other.CopyMethodPointer;                                                                                                                                        \
                                                                                                                                                                                                    \
                /*zero the body buffer*/                                                                                                                                                            \
                memset( BodyBuffer, 0, FunctorSize );                                                                                                                                               \
                                                                                                                                                                                                    \
                /*NOTE: we copy into zero initialized memory*/                                                                                                                                      \
                CopyMethodPointer( BodyBuffer, Other.BodyBuffer );                                                                                                                                  \
            }                                                                                                                                                                                       \
                                                                                                                                                                                                    \
            return *this;                                                                                                                                                                           \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        CopyFuctorTraits( CopyFuctorTraits&& ) = delete;                                                                                                                                            \
        CopyFuctorTraits& operator=( CopyFuctorTraits&& ) = delete;                                                                                                                                 \
                                                                                                                                                                                                    \
        ASD_FORCEINLINE ReturnType ASD_CDECL operator()( Args... args ) const NOEXCEPT_VALUE                                                                                                        \
        {                                                                                                                                                                                           \
            if constexpr ( !std::is_void<ReturnType>() )                                                                                                                                            \
                return Pointer( BodyBuffer, std::forward<Args>( args )... );                                                                                                                        \
            else                                                                                                                                                                                    \
                Pointer( BodyBuffer, std::forward<Args>( args )... );                                                                                                                               \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        ASD_FORCEINLINE ReturnType ASD_CDECL Dispatch( Args... args ) const NOEXCEPT_VALUE                                                                                                          \
        {                                                                                                                                                                                           \
            if constexpr ( !std::is_void<ReturnType>() )                                                                                                                                            \
                return Pointer( BodyBuffer, std::forward<Args>( args )... );                                                                                                                        \
            else                                                                                                                                                                                    \
                Pointer( BodyBuffer, std::forward<Args>( args )... );                                                                                                                               \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        template<typename TFunctor>                                                                                                                                                                 \
        ASD_FORCEINLINE void operator+=( const TFunctor& lambda ) NOEXCEPT_VALUE                                                                                                                    \
        {                                                                                                                                                                                           \
            static_assert(ASD::is_functor_v<TFunctor, ReturnType( Args... ) NOEXCEPT_VALUE>, "The givent type must be a functor of the required type!");                                            \
            BuildHandler( lambda );                                                                                                                                                                 \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        template<typename TFunctor>                                                                                                                                                                 \
        ASD_FORCEINLINE void SetFunctor( const TFunctor& lambda ) NOEXCEPT_VALUE                                                                                                                    \
        {                                                                                                                                                                                           \
            static_assert(ASD::is_functor_v<TFunctor, ReturnType( Args... ) NOEXCEPT_VALUE>, "The givent type must be a functor of the required type!");                                            \
            BuildHandler( lambda );                                                                                                                                                                 \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        ASD_FORCEINLINE void Destroy() NOEXCEPT_VALUE                                                                                                                                               \
        {                                                                                                                                                                                           \
            if( false == IsNull() )                                                                                                                                                                 \
            {                                                                                                                                                                                       \
                if( nullptr != DestroyPointer )                                                                                                                                                     \
                    DestroyPointer( BodyBuffer );                                                                                                                                                   \
                                                                                                                                                                                                    \
                Pointer = nullptr;                                                                                                                                                                  \
            }                                                                                                                                                                                       \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        ASD_FORCEINLINE bool IsNull() const NOEXCEPT_VALUE                                                                                                                                          \
        {                                                                                                                                                                                           \
            return Pointer == nullptr;                                                                                                                                                              \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        ASD_FORCEINLINE constexpr bool IsTrivial() const NOEXCEPT_VALUE                                                                                                                             \
        {                                                                                                                                                                                           \
            if constexpr ( true == bStrict )                                                                                                                                                        \
            {                                                                                                                                                                                       \
                return false;                                                                                                                                                                       \
            }                                                                                                                                                                                       \
            else                                                                                                                                                                                    \
            {                                                                                                                                                                                       \
                return false == IsNull() && nullptr == DestroyPointer;                                                                                                                              \
            }                                                                                                                                                                                       \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
    private:                                                                                                                                                                                        \
        template<typename TFunctor>                                                                                                                                                                 \
        void BuildHandler( const TFunctor& lambda ) NOEXCEPT_VALUE                                                                                                                                  \
        {                                                                                                                                                                                           \
            static_assert( sizeof( TFunctor ) <= FunctorSize, "The given functor's size must be smaller or equal to FunctorSize" );                                                                 \
            static_assert( !bStrict || !asd_is_trivial_v<TFunctor>, "The provided functor (TFunctor) must not be trivial, use TrivialFuctorTraits instead!" );                                      \
            constexpr bool bIsCopyable = NOEXCEPT_BOOL_VALUE ?                                                                                                                                      \
                                std::is_nothrow_copy_constructible_v<TFunctor> && std::is_nothrow_copy_assignable_v<TFunctor> :                                                                     \
                                std::is_copy_constructible_v<TFunctor> && std::is_copy_assignable_v<TFunctor>;                                                                                      \
            static_assert( bIsCopyable, "The provided Functor must be copy constructible and assignable" );                                                                                         \
            static_assert( !NOEXCEPT_BOOL_VALUE || std::is_nothrow_destructible_v<TFunctor>, "The provided Functor must be noexcept destructible" );                                                \
            static_assert( !NOEXCEPT_BOOL_VALUE || std::is_nothrow_invocable_v<TFunctor, Args...> , "The given functor's call operator must be noexexcept" );                                       \
                                                                                                                                                                                                    \
            /*Set the functor method pointer*/                                                                                                                                                      \
            auto MethodPointer = &TFunctor::operator( );                                                                                                                                            \
            Pointer            = *reinterpret_cast<TPointer*>( &MethodPointer );                                                                                                                    \
                                                                                                                                                                                                    \
            if constexpr( asd_is_trivial_v<TFunctor> )                                                                                                                                              \
            {                                                                                                                                                                                       \
                /*No destructor or copy method needed, type is trivial*/                                                                                                                            \
                DestroyPointer    = nullptr;                                                                                                                                                        \
                CopyMethodPointer = nullptr;                                                                                                                                                        \
                                                                                                                                                                                                    \
                /*Perform a trivial copy of the functor body*/                                                                                                                                      \
                memcpy( BodyBuffer, &lambda, sizeof( TFunctor ) );                                                                                                                                  \
            }                                                                                                                                                                                       \
            else                                                                                                                                                                                    \
            {                                                                                                                                                                                       \
                /*Set destructor pointer (not single dispatch, but only for destruction, can't take pointer of destructor T_T)*/                                                                    \
                DestroyPointer = &DestroyStubFunction<TFunctor>;                                                                                                                                    \
                                                                                                                                                                                                    \
                /*Set copy function (not single dispatch, but only for copy, can't take pointer of copy operator T_T)*/                                                                             \
                CopyMethodPointer = &CopyStubFunction<TFunctor>;                                                                                                                                    \
                                                                                                                                                                                                    \
                /*Copy construct*/                                                                                                                                                                  \
                new( BodyBuffer ) TFunctor( lambda );                                                                                                                                               \
            }                                                                                                                                                                                       \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        template<typename TFunctor>                                                                                                                                                                 \
        static void ASD_CDECL DestroyStubFunction( void* Body ) NOEXCEPT_VALUE                                                                                                                      \
        {                                                                                                                                                                                           \
            reinterpret_cast<TFunctor*>( Body )->~TFunctor( );                                                                                                                                      \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        template<typename TFunctor>                                                                                                                                                                 \
        static void ASD_CDECL CopyStubFunction( void* Body, const void *SourceBody ) NOEXCEPT_VALUE                                                                                                 \
        {                                                                                                                                                                                           \
            /*invoke the copy assignment operator*/                                                                                                                                                 \
            *reinterpret_cast<TFunctor*>( Body ) = *reinterpret_cast<const TFunctor*>( SourceBody );                                                                                                \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
protected:                                                                                                                                                                                          \
        TPointer                 Pointer;                                                                                                                                                           \
        TDestroyHandler          DestroyPointer;                                                                                                                                                    \
        TCopyMethodPointer       CopyMethodPointer;                                                                                                                                                 \
        mutable uint8_t          BodyBuffer[FunctorSize];                                                                                                                                           \
    };        

#define MOVE_FUNCTOR_TRAITS( NOEXCEPT_VALUE, NOEXCEPT_BOOL_VALUE )                                                                                                                                  \
    template<size_t FunctorSize, bool bStrict, typename ReturnType, typename ...Args>                                                                                                               \
    struct MoveFuctorTraits<FunctorSize, ReturnType( ASD_CDECL * )( Args... ) NOEXCEPT_VALUE, bStrict>                                                                                              \
        : FuctorTraitsBase<FunctorSize, CallingConventions::Cdecl, ReturnType, Args...>                                                                                                             \
    {                                                                                                                                                                                               \
        using TBase                      = FuctorTraitsBase<FunctorSize, CallingConventions::Cdecl, ReturnType, Args...>;                                                                           \
        using TPointer                   = ReturnType ( ASD_CDECL * )( void*, Args... ) NOEXCEPT_VALUE;                                                                                             \
        using TMoveOrCopyMethodPointer   = void ( ASD_CDECL* )( void*, void* ) NOEXCEPT_VALUE;                                                                                                      \
        using TDestroyHandler            = void ( ASD_CDECL* )( void* ) NOEXCEPT_VALUE;                                                                                                             \
        constexpr static bool IsNoexcept = NOEXCEPT_BOOL_VALUE;                                                                                                                                     \
        constexpr static bool IsVariadic = false;                                                                                                                                                   \
                                                                                                                                                                                                    \
        MoveFuctorTraits() NOEXCEPT_VALUE : Pointer{ nullptr }, DestroyPointer{ nullptr }, MoveMethodPointer{ nullptr } {}                                                                          \
                                                                                                                                                                                                    \
        MoveFuctorTraits( const MoveFuctorTraits& ) = delete;                                                                                                                                       \
        MoveFuctorTraits& operator=( const MoveFuctorTraits& ) = delete;                                                                                                                            \
                                                                                                                                                                                                    \
        MoveFuctorTraits( MoveFuctorTraits&& Other ) noexcept : Pointer{ Other.Pointer }                                                                                                            \
        {                                                                                                                                                                                           \
            if( Other.IsTrivial() )                                                                                                                                                                 \
            {                                                                                                                                                                                       \
                /*no need for destroy and copy pointers*/                                                                                                                                           \
                DestroyPointer    = nullptr;                                                                                                                                                        \
                MoveMethodPointer = nullptr;                                                                                                                                                        \
                                                                                                                                                                                                    \
                /*Perform a trivial copy of the functor body*/                                                                                                                                      \
                memcpy( BodyBuffer, Other.BodyBuffer, FunctorSize );                                                                                                                                \
            }                                                                                                                                                                                       \
            else                                                                                                                                                                                    \
            {                                                                                                                                                                                       \
                /*copy destroy and move pointers*/                                                                                                                                                  \
                DestroyPointer    = Other.DestroyPointer;                                                                                                                                           \
                MoveMethodPointer = Other.MoveMethodPointer;                                                                                                                                        \
                                                                                                                                                                                                    \
                /*zero the body buffer*/                                                                                                                                                            \
                memset( BodyBuffer, 0, FunctorSize );                                                                                                                                               \
                                                                                                                                                                                                    \
                /*NOTE: we move into zero initialized memory*/                                                                                                                                      \
                Other.MoveMethodPointer( BodyBuffer, Other.BodyBuffer );                                                                                                                            \
            }                                                                                                                                                                                       \
        }                                                                                                                                                                                           \
        MoveFuctorTraits& operator=( MoveFuctorTraits&& Other ) noexcept                                                                                                                            \
        {                                                                                                                                                                                           \
            if( this == &Other )                                                                                                                                                                    \
            {                                                                                                                                                                                       \
                return *this;                                                                                                                                                                       \
            }                                                                                                                                                                                       \
                                                                                                                                                                                                    \
            /*destroy potential valid functor*/                                                                                                                                                     \
            Destroy();                                                                                                                                                                              \
                                                                                                                                                                                                    \
            /*copy pointer*/                                                                                                                                                                        \
            Pointer = Other.Pointer;                                                                                                                                                                \
                                                                                                                                                                                                    \
            if( Other.IsTrivial() )                                                                                                                                                                 \
            {                                                                                                                                                                                       \
                /*no need for destroy and copy pointers*/                                                                                                                                           \
                DestroyPointer    = nullptr;                                                                                                                                                        \
                MoveMethodPointer = nullptr;                                                                                                                                                        \
                                                                                                                                                                                                    \
                /*Perform a trivial copy of the functor body*/                                                                                                                                      \
                memcpy( BodyBuffer, Other.BodyBuffer, FunctorSize );                                                                                                                                \
            }                                                                                                                                                                                       \
            else                                                                                                                                                                                    \
            {                                                                                                                                                                                       \
                /*copy destroy and move pointers*/                                                                                                                                                  \
                DestroyPointer    = Other.DestroyPointer;                                                                                                                                           \
                MoveMethodPointer = Other.MoveMethodPointer;                                                                                                                                        \
                                                                                                                                                                                                    \
                /*zero the body buffer*/                                                                                                                                                            \
                memset( BodyBuffer, 0, FunctorSize );                                                                                                                                               \
                                                                                                                                                                                                    \
                /*NOTE: we move into zero initialized memory*/                                                                                                                                      \
                MoveMethodPointer( BodyBuffer, Other.BodyBuffer );                                                                                                                                  \
            }                                                                                                                                                                                       \
                                                                                                                                                                                                    \
            /*mark Other as null*/                                                                                                                                                                  \
            Other.Pointer = nullptr;                                                                                                                                                                \
                                                                                                                                                                                                    \
            return *this;                                                                                                                                                                           \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        ASD_FORCEINLINE ReturnType ASD_CDECL operator()( Args... args ) const NOEXCEPT_VALUE                                                                                                        \
        {                                                                                                                                                                                           \
            if constexpr ( !std::is_void<ReturnType>() )                                                                                                                                            \
                return Pointer( BodyBuffer, std::forward<Args>( args )... );                                                                                                                        \
            else                                                                                                                                                                                    \
                Pointer( BodyBuffer, std::forward<Args>( args )... );                                                                                                                               \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        ASD_FORCEINLINE ReturnType ASD_CDECL Dispatch( Args... args ) const NOEXCEPT_VALUE                                                                                                          \
        {                                                                                                                                                                                           \
            if constexpr ( !std::is_void<ReturnType>() )                                                                                                                                            \
                return Pointer( BodyBuffer, std::forward<Args>( args )... );                                                                                                                        \
            else                                                                                                                                                                                    \
                Pointer( BodyBuffer, std::forward<Args>( args )... );                                                                                                                               \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        template<typename TFunctor>                                                                                                                                                                 \
        ASD_FORCEINLINE void operator+=( TFunctor&& lambda ) NOEXCEPT_VALUE                                                                                                                         \
        {                                                                                                                                                                                           \
            static_assert(ASD::is_functor_v<TFunctor, ReturnType( Args... ) NOEXCEPT_VALUE>, "The givent type must be a functor of the required type!");                                            \
            BuildHandler( std::forward<TFunctor>( lambda ) );                                                                                                                                       \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        template<typename TFunctor>                                                                                                                                                                 \
        ASD_FORCEINLINE void SetFunctor( TFunctor&& lambda ) NOEXCEPT_VALUE                                                                                                                         \
        {                                                                                                                                                                                           \
            static_assert(ASD::is_functor_v<TFunctor, ReturnType( Args... ) NOEXCEPT_VALUE>, "The givent type must be a functor of the required type!");                                            \
            BuildHandler( std::forward<TFunctor>( lambda ) );                                                                                                                                       \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        ASD_FORCEINLINE void Destroy() NOEXCEPT_VALUE                                                                                                                                               \
        {                                                                                                                                                                                           \
            if( false == IsNull() )                                                                                                                                                                 \
            {                                                                                                                                                                                       \
                if( nullptr != DestroyPointer )                                                                                                                                                     \
                    DestroyPointer( BodyBuffer );                                                                                                                                                   \
                                                                                                                                                                                                    \
                Pointer = nullptr;                                                                                                                                                                  \
            }                                                                                                                                                                                       \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        ASD_FORCEINLINE bool IsNull() const NOEXCEPT_VALUE                                                                                                                                          \
        {                                                                                                                                                                                           \
            return Pointer == nullptr;                                                                                                                                                              \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        ASD_FORCEINLINE constexpr bool IsTrivial() const NOEXCEPT_VALUE                                                                                                                             \
        {                                                                                                                                                                                           \
            if constexpr ( true == bStrict )                                                                                                                                                        \
            {                                                                                                                                                                                       \
                return false;                                                                                                                                                                       \
            }                                                                                                                                                                                       \
            else                                                                                                                                                                                    \
            {                                                                                                                                                                                       \
                return false == IsNull() && nullptr == DestroyPointer;                                                                                                                              \
            }                                                                                                                                                                                       \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
    private:                                                                                                                                                                                        \
        template<typename TFunctor>                                                                                                                                                                 \
        void BuildHandler( TFunctor&& lambda ) NOEXCEPT_VALUE                                                                                                                                       \
        {                                                                                                                                                                                           \
            static_assert( sizeof( TFunctor ) <= FunctorSize, "The given functor's size must be smaller or equal to FunctorSize" );                                                                 \
            static_assert( !bStrict || !asd_is_trivial_v<TFunctor>, "The provided functor (TFunctor) must not be trivial, use TrivialFuctorTraits instead!" );                                      \
            constexpr bool bIsMoveable = NOEXCEPT_BOOL_VALUE ?                                                                                                                                      \
                                std::is_nothrow_move_constructible_v<TFunctor> && std::is_nothrow_move_assignable_v<TFunctor> :                                                                     \
                                std::is_move_constructible_v<TFunctor> && std::is_move_assignable_v<TFunctor>;                                                                                      \
            static_assert( bIsMoveable, "The provided Functor must be move constructible and assignable" );                                                                                         \
            static_assert( !NOEXCEPT_BOOL_VALUE || std::is_nothrow_destructible_v<TFunctor>, "The provided Functor must be noexcept destructible" );                                                \
            static_assert( !NOEXCEPT_BOOL_VALUE || std::is_nothrow_invocable_v<TFunctor, Args...> , "The given functor's call operator must be noexexcept" );                                       \
                                                                                                                                                                                                    \
            /*Set the functor method pointer*/                                                                                                                                                      \
            auto MethodPointer = &TFunctor::operator( );                                                                                                                                            \
            Pointer            = *reinterpret_cast<TPointer*>( &MethodPointer );                                                                                                                    \
                                                                                                                                                                                                    \
            if constexpr( asd_is_trivial_v<TFunctor> )                                                                                                                                              \
            {                                                                                                                                                                                       \
                /*No destructor or move method needed, type is trivial*/                                                                                                                            \
                DestroyPointer    = nullptr;                                                                                                                                                        \
                MoveMethodPointer = nullptr;                                                                                                                                                        \
                                                                                                                                                                                                    \
                /*Perform a trivial copy of the functor body*/                                                                                                                                      \
                memcpy( BodyBuffer, &lambda, sizeof( TFunctor ) );                                                                                                                                  \
            }                                                                                                                                                                                       \
            else                                                                                                                                                                                    \
            {                                                                                                                                                                                       \
                /*Set destructor pointer (not single dispatch, but only for destruction, can't take pointer of destructor T_T)*/                                                                    \
                DestroyPointer = &DestroyStubFunction<TFunctor>;                                                                                                                                    \
                                                                                                                                                                                                    \
                /*Set move function (not single dispatch, but only for copy, can't take pointer of copy operator T_T)*/                                                                             \
                MoveMethodPointer = &MoveStubFunction<TFunctor>;                                                                                                                                    \
                                                                                                                                                                                                    \
                /*Move construct*/                                                                                                                                                                  \
                new( BodyBuffer ) TFunctor( std::forward<TFunctor>( lambda ) );                                                                                                                     \
            }                                                                                                                                                                                       \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        template<typename TFunctor>                                                                                                                                                                 \
        static void ASD_CDECL DestroyStubFunction( void* Body ) NOEXCEPT_VALUE                                                                                                                      \
        {                                                                                                                                                                                           \
            reinterpret_cast<TFunctor*>( Body )->~TFunctor( );                                                                                                                                      \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
        template<typename TFunctor>                                                                                                                                                                 \
        static void ASD_CDECL MoveStubFunction( void* Body, void *SourceBody ) NOEXCEPT_VALUE                                                                                                       \
        {                                                                                                                                                                                           \
            /*invoke the move assignment operator*/                                                                                                                                                 \
            *reinterpret_cast<TFunctor*>( Body ) = std::move( *reinterpret_cast<TFunctor*>( SourceBody ) );                                                                                         \
        }                                                                                                                                                                                           \
                                                                                                                                                                                                    \
protected:                                                                                                                                                                                          \
        TPointer                 Pointer;                                                                                                                                                           \
        TDestroyHandler          DestroyPointer;                                                                                                                                                    \
        TMoveOrCopyMethodPointer MoveMethodPointer;                                                                                                                                                 \
        mutable uint8_t          BodyBuffer[FunctorSize];                                                                                                                                           \
    };    

#define ASD_EMPTY_MACRO

    TRIVIAL_FUNCTOR_TRAITS( ASD_EMPTY_MACRO, false );
    TRIVIAL_FUNCTOR_TRAITS( noexcept, true );

    UNIQUE_FUNCTOR_TRAITS( ASD_EMPTY_MACRO, false );
    UNIQUE_FUNCTOR_TRAITS( noexcept, true );

    COPY_FUNCTOR_TRAITS( ASD_EMPTY_MACRO, false );
    COPY_FUNCTOR_TRAITS( noexcept, true );

    MOVE_FUNCTOR_TRAITS( ASD_EMPTY_MACRO, false );
    MOVE_FUNCTOR_TRAITS( noexcept, true );

#undef TRIVIAL_FUNCTOR_TRAITS
#undef UNIQUE_FUNCTOR_TRAITS
#undef COPY_FUNCTOR_TRAITS
#undef MOVE_FUNCTOR_TRAITS
#undef ASD_EMPTY_MACRO
}
