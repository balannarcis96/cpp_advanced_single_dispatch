#pragma once

namespace FnPtrTests
{
	static int GFnPtrTestFunction( int a )
	{
		return a + 1;
	}

	TEST( FnPtrTests, FnPtr_DefaultCtor )
	{
		const ASD::FnPtr<void(void)> FnPtr;

		ASSERT_TRUE( true == FnPtr.IsNull(  ) );
		ASSERT_TRUE( false == static_cast<bool>( FnPtr ) ); //operator bool()
	}

	TEST( FnPtrTests, FnPtr_CustomCtor )
	{
		const ASD::FnPtr<int(int)> FnPtr = { GFnPtrTestFunction };

		ASSERT_TRUE( false == FnPtr.IsNull(  ) );
		ASSERT_TRUE( true == static_cast<bool>( FnPtr ) ); //operator bool()
	}

	TEST( FnPtrTests, FnPtr_AssignmentOperator )
	{
		ASD::FnPtr<int(int)> FnPtr;

		ASSERT_TRUE( true == FnPtr.IsNull(  ) );
		ASSERT_TRUE( false == static_cast<bool>( FnPtr ) ); //operator bool()

		FnPtr = GFnPtrTestFunction;

		ASSERT_TRUE( false == FnPtr.IsNull(  ) );
		ASSERT_TRUE( true == static_cast<bool>( FnPtr ) ); //operator bool()
	}
	
	TEST( FnPtrTests, FnPtr_ValueTest )
	{
		ASD::FnPtr<int(int)> FnPtr;

		ASSERT_TRUE( true == FnPtr.IsNull(  ) );
		ASSERT_TRUE( false == static_cast<bool>( FnPtr ) ); //operator bool()
		ASSERT_TRUE( FnPtr == nullptr ); //operator ==

		FnPtr = GFnPtrTestFunction;

		ASSERT_TRUE( false == FnPtr.IsNull(  ) );
		ASSERT_TRUE( true == static_cast<bool>( FnPtr ) ); //operator bool()
		ASSERT_TRUE( FnPtr == GFnPtrTestFunction ); //operator ==
	}

	TEST( FnPtrTests, FnPtr_CallOperator )
	{
		ASD::FnPtr<int(int)> FnPtr;

		ASSERT_TRUE( true == FnPtr.IsNull(  ) );
		ASSERT_TRUE( false == static_cast<bool>( FnPtr ) ); //operator bool()

		FnPtr = GFnPtrTestFunction;

		ASSERT_TRUE( false == FnPtr.IsNull(  ) );
		ASSERT_TRUE( true == static_cast<bool>( FnPtr ) ); //operator bool()

		const int DirectResult = GFnPtrTestFunction( 1 );
		const int PtrResult = FnPtr( 1 );

		ASSERT_EQ( DirectResult, PtrResult );
	}
}
