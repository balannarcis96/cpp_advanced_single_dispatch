#pragma once

namespace RawDelegateTests
{
	class MyClass
	{
	public:
		int DoSmth( int a )
		{
			return a + 1 + ( AdditionalValue * static_cast<int>( bEnableCustomBehavior ) );
		}
		
		int ASD_STDCALL DoSmth_StdCall( int a )
		{
			return a + 1 + ( AdditionalValue * static_cast<int>( bEnableCustomBehavior ) );
		}

		int ASD_THISCALL DoSmth_ThisCall( int a )
		{
			return a + 1 + ( AdditionalValue * static_cast<int>( bEnableCustomBehavior ) );
		}
		
		int ASD_FASTCALL DoSmth_FastCall( int a )
		{
			return a + 1 + ( AdditionalValue * static_cast<int>( bEnableCustomBehavior ) );
		}

		int ASD_VECTORCALL DoSmth_VectorCall( int a )
		{
			return a + 1 + ( AdditionalValue * static_cast<int>( bEnableCustomBehavior ) );
		}
		
		int ASD_STDCALL DoSmth_StdCall_Noexcept( int a ) noexcept
		{
			return a + 1 + ( AdditionalValue * static_cast<int>( bEnableCustomBehavior ) );
		}
		
		int DoSmth_Noexcept( int a ) noexcept
		{
			return a + 1 + ( AdditionalValue * static_cast<int>( bEnableCustomBehavior ) );
		}

		int ASD_THISCALL DoSmth_ThisCall_Noexcept( int a ) noexcept
		{
			return a + 1 + ( AdditionalValue * static_cast<int>( bEnableCustomBehavior ) );
		}
		
		int ASD_FASTCALL DoSmth_FastCall_Noexcept( int a ) noexcept
		{
			return a + 1 + ( AdditionalValue * static_cast<int>( bEnableCustomBehavior ) );
		}

		int ASD_VECTORCALL DoSmth_VectorCall_Noexcept( int a ) noexcept
		{
			return a + 1 + ( AdditionalValue * static_cast<int>( bEnableCustomBehavior ) );
		}

		int  AdditionalValue       { 0 };
		bool bEnableCustomBehavior { false };
	};

	TEST( RawDelegateTests, RawDelegate_DefaultCtor )
	{
		{
			const ASD::RawDelegate<void( ASD_CDECL MyClass::* )( void )> RawDelegate;
			ASSERT_TRUE( true == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegate ) ); //operator bool()
			
			const ASD::RawDelegate<void( ASD_CDECL MyClass::* )( void ) noexcept> RawDelegateNoexcept;
			ASSERT_TRUE( true == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
		}

		if constexpr( ASD::CallingConventions::HasThiscall )
		{
			const ASD::RawDelegate<void( ASD_THISCALL MyClass::* )( void )> RawDelegate;
			ASSERT_TRUE( true == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegate ) ); //operator bool()
			
			const ASD::RawDelegate<void( ASD_THISCALL MyClass::* )( void ) noexcept> RawDelegateNoexcept;
			ASSERT_TRUE( true == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasStdcall )
		{
			const ASD::RawDelegate<void( ASD_STDCALL MyClass::* )( void )> RawDelegate;
			ASSERT_TRUE( true == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegate ) ); //operator bool()
			
			const ASD::RawDelegate<void( ASD_STDCALL MyClass::* )( void ) noexcept> RawDelegateNoexcept;
			ASSERT_TRUE( true == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasFastcall )
		{
			const ASD::RawDelegate<void( ASD_FASTCALL MyClass::* )( void )> RawDelegate;
			ASSERT_TRUE( true == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegate ) ); //operator bool()
			
			const ASD::RawDelegate<void( ASD_FASTCALL MyClass::* )( void ) noexcept> RawDelegateNoexcept;
			ASSERT_TRUE( true == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasVectorcall )
		{
			const ASD::RawDelegate<void( ASD_VECTORCALL MyClass::* )( void )> RawDelegate;
			ASSERT_TRUE( true == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegate ) ); //operator bool()
			
			const ASD::RawDelegate<void( ASD_VECTORCALL MyClass::* )( void ) noexcept> RawDelegateNoexcept;
			ASSERT_TRUE( true == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
		}
	}
	
	TEST( RawDelegateTests, RawDelegate_CustomCtor )
	{
		MyClass MyClassInstance;

		{
			const ASD::RawDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate{ &MyClass::DoSmth, &MyClassInstance };
			ASSERT_TRUE( false == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegate ) ); //operator bool()
			
			const ASD::RawDelegate<int( ASD_CDECL MyClass::* )( int ) noexcept> RawDelegateNoexcept{ &MyClass::DoSmth_Noexcept, &MyClassInstance };
			ASSERT_TRUE( false == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
		}

		if constexpr( ASD::CallingConventions::HasThiscall )
		{
			const ASD::RawDelegate<int( ASD_THISCALL MyClass::* )( int )> RawDelegate{ &MyClass::DoSmth_ThisCall, &MyClassInstance };
			ASSERT_TRUE( false == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegate ) ); //operator bool()
			
			const ASD::RawDelegate<int( ASD_THISCALL MyClass::* )( int ) noexcept> RawDelegateNoexcept{ &MyClass::DoSmth_ThisCall_Noexcept, &MyClassInstance };
			ASSERT_TRUE( false == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasStdcall )
		{
			const ASD::RawDelegate<int( ASD_STDCALL MyClass::* )( int )> RawDelegate{ &MyClass::DoSmth_StdCall, &MyClassInstance };
			ASSERT_TRUE( false == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegate ) ); //operator bool()
			
			const ASD::RawDelegate<int( ASD_STDCALL MyClass::* )( int ) noexcept> RawDelegateNoexcept{ &MyClass::DoSmth_StdCall_Noexcept, &MyClassInstance };
			ASSERT_TRUE( false == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasFastcall )
		{
			const ASD::RawDelegate<int( ASD_FASTCALL MyClass::* )( int )> RawDelegate{ &MyClass::DoSmth_FastCall, &MyClassInstance };
			ASSERT_TRUE( false == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegate ) ); //operator bool()
			
			const ASD::RawDelegate<int( ASD_FASTCALL MyClass::* )( int ) noexcept> RawDelegateNoexcept{ &MyClass::DoSmth_FastCall_Noexcept, &MyClassInstance };
			ASSERT_TRUE( false == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasVectorcall )
		{
			const ASD::RawDelegate<int( ASD_VECTORCALL MyClass::* )( int )> RawDelegate{ &MyClass::DoSmth_VectorCall, &MyClassInstance };
			ASSERT_TRUE( false == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegate ) ); //operator bool()
			
			const ASD::RawDelegate<int( ASD_VECTORCALL MyClass::* )( int ) noexcept> RawDelegateNoexcept{ &MyClass::DoSmth_VectorCall_Noexcept, &MyClassInstance };
			ASSERT_TRUE( false == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
		}
	}
	
	TEST( RawDelegateTests, RawDelegate_AssignmentOperator )
	{
		MyClass MyClassInstance;

		{
			ASD::RawDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate;
			ASSERT_TRUE( true == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegate ) ); //operator bool()
			RawDelegate.SetMethodAndInstance( &MyClass::DoSmth, &MyClassInstance );
			ASSERT_TRUE( false == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegate ) ); //operator bool()
			
			ASD::RawDelegate<int( ASD_CDECL MyClass::* )( int ) noexcept> RawDelegateNoexcept;
			ASSERT_TRUE( true == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
			RawDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_Noexcept, &MyClassInstance );
			ASSERT_TRUE( false == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
		}

		if constexpr( ASD::CallingConventions::HasThiscall )
		{
			ASD::RawDelegate<int( ASD_THISCALL MyClass::* )( int )> RawDelegate;
			ASSERT_TRUE( true == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegate ) ); //operator bool()
			RawDelegate.SetMethodAndInstance( &MyClass::DoSmth_ThisCall, &MyClassInstance );
			ASSERT_TRUE( false == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegate ) ); //operator bool()
			
			ASD::RawDelegate<int( ASD_THISCALL MyClass::* )( int ) noexcept> RawDelegateNoexcept;
			ASSERT_TRUE( true == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
			RawDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_ThisCall_Noexcept, &MyClassInstance );
			ASSERT_TRUE( false == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasStdcall )
		{
			ASD::RawDelegate<int( ASD_STDCALL MyClass::* )( int )> RawDelegate;
			ASSERT_TRUE( true == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegate ) ); //operator bool()
			RawDelegate.SetMethodAndInstance( &MyClass::DoSmth_StdCall, &MyClassInstance );
			ASSERT_TRUE( false == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegate ) ); //operator bool()
			
			ASD::RawDelegate<int( ASD_STDCALL MyClass::* )( int ) noexcept> RawDelegateNoexcept;
			ASSERT_TRUE( true == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
			RawDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_StdCall_Noexcept, &MyClassInstance );
			ASSERT_TRUE( false == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasFastcall )
		{
			ASD::RawDelegate<int( ASD_FASTCALL MyClass::* )( int )> RawDelegate;
			ASSERT_TRUE( true == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegate ) ); //operator bool()
			RawDelegate.SetMethodAndInstance( &MyClass::DoSmth_FastCall, &MyClassInstance );
			ASSERT_TRUE( false == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegate ) ); //operator bool()
			
			ASD::RawDelegate<int( ASD_FASTCALL MyClass::* )( int ) noexcept> RawDelegateNoexcept;
			ASSERT_TRUE( true == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
			RawDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_FastCall_Noexcept, &MyClassInstance );
			ASSERT_TRUE( false == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasVectorcall )
		{
			ASD::RawDelegate<int( ASD_VECTORCALL MyClass::* )( int )> RawDelegate;
			ASSERT_TRUE( true == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegate ) ); //operator bool()
			RawDelegate.SetMethodAndInstance( &MyClass::DoSmth_VectorCall, &MyClassInstance );
			ASSERT_TRUE( false == RawDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegate ) ); //operator bool()
			
			ASD::RawDelegate<int( ASD_VECTORCALL MyClass::* )( int ) noexcept> RawDelegateNoexcept;
			ASSERT_TRUE( true == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
			RawDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_VectorCall_Noexcept, &MyClassInstance );
			ASSERT_TRUE( false == RawDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( RawDelegateNoexcept ) ); //operator bool()
		}
	}
	
	TEST( RawDelegateTests, RawDelegate_API )
	{
		MyClass MyClassInstance{ 0, false };

		ASD::RawDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate;
		ASSERT_TRUE( RawDelegate.GetInstance() == nullptr );
		ASSERT_EQ( nullptr, RawDelegate.GetMethod() );
		ASSERT_EQ( false, RawDelegate.HasMethod() );
		ASSERT_EQ( false, RawDelegate.HasInstance() );
		ASSERT_EQ( true, RawDelegate.IsNull() );

		RawDelegate.SetMethodAndInstance( &MyClass::DoSmth, &MyClassInstance );
		ASSERT_TRUE( RawDelegate.GetInstance() == &MyClassInstance );
		ASSERT_EQ( &MyClass::DoSmth, RawDelegate.GetMethod() );
		ASSERT_EQ( true, RawDelegate.HasMethod() );
		ASSERT_EQ( true, RawDelegate.HasInstance() );
		ASSERT_EQ( false, RawDelegate.IsNull() );

		RawDelegate.SetMethodAndInstance( nullptr, nullptr );
		ASSERT_TRUE( RawDelegate.GetInstance() == nullptr );
		ASSERT_EQ( nullptr, RawDelegate.GetMethod() );
		ASSERT_EQ( false, RawDelegate.HasMethod() );
		ASSERT_EQ( false, RawDelegate.HasInstance() );
		ASSERT_EQ( true, RawDelegate.IsNull() );

		RawDelegate.SetInstance( &MyClassInstance );
		ASSERT_TRUE( RawDelegate.GetInstance() == &MyClassInstance );
		ASSERT_EQ( nullptr, RawDelegate.GetMethod() );
		ASSERT_EQ( false, RawDelegate.HasMethod() );
		ASSERT_EQ( true, RawDelegate.HasInstance() );
		ASSERT_EQ( true, RawDelegate.IsNull() );
		
		RawDelegate.SetMethod( &MyClass::DoSmth );
		ASSERT_TRUE( RawDelegate.GetInstance() == &MyClassInstance );
		ASSERT_EQ( &MyClass::DoSmth, RawDelegate.GetMethod() );
		ASSERT_EQ( true, RawDelegate.HasMethod() );
		ASSERT_EQ( true, RawDelegate.HasInstance() );
		ASSERT_EQ( false, RawDelegate.IsNull() );

		RawDelegate.SetInstance( nullptr );
		RawDelegate.SetMethod( nullptr );
		ASSERT_TRUE( RawDelegate.GetInstance() == nullptr );
		ASSERT_EQ( nullptr, RawDelegate.GetMethod() );
		ASSERT_EQ( false, RawDelegate.HasMethod() );
		ASSERT_EQ( false, RawDelegate.HasInstance() );
		ASSERT_EQ( true, RawDelegate.IsNull() );

		ASSERT_TRUE( RawDelegate.ReleaseInstance() == nullptr );
		ASSERT_TRUE( RawDelegate.ResetInstance( &MyClassInstance ) == nullptr );
		ASSERT_TRUE( RawDelegate.GetInstance() == &MyClassInstance );
		ASSERT_TRUE( RawDelegate.ReleaseInstance() == &MyClassInstance );
		ASSERT_TRUE( RawDelegate.GetInstance() == nullptr );
		ASSERT_TRUE( RawDelegate.ReleaseInstance() == nullptr );
		ASSERT_EQ( false, RawDelegate.HasMethod() );
		ASSERT_EQ( false, RawDelegate.HasInstance() );
		ASSERT_EQ( true, RawDelegate.IsNull() );
	}

	TEST( RawDelegateTests, RawDelegate_Dispatch )
	{
		MyClass MyClassInstance{ 0, false };

		{
			ASD::RawDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate;
			RawDelegate.SetMethodAndInstance( &MyClass::DoSmth, &MyClassInstance );
			auto Result = RawDelegate.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = RawDelegate.Dispatch( MyClassInstance, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = RawDelegate.Dispatch( &MyClassInstance, 3 );
			ASSERT_TRUE( Result == 4 );
			
			ASD::RawDelegate<int( ASD_CDECL MyClass::* )( int ) noexcept> RawDelegateNoexcept;
			RawDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_Noexcept, &MyClassInstance );
			Result = RawDelegateNoexcept.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = RawDelegateNoexcept.Dispatch( MyClassInstance, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = RawDelegateNoexcept.Dispatch( &MyClassInstance, 3 );
			ASSERT_TRUE( Result == 4 );
		}

		if constexpr( ASD::CallingConventions::HasThiscall )
		{
			ASD::RawDelegate<int( ASD_THISCALL MyClass::* )( int )> RawDelegate;
			RawDelegate.SetMethodAndInstance( &MyClass::DoSmth_ThisCall, &MyClassInstance );
			auto Result = RawDelegate.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = RawDelegate.Dispatch( MyClassInstance, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = RawDelegate.Dispatch( &MyClassInstance, 3 );
			ASSERT_TRUE( Result == 4 );
			
			ASD::RawDelegate<int( ASD_THISCALL MyClass::* )( int ) noexcept> RawDelegateNoexcept;
			RawDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_ThisCall_Noexcept, &MyClassInstance );
			Result = RawDelegateNoexcept.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = RawDelegateNoexcept.Dispatch( MyClassInstance, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = RawDelegateNoexcept.Dispatch( &MyClassInstance, 3 );
			ASSERT_TRUE( Result == 4 );
		}
		
		if constexpr( ASD::CallingConventions::HasStdcall )
		{
			ASD::RawDelegate<int( ASD_STDCALL MyClass::* )( int )> RawDelegate;
			RawDelegate.SetMethodAndInstance( &MyClass::DoSmth_StdCall, &MyClassInstance );
			auto Result = RawDelegate.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = RawDelegate.Dispatch( MyClassInstance, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = RawDelegate.Dispatch( &MyClassInstance, 3 );
			ASSERT_TRUE( Result == 4 );
			
			ASD::RawDelegate<int( ASD_STDCALL MyClass::* )( int ) noexcept> RawDelegateNoexcept;
			RawDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_StdCall_Noexcept, &MyClassInstance );
			Result = RawDelegateNoexcept.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = RawDelegateNoexcept.Dispatch( MyClassInstance, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = RawDelegateNoexcept.Dispatch( &MyClassInstance, 3 );
			ASSERT_TRUE( Result == 4 );
		}
		
		if constexpr( ASD::CallingConventions::HasFastcall )
		{
			ASD::RawDelegate<int( ASD_FASTCALL MyClass::* )( int )> RawDelegate;
			RawDelegate.SetMethodAndInstance( &MyClass::DoSmth_FastCall, &MyClassInstance );
			auto Result = RawDelegate.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = RawDelegate.Dispatch( MyClassInstance, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = RawDelegate.Dispatch( &MyClassInstance, 3 );
			ASSERT_TRUE( Result == 4 );
			
			ASD::RawDelegate<int( ASD_FASTCALL MyClass::* )( int ) noexcept> RawDelegateNoexcept;
			RawDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_FastCall_Noexcept, &MyClassInstance );
			Result = RawDelegateNoexcept.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = RawDelegateNoexcept.Dispatch( MyClassInstance, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = RawDelegateNoexcept.Dispatch( &MyClassInstance, 3 );
			ASSERT_TRUE( Result == 4 );
		}
		
		if constexpr( ASD::CallingConventions::HasVectorcall )
		{
			ASD::RawDelegate<int( ASD_VECTORCALL MyClass::* )( int )> RawDelegate;
			RawDelegate.SetMethodAndInstance( &MyClass::DoSmth_VectorCall, &MyClassInstance );
			auto Result = RawDelegate.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = RawDelegate.Dispatch( MyClassInstance, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = RawDelegate.Dispatch( &MyClassInstance, 3 );
			ASSERT_TRUE( Result == 4 );
			
			ASD::RawDelegate<int( ASD_VECTORCALL MyClass::* )( int ) noexcept> RawDelegateNoexcept;
			RawDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_VectorCall_Noexcept, &MyClassInstance );
			Result = RawDelegateNoexcept.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = RawDelegateNoexcept.Dispatch( MyClassInstance, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = RawDelegateNoexcept.Dispatch( &MyClassInstance, 3 );
			ASSERT_TRUE( Result == 4 );
		}
	}
	
	TEST( RawDelegateTests, RawDelegate_AllCustomCtors )
	{
		MyClass MyClassInstance{ 0, false };
		
		{
			ASD::RawDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate { &MyClass::DoSmth };

			ASSERT_TRUE( RawDelegate.GetInstance() == nullptr );
			ASSERT_EQ( &MyClass::DoSmth, RawDelegate.GetMethod() );
			ASSERT_EQ( true, RawDelegate.HasMethod() );
			ASSERT_EQ( false, RawDelegate.HasInstance() );
			ASSERT_EQ( true, RawDelegate.IsNull() );
		}

		{
			ASD::RawDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate { &MyClass::DoSmth, &MyClassInstance };

			ASSERT_TRUE( RawDelegate.GetInstance() == &MyClassInstance );
			ASSERT_EQ( &MyClass::DoSmth, RawDelegate.GetMethod() );
			ASSERT_EQ( true, RawDelegate.HasMethod() );
			ASSERT_EQ( true, RawDelegate.HasInstance() );
			ASSERT_EQ( false, RawDelegate.IsNull() );
		}
	}

	TEST( RawDelegateTests, RawDelegate_Copy )
	{
		MyClass MyClassInstance{ 0, false };
		
		{
			const ASD::RawDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate { &MyClass::DoSmth, &MyClassInstance };
			const ASD::RawDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate2 { RawDelegate };

			ASSERT_TRUE( RawDelegate.GetInstance() == RawDelegate2.GetInstance() );
			ASSERT_TRUE( RawDelegate.GetMethod() == RawDelegate2.GetMethod() );
		}

		{
			const ASD::RawDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate { &MyClass::DoSmth, &MyClassInstance };
			ASD::RawDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate2 { };

			RawDelegate2 = RawDelegate;

			ASSERT_TRUE( RawDelegate.GetInstance() == RawDelegate2.GetInstance() );
			ASSERT_TRUE( RawDelegate.GetMethod() == RawDelegate2.GetMethod() );
		}
	}
	
	TEST( RawDelegateTests, RawDelegate_Move )
	{
		MyClass MyClassInstance{ 0, false };

		{
			ASD::RawDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate { &MyClass::DoSmth, &MyClassInstance };
			ASSERT_TRUE( RawDelegate.GetInstance() == &MyClassInstance );
			ASSERT_EQ( &MyClass::DoSmth, RawDelegate.GetMethod() );

			const ASD::RawDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate2 { std::move( RawDelegate ) };
		
			ASSERT_TRUE( RawDelegate.IsNull() );
			ASSERT_TRUE( RawDelegate2.GetInstance() == &MyClassInstance );
			ASSERT_EQ( RawDelegate2.GetMethod(), &MyClass::DoSmth );
		}

		{
			ASD::RawDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate { &MyClass::DoSmth, &MyClassInstance };
			ASSERT_TRUE( RawDelegate.GetInstance() == &MyClassInstance );
			ASSERT_EQ( &MyClass::DoSmth, RawDelegate.GetMethod() );

			ASD::RawDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate2;

			RawDelegate2 = std::move( RawDelegate );
		
			ASSERT_TRUE( RawDelegate.IsNull() );
			ASSERT_TRUE( RawDelegate2.GetInstance() == &MyClassInstance );
			ASSERT_EQ( RawDelegate2.GetMethod(), &MyClass::DoSmth );
		}
	}
}
