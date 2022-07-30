#pragma once

namespace FnPtrTests
{
	static int GFnPtrTestFunction( int a )
	{
		return a + 1;
	}
	
	static int ASD_CDECL GFnPtrTestFunction_Cdecl( int a )
	{
		return a + 1;
	}
	
	static int ASD_STDCALL GFnPtrTestFunction_StdCall( int a )
	{
		return a + 1;
	}
	
	static int ASD_FASTCALL GFnPtrTestFunction_FastCall( int a )
	{
		return a + 1;
	}
	
	static int ASD_VECTORCALL GFnPtrTestFunction_VectorCall( int a )
	{
		return a + 1;
	}
	
	static int GFnPtrTestFunction_Noexcept( int a ) noexcept
	{
		return a + 1;
	}
	
	static int ASD_CDECL GFnPtrTestFunction_Cdecl_Noexcept( int a ) noexcept
	{
		return a + 1;
	}
	
	static int ASD_STDCALL GFnPtrTestFunction_StdCall_Noexcept( int a ) noexcept
	{
		return a + 1;
	}
	
	static int ASD_FASTCALL GFnPtrTestFunction_FastCall_Noexcept( int a ) noexcept
	{
		return a + 1;
	}
	
	static int ASD_VECTORCALL GFnPtrTestFunction_VectorCall_Noexcept( int a ) noexcept
	{
		return a + 1;
	}

	TEST( FnPtrTests, FnPtr_DefaultCtor )
	{
		{ //default calling convention must be __cdecl
			const ASD::FnPtr<void( ASD_CDECL* )( void )> FnPtr;
			ASSERT_TRUE( true == FnPtr.IsNull() );
			ASSERT_TRUE( false == static_cast<bool>( FnPtr ) ); //operator bool()

			const ASD::FnPtr<void( ASD_CDECL* )( void ) noexcept> FnPtrNoexcept;
			ASSERT_TRUE( true == FnPtrNoexcept.IsNull() );
			ASSERT_TRUE( false == static_cast<bool>( FnPtrNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasStdcall )
		{
			const ASD::FnPtr<void( ASD_STDCALL* )( void )> FnPtr;
			ASSERT_TRUE( true == FnPtr.IsNull() );
			ASSERT_TRUE( false == static_cast<bool>( FnPtr ) ); //operator bool()

			const ASD::FnPtr<void( ASD_STDCALL* )( void ) noexcept> FnPtrNoexcept;
			ASSERT_TRUE( true == FnPtrNoexcept.IsNull() );
			ASSERT_TRUE( false == static_cast<bool>( FnPtrNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasFastcall )
		{
			const ASD::FnPtr<void( ASD_FASTCALL* )( void )> FnPtr;
			ASSERT_TRUE( true == FnPtr.IsNull() );
			ASSERT_TRUE( false == static_cast<bool>( FnPtr ) ); //operator bool()

			const ASD::FnPtr<void( ASD_FASTCALL* )( void ) noexcept> FnPtrNoexcept;
			ASSERT_TRUE( true == FnPtrNoexcept.IsNull() );
			ASSERT_TRUE( false == static_cast<bool>( FnPtrNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasVectorcall )
		{
			const ASD::FnPtr<void( ASD_VECTORCALL* )( void )> FnPtr;
			ASSERT_TRUE( true == FnPtr.IsNull() );
			ASSERT_TRUE( false == static_cast<bool>( FnPtr ) ); //operator bool()

			const ASD::FnPtr<void( ASD_VECTORCALL* )( void ) noexcept> FnPtrNoexcept;
			ASSERT_TRUE( true == FnPtrNoexcept.IsNull() );
			ASSERT_TRUE( false == static_cast<bool>( FnPtrNoexcept ) ); //operator bool()
		}
	}

	TEST( FnPtrTests, FnPtr_CustomCtor )
	{
		{ //default calling convention must be __cdecl
			const ASD::FnPtr<int( ASD_CDECL* )( int )> FnPtr { GFnPtrTestFunction };
			ASSERT_TRUE( false == FnPtr.IsNull() );
			ASSERT_TRUE( true == static_cast<bool>( FnPtr ) ); //operator bool()
			
			const ASD::FnPtr<int( ASD_CDECL* )( int ) noexcept> FnPtrNoexcept { GFnPtrTestFunction_Noexcept };
			ASSERT_TRUE( false == FnPtr.IsNull() );
			ASSERT_TRUE( true == static_cast<bool>( FnPtr ) ); //operator bool()
		}

		if constexpr( ASD::CallingConventions::HasStdcall )
		{
			const ASD::FnPtr<int( ASD_STDCALL* )( int )> FnPtr { GFnPtrTestFunction_StdCall };
			ASSERT_TRUE( false == FnPtr.IsNull() );
			ASSERT_TRUE( true == static_cast<bool>( FnPtr ) ); //operator bool()
			
			const ASD::FnPtr<int( ASD_STDCALL* )( int ) noexcept> FnPtrNoexcept { GFnPtrTestFunction_StdCall_Noexcept };
			ASSERT_TRUE( false == FnPtr.IsNull() );
			ASSERT_TRUE( true == static_cast<bool>( FnPtr ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasFastcall )
		{
			const ASD::FnPtr<int( ASD_FASTCALL* )( int )> FnPtr { GFnPtrTestFunction_FastCall };
			ASSERT_TRUE( false == FnPtr.IsNull() );
			ASSERT_TRUE( true == static_cast<bool>( FnPtr ) ); //operator bool()
			
			const ASD::FnPtr<int( ASD_FASTCALL* )( int ) noexcept> FnPtrNoexcept { GFnPtrTestFunction_FastCall_Noexcept };
			ASSERT_TRUE( false == FnPtr.IsNull() );
			ASSERT_TRUE( true == static_cast<bool>( FnPtr ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasVectorcall )
		{
			const ASD::FnPtr<int( ASD_VECTORCALL* )( int )> FnPtr { GFnPtrTestFunction_VectorCall };
			ASSERT_TRUE( false == FnPtr.IsNull() );
			ASSERT_TRUE( true == static_cast<bool>( FnPtr ) ); //operator bool()
			
			const ASD::FnPtr<int( ASD_VECTORCALL* )( int ) noexcept> FnPtrNoexcept { GFnPtrTestFunction_VectorCall_Noexcept };
			ASSERT_TRUE( false == FnPtr.IsNull() );
			ASSERT_TRUE( true == static_cast<bool>( FnPtr ) ); //operator bool()
		}
	}

	TEST( FnPtrTests, FnPtr_AssignmentOperator )
	{
		ASD::FnPtr<int( ASD_CDECL* )( int )> FnPtr;

		ASSERT_TRUE( true == FnPtr.IsNull(  ) );
		ASSERT_TRUE( false == static_cast<bool>( FnPtr ) ); //operator bool()

		FnPtr = GFnPtrTestFunction;

		ASSERT_TRUE( false == FnPtr.IsNull(  ) );
		ASSERT_TRUE( true == static_cast<bool>( FnPtr ) ); //operator bool()
		
		ASD::FnPtr<int( ASD_CDECL* )( int ) noexcept> FnPtrNoexcept;

		ASSERT_TRUE( true == FnPtrNoexcept.IsNull(  ) );
		ASSERT_TRUE( false == static_cast<bool>( FnPtrNoexcept ) ); //operator bool()

		FnPtrNoexcept = GFnPtrTestFunction_Noexcept;

		ASSERT_TRUE( false == FnPtrNoexcept.IsNull(  ) );
		ASSERT_TRUE( true == static_cast<bool>( FnPtrNoexcept ) ); //operator bool()
	}
	
	TEST( FnPtrTests, FnPtr_ValueTest )
	{
		ASD::FnPtr<int( ASD_CDECL* )( int )> FnPtr;

		ASSERT_TRUE( true == FnPtr.IsNull(  ) );
		ASSERT_TRUE( false == static_cast<bool>( FnPtr ) ); //operator bool()
		ASSERT_TRUE( FnPtr == nullptr ); //operator ==

		FnPtr = GFnPtrTestFunction;

		ASSERT_TRUE( false == FnPtr.IsNull(  ) );
		ASSERT_TRUE( true == static_cast<bool>( FnPtr ) ); //operator bool()
		ASSERT_TRUE( FnPtr == GFnPtrTestFunction ); //operator ==

		ASD::FnPtr<int( ASD_CDECL* )( int ) noexcept> FnPtrNoexcept;

		ASSERT_TRUE( true == FnPtrNoexcept.IsNull(  ) );
		ASSERT_TRUE( false == static_cast<bool>( FnPtrNoexcept ) ); //operator bool()
		ASSERT_TRUE( FnPtrNoexcept == nullptr ); //operator ==

		FnPtrNoexcept = GFnPtrTestFunction_Noexcept;

		ASSERT_TRUE( false == FnPtrNoexcept.IsNull(  ) );
		ASSERT_TRUE( true == static_cast<bool>( FnPtrNoexcept ) ); //operator bool()
		ASSERT_TRUE( FnPtrNoexcept == GFnPtrTestFunction_Noexcept ); //operator ==
	}

	TEST( FnPtrTests, FnPtr_CallOperator )
	{
		ASD::FnPtr<int( ASD_CDECL* )( int )> FnPtr;

		ASSERT_TRUE( true == FnPtr.IsNull(  ) );
		ASSERT_TRUE( false == static_cast<bool>( FnPtr ) ); //operator bool()

		FnPtr = GFnPtrTestFunction;

		ASSERT_TRUE( false == FnPtr.IsNull(  ) );
		ASSERT_TRUE( true == static_cast<bool>( FnPtr ) ); //operator bool()

		const int DirectResult = GFnPtrTestFunction( 1 );
		const int PtrResult = FnPtr( 1 );

		ASSERT_EQ( DirectResult, PtrResult );

		ASD::FnPtr<int( ASD_CDECL* )( int )> FnPtrNoexcept;

		ASSERT_TRUE( true == FnPtrNoexcept.IsNull(  ) );
		ASSERT_TRUE( false == static_cast<bool>( FnPtrNoexcept ) ); //operator bool()

		FnPtrNoexcept = GFnPtrTestFunction_Noexcept;

		ASSERT_TRUE( false == FnPtrNoexcept.IsNull(  ) );
		ASSERT_TRUE( true == static_cast<bool>( FnPtrNoexcept ) ); //operator bool()

		const int DirectResult_Noexcept = GFnPtrTestFunction_Noexcept( 1 );
		const int PtrResult_Noexcept = FnPtrNoexcept( 1 );

		ASSERT_EQ( DirectResult_Noexcept, PtrResult_Noexcept );
	}
}
