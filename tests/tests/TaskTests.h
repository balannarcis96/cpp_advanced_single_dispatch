#pragma once

namespace TaskTests
{
    struct MyType
    {
        int a { 0 };
    };

    TEST( TaskTests, Task_Construct_Destruct )
    {
        auto SPtr = std::make_shared<MyType>();
        ASSERT_TRUE( SPtr.use_count() == 1 );
        
        {
            ASD::Task<24> NewTask;
            bool bIsFromBase = false;

            NewTask += [ SPtr, &bIsFromBase ]() noexcept -> void
            {
                if( bIsFromBase )
                    puts("[ITask]This is from the task!");
                else
                    puts("[ Task]This is from the task!");
            };

            ASSERT_TRUE( SPtr.use_count() == 2 );

            NewTask.Dispatch();
            NewTask.Dispatch();
            NewTask.Dispatch();

            ASD::ITask* TaskBase = &NewTask;

            bIsFromBase = true;
            
            // dispatch through base!
            TaskBase->Dispatch();
            TaskBase->Dispatch();
            TaskBase->Dispatch();

            ASSERT_TRUE( SPtr.use_count() == 2 );

            TaskBase->Clear();

            ASSERT_TRUE( SPtr.use_count() == 1 );
        }
       
        ASSERT_TRUE( SPtr.use_count() == 1 );
    }
}
