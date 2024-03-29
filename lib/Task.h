//!
//! \file Task.h
//! 
//! \brief single leve dispatched task abstraction
//! 
//! \author Balan Narcis (balannarcis96@gmail.com)
//! 
#pragma once

namespace ASD
{
    constexpr size_t CTaskMinimumSize = 1;
    
    //! 
    //! \brief Single level dispatched task
    //! 
    //! \important Do not temper! Any modifications that will affect sizeof(ITask) will break the task abstraction.
    //! 
    struct ITask
    {   
        using TDispatchFunctionPtr = void( ASD_CDECL* )() noexcept;
        using TDispatchProto       = UniqueFunctorWrapper<CTaskMinimumSize, TDispatchFunctionPtr>;

        ITask() = default;
        ~ITask() noexcept 
        {
            Clear();
        }

        //! 
        //! \brief Dispatch this task
        //! 
        ASD_FORCEINLINE void Dispatch() const noexcept
        {
            //ASD_ASSERT( false == IsNull() );
            CastSelfToProto().Dispatch();
        }
        
        //! 
        //! Is this task valid
        //! 
        ASD_FORCEINLINE bool IsNull() const noexcept
        {
            return CastSelfToProto().IsNull();
        }

        //! 
        //! Clear the underlying functor
        //! 
        ASD_FORCEINLINE void Clear() noexcept
        {
            CastSelfToProto().Destroy();
        }

    protected:
        const TDispatchProto& CastSelfToProto() const noexcept
        {
            return *reinterpret_cast<const TDispatchProto*>( this );
        }

        TDispatchProto& CastSelfToProto() noexcept
        {
            return *reinterpret_cast<TDispatchProto*>( this );
        }
    };

    template<size_t TaskSize>
    struct Task : ITask
    {
        using TDispatch = ASD::UniqueFunctorWrapper<TaskSize, typename ITask::TDispatchFunctionPtr>;

        Task() noexcept = default;
        ~Task() noexcept = default;
        
        //! 
        //! Set the functor for this task
        //! 
        template<typename TFunctor>
        ASD_FORCEINLINE void operator+=( TFunctor&& InFunctor ) noexcept
        {
            // set the dispatch functor
            OnDispatch += std::forward<TFunctor>( InFunctor );
        }

    private:
        TDispatch OnDispatch; //!< The functor to dispatch for this task
    };
}