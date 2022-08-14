//!
//! \file FunctorWrapper.h
//! 
//! \brief Functor instance wrapper
//! 
//! \author Balan Narcis (balannarcis96@gmail.com)
//! 
#pragma once

#include "FunctorTraits.h"

namespace ASD
{
    //!
    //! \brief Trivial functor wrapper
    //!                - performs raw copy
    //!                - does not allow move
    //!                - does not handle destruction
    //! \required The functor type must be trivial
    //! \tparam FunctorSize maximumAllowed functor size
    //!
    template<size_t FunctorSize, typename FunctorSignature>
    using TrivialFunctorWrapper = TrivialFuctorTraits<FunctorSize, FunctorSignature>;

    //!
    //! \brief Unique functor wrapper
    //!                - does not allow copy
    //!                - does not allow move
    //!                - handles correct destruction (calls destructor of non trivial types captured in the functor body)
    //! \tparam FunctorSize maximumAllowed functor size
    //! \tparam bStrict if true, it will not accept trivial functors
    //!
    template<size_t FunctorSize, typename FunctorSignature, bool bStrict = false>
    using UniqueFunctorWrapper = UniqueFuctorTraits<FunctorSize, FunctorSignature, bStrict>;

    //!
    //! \brief Copyable functor wrapper
    //!                - allows only copy
    //!                - does not allow move
    //!                - handles correct destruction
    //! \required Copy construct/assign must be possible on the functor type
    //! \tparam FunctorSize maximumAllowed functor size
    //! \tparam bStrict if true, it will not accept trivial functors
    //!
    template<size_t FunctorSize, typename FunctorSignature, bool bStrict = false>
    using CopyFunctorWrapper = CopyFuctorTraits<FunctorSize, FunctorSignature, bStrict>;

    //!
    //! \brief Moveable functor wrapper
    //!                - does not allow copy
    //!                - allows only move
    //!                - handles correct destruction
    //! \required Move construct/assign must be possible on the functor type
    //! \tparam FunctorSize maximumAllowed functor size
    //! \tparam bStrict if true, it will not accept trivial functors
    //!
    template<size_t FunctorSize, typename FunctorSignature, bool bStrict = false>
    using MoveFunctorWrapper = MoveFuctorTraits<FunctorSize, FunctorSignature, bStrict>;
}
