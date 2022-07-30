//!
//! \file Utils.h
//! 
//! \brief macros, utility functions and types
//! 
//! \author Balan Narcis (balannarcis96@gmail.com)
//! 
#pragma once

#include <type_traits>

#if defined(__GNUC__) || defined(__clang__)
	#define ASD_FORCEINLINE __attribute__((always_inline))
#elif defined(_MSC_VER) || defined(__INTEL_COMPILER)
	#define ASD_FORCEINLINE __forceinline
#else
	#define ASD_FORCEINLINE 
#endif

//c++17 and latter
#define ASD_NODISCARD [[nodiscard]]

#if __cplusplus > 201703 
#define ASD_UNLIKELY [[unlikely]]
#define ASD_LIKELY [[likely]]
#else
#define ASD_UNLIKELY 
#define ASD_LIKELY
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
}
