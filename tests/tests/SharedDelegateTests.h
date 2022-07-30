#pragma once

namespace SharedDelegateTests
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

	TEST( SharedDelegateTests, SharedDelegate_DefaultCtor )
	{
		{
			const ASD::SharedDelegate<void( ASD_CDECL MyClass::* )( void )> SharedDelegate;
			ASSERT_TRUE( true == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegate ) ); //operator bool()
			
			const ASD::SharedDelegate<void( ASD_CDECL MyClass::* )( void ) noexcept> SharedDelegateNoexcept;
			ASSERT_TRUE( true == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
		}

		if constexpr( ASD::CallingConventions::HasThiscall )
		{
			const ASD::SharedDelegate<void( ASD_THISCALL MyClass::* )( void )> SharedDelegate;
			ASSERT_TRUE( true == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegate ) ); //operator bool()
			
			const ASD::SharedDelegate<void( ASD_THISCALL MyClass::* )( void ) noexcept> SharedDelegateNoexcept;
			ASSERT_TRUE( true == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasStdcall )
		{
			const ASD::SharedDelegate<void( ASD_STDCALL MyClass::* )( void )> SharedDelegate;
			ASSERT_TRUE( true == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegate ) ); //operator bool()
			
			const ASD::SharedDelegate<void( ASD_STDCALL MyClass::* )( void ) noexcept> SharedDelegateNoexcept;
			ASSERT_TRUE( true == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasFastcall )
		{
			const ASD::SharedDelegate<void( ASD_FASTCALL MyClass::* )( void )> SharedDelegate;
			ASSERT_TRUE( true == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegate ) ); //operator bool()
			
			const ASD::SharedDelegate<void( ASD_FASTCALL MyClass::* )( void ) noexcept> SharedDelegateNoexcept;
			ASSERT_TRUE( true == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasVectorcall )
		{
			const ASD::SharedDelegate<void( ASD_VECTORCALL MyClass::* )( void )> SharedDelegate;
			ASSERT_TRUE( true == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegate ) ); //operator bool()
			
			const ASD::SharedDelegate<void( ASD_VECTORCALL MyClass::* )( void ) noexcept> SharedDelegateNoexcept;
			ASSERT_TRUE( true == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
		}
	}
	
	TEST( SharedDelegateTests, SharedDelegate_CustomCtor )
	{
		auto MyClassInstance = std::make_shared<MyClass>();

		{
			const ASD::SharedDelegate<int( ASD_CDECL MyClass::* )( int )> SharedDelegate{ &MyClass::DoSmth, MyClassInstance };
			ASSERT_TRUE( false == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegate ) ); //operator bool()
			
			const ASD::SharedDelegate<int( ASD_CDECL MyClass::* )( int ) noexcept> SharedDelegateNoexcept{ &MyClass::DoSmth_Noexcept, MyClassInstance };
			ASSERT_TRUE( false == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
		}

		if constexpr( ASD::CallingConventions::HasThiscall )
		{
			const ASD::SharedDelegate<int( ASD_THISCALL MyClass::* )( int )> SharedDelegate{ &MyClass::DoSmth_ThisCall, MyClassInstance };
			ASSERT_TRUE( false == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegate ) ); //operator bool()
			
			const ASD::SharedDelegate<int( ASD_THISCALL MyClass::* )( int ) noexcept> SharedDelegateNoexcept{ &MyClass::DoSmth_ThisCall_Noexcept, MyClassInstance };
			ASSERT_TRUE( false == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasStdcall )
		{
			const ASD::SharedDelegate<int( ASD_STDCALL MyClass::* )( int )> SharedDelegate{ &MyClass::DoSmth_StdCall, MyClassInstance };
			ASSERT_TRUE( false == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegate ) ); //operator bool()
			
			const ASD::SharedDelegate<int( ASD_STDCALL MyClass::* )( int ) noexcept> SharedDelegateNoexcept{ &MyClass::DoSmth_StdCall_Noexcept, MyClassInstance };
			ASSERT_TRUE( false == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasFastcall )
		{
			const ASD::SharedDelegate<int( ASD_FASTCALL MyClass::* )( int )> SharedDelegate{ &MyClass::DoSmth_FastCall, MyClassInstance };
			ASSERT_TRUE( false == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegate ) ); //operator bool()
			
			const ASD::SharedDelegate<int( ASD_FASTCALL MyClass::* )( int ) noexcept> SharedDelegateNoexcept{ &MyClass::DoSmth_FastCall_Noexcept, MyClassInstance };
			ASSERT_TRUE( false == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasVectorcall )
		{
			const ASD::SharedDelegate<int( ASD_VECTORCALL MyClass::* )( int )> SharedDelegate{ &MyClass::DoSmth_VectorCall, MyClassInstance };
			ASSERT_TRUE( false == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegate ) ); //operator bool()
			
			const ASD::SharedDelegate<int( ASD_VECTORCALL MyClass::* )( int ) noexcept> SharedDelegateNoexcept{ &MyClass::DoSmth_VectorCall_Noexcept, MyClassInstance };
			ASSERT_TRUE( false == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
		}
	}
	
	TEST( SharedDelegateTests, SharedDelegate_AssignmentOperator )
	{
		auto MyClassInstance = std::make_shared<MyClass>();

		{
			ASD::SharedDelegate<int( ASD_CDECL MyClass::* )( int )> SharedDelegate;
			ASSERT_TRUE( true == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegate ) ); //operator bool()
			SharedDelegate.SetMethodAndInstance( &MyClass::DoSmth, MyClassInstance );
			ASSERT_TRUE( false == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegate ) ); //operator bool()
			
			ASD::SharedDelegate<int( ASD_CDECL MyClass::* )( int ) noexcept> SharedDelegateNoexcept;
			ASSERT_TRUE( true == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
			SharedDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_Noexcept, MyClassInstance );
			ASSERT_TRUE( false == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
		}

		if constexpr( ASD::CallingConventions::HasThiscall )
		{
			ASD::SharedDelegate<int( ASD_THISCALL MyClass::* )( int )> SharedDelegate;
			ASSERT_TRUE( true == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegate ) ); //operator bool()
			SharedDelegate.SetMethodAndInstance( &MyClass::DoSmth_ThisCall, MyClassInstance );
			ASSERT_TRUE( false == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegate ) ); //operator bool()
			
			ASD::SharedDelegate<int( ASD_THISCALL MyClass::* )( int ) noexcept> SharedDelegateNoexcept;
			ASSERT_TRUE( true == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
			SharedDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_ThisCall_Noexcept, MyClassInstance );
			ASSERT_TRUE( false == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasStdcall )
		{
			ASD::SharedDelegate<int( ASD_STDCALL MyClass::* )( int )> SharedDelegate;
			ASSERT_TRUE( true == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegate ) ); //operator bool()
			SharedDelegate.SetMethodAndInstance( &MyClass::DoSmth_StdCall, MyClassInstance );
			ASSERT_TRUE( false == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegate ) ); //operator bool()
			
			ASD::SharedDelegate<int( ASD_STDCALL MyClass::* )( int ) noexcept> SharedDelegateNoexcept;
			ASSERT_TRUE( true == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
			SharedDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_StdCall_Noexcept, MyClassInstance );
			ASSERT_TRUE( false == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasFastcall )
		{
			ASD::SharedDelegate<int( ASD_FASTCALL MyClass::* )( int )> SharedDelegate;
			ASSERT_TRUE( true == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegate ) ); //operator bool()
			SharedDelegate.SetMethodAndInstance( &MyClass::DoSmth_FastCall, MyClassInstance );
			ASSERT_TRUE( false == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegate ) ); //operator bool()
			
			ASD::SharedDelegate<int( ASD_FASTCALL MyClass::* )( int ) noexcept> SharedDelegateNoexcept;
			ASSERT_TRUE( true == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
			SharedDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_FastCall_Noexcept, MyClassInstance );
			ASSERT_TRUE( false == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasVectorcall )
		{
			ASD::SharedDelegate<int( ASD_VECTORCALL MyClass::* )( int )> SharedDelegate;
			ASSERT_TRUE( true == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegate ) ); //operator bool()
			SharedDelegate.SetMethodAndInstance( &MyClass::DoSmth_VectorCall, MyClassInstance );
			ASSERT_TRUE( false == SharedDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegate ) ); //operator bool()
			
			ASD::SharedDelegate<int( ASD_VECTORCALL MyClass::* )( int ) noexcept> SharedDelegateNoexcept;
			ASSERT_TRUE( true == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
			SharedDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_VectorCall_Noexcept, MyClassInstance );
			ASSERT_TRUE( false == SharedDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( SharedDelegateNoexcept ) ); //operator bool()
		}
	}
	
	TEST( SharedDelegateTests, SharedDelegate_API )
	{
		auto MyClassInstance = std::make_shared<MyClass>();

		ASD::SharedDelegate<int( ASD_CDECL MyClass::* )( int )> SharedDelegate;
		ASSERT_TRUE( SharedDelegate.GetInstance() == nullptr );
		ASSERT_EQ( nullptr, SharedDelegate.GetMethod() );
		ASSERT_EQ( false, SharedDelegate.HasMethod() );
		ASSERT_EQ( false, SharedDelegate.HasInstance() );
		ASSERT_EQ( true, SharedDelegate.IsNull() );

		SharedDelegate.SetMethodAndInstance( &MyClass::DoSmth, MyClassInstance );
		ASSERT_TRUE( SharedDelegate.GetInstance() == MyClassInstance.get() );
		ASSERT_EQ( &MyClass::DoSmth, SharedDelegate.GetMethod() );
		ASSERT_EQ( true, SharedDelegate.HasMethod() );
		ASSERT_EQ( true, SharedDelegate.HasInstance() );
		ASSERT_EQ( false, SharedDelegate.IsNull() );
		
		SharedDelegate.SetMethodAndInstance( &MyClass::DoSmth, std::make_shared<MyClass>() );
		ASSERT_TRUE( SharedDelegate.GetInstance() != nullptr );
		ASSERT_TRUE( SharedDelegate.GetInstancePtr().use_count() == 2 );
		ASSERT_EQ( &MyClass::DoSmth, SharedDelegate.GetMethod() );
		ASSERT_EQ( true, SharedDelegate.HasMethod() );
		ASSERT_EQ( true, SharedDelegate.HasInstance() );
		ASSERT_EQ( false, SharedDelegate.IsNull() );

		SharedDelegate.SetMethodAndInstance( nullptr, nullptr );
		ASSERT_TRUE( SharedDelegate.GetInstance() == nullptr );
		ASSERT_EQ( nullptr, SharedDelegate.GetMethod() );
		ASSERT_EQ( false, SharedDelegate.HasMethod() );
		ASSERT_EQ( false, SharedDelegate.HasInstance() );
		ASSERT_EQ( true, SharedDelegate.IsNull() );

		SharedDelegate.SetInstance( MyClassInstance );
		ASSERT_TRUE( SharedDelegate.GetInstance() == MyClassInstance.get() );
		ASSERT_EQ( nullptr, SharedDelegate.GetMethod() );
		ASSERT_EQ( false, SharedDelegate.HasMethod() );
		ASSERT_EQ( true, SharedDelegate.HasInstance() );
		ASSERT_EQ( true, SharedDelegate.IsNull() );
		
		SharedDelegate.SetMethod( &MyClass::DoSmth );
		ASSERT_TRUE( SharedDelegate.GetInstance() == MyClassInstance.get() );
		ASSERT_EQ( &MyClass::DoSmth, SharedDelegate.GetMethod() );
		ASSERT_EQ( true, SharedDelegate.HasMethod() );
		ASSERT_EQ( true, SharedDelegate.HasInstance() );
		ASSERT_EQ( false, SharedDelegate.IsNull() );

		SharedDelegate.SetInstance( nullptr );
		SharedDelegate.SetMethod( nullptr );
		ASSERT_TRUE( SharedDelegate.GetInstance() == nullptr );
		ASSERT_EQ( nullptr, SharedDelegate.GetMethod() );
		ASSERT_EQ( false, SharedDelegate.HasMethod() );
		ASSERT_EQ( false, SharedDelegate.HasInstance() );
		ASSERT_EQ( true, SharedDelegate.IsNull() );

		ASSERT_TRUE( SharedDelegate.ReleaseInstance() == nullptr );
		ASSERT_TRUE( SharedDelegate.ResetInstance( MyClassInstance ) == nullptr );
		ASSERT_TRUE( SharedDelegate.GetInstance() == MyClassInstance.get() );
		ASSERT_TRUE( SharedDelegate.ReleaseInstance() == MyClassInstance );
		ASSERT_TRUE( SharedDelegate.GetInstance() == nullptr );
		ASSERT_TRUE( SharedDelegate.ReleaseInstance() == nullptr );
		ASSERT_EQ( false, SharedDelegate.HasMethod() );
		ASSERT_EQ( false, SharedDelegate.HasInstance() );
		ASSERT_EQ( true, SharedDelegate.IsNull() );
	}

	TEST( SharedDelegateTests, SharedDelegate_Dispatch )
	{
		auto MyClassInstance = std::make_shared<MyClass>();
		MyClass MyClassInstance2 { 0, false };

		{
			ASD::SharedDelegate<int( ASD_CDECL MyClass::* )( int )> SharedDelegate;
			SharedDelegate.SetMethodAndInstance( &MyClass::DoSmth, MyClassInstance );
			auto Result = SharedDelegate.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = SharedDelegate.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = SharedDelegate.Dispatch( MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
			
			ASD::SharedDelegate<int( ASD_CDECL MyClass::* )( int ) noexcept> SharedDelegateNoexcept;
			SharedDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_Noexcept, MyClassInstance );
			Result = SharedDelegateNoexcept.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = SharedDelegateNoexcept.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = SharedDelegateNoexcept.Dispatch( MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
		}

		if constexpr( ASD::CallingConventions::HasThiscall )
		{
			ASD::SharedDelegate<int( ASD_THISCALL MyClass::* )( int )> SharedDelegate;
			SharedDelegate.SetMethodAndInstance( &MyClass::DoSmth_ThisCall, MyClassInstance );
			auto Result = SharedDelegate.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = SharedDelegate.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = SharedDelegate.Dispatch( MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
			
			ASD::SharedDelegate<int( ASD_THISCALL MyClass::* )( int ) noexcept> SharedDelegateNoexcept;
			SharedDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_ThisCall_Noexcept, MyClassInstance );
			Result = SharedDelegateNoexcept.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = SharedDelegateNoexcept.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = SharedDelegateNoexcept.Dispatch( MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
		}
		
		if constexpr( ASD::CallingConventions::HasStdcall )
		{
			ASD::SharedDelegate<int( ASD_STDCALL MyClass::* )( int )> SharedDelegate;
			SharedDelegate.SetMethodAndInstance( &MyClass::DoSmth_StdCall, MyClassInstance );
			auto Result = SharedDelegate.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = SharedDelegate.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = SharedDelegate.Dispatch( MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
			
			ASD::SharedDelegate<int( ASD_STDCALL MyClass::* )( int ) noexcept> SharedDelegateNoexcept;
			SharedDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_StdCall_Noexcept, MyClassInstance );
			Result = SharedDelegateNoexcept.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = SharedDelegateNoexcept.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = SharedDelegateNoexcept.Dispatch( MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
		}
		
		if constexpr( ASD::CallingConventions::HasFastcall )
		{
			ASD::SharedDelegate<int( ASD_FASTCALL MyClass::* )( int )> SharedDelegate;
			SharedDelegate.SetMethodAndInstance( &MyClass::DoSmth_FastCall, MyClassInstance );
			auto Result = SharedDelegate.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = SharedDelegate.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = SharedDelegate.Dispatch( MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
			
			ASD::SharedDelegate<int( ASD_FASTCALL MyClass::* )( int ) noexcept> SharedDelegateNoexcept;
			SharedDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_FastCall_Noexcept, MyClassInstance );
			Result = SharedDelegateNoexcept.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = SharedDelegateNoexcept.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = SharedDelegateNoexcept.Dispatch( MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
		}
		
		if constexpr( ASD::CallingConventions::HasVectorcall )
		{
			ASD::SharedDelegate<int( ASD_VECTORCALL MyClass::* )( int )> SharedDelegate;
			SharedDelegate.SetMethodAndInstance( &MyClass::DoSmth_VectorCall, MyClassInstance );
			auto Result = SharedDelegate.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = SharedDelegate.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = SharedDelegate.Dispatch( MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
			
			ASD::SharedDelegate<int( ASD_VECTORCALL MyClass::* )( int ) noexcept> SharedDelegateNoexcept;
			SharedDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_VectorCall_Noexcept, MyClassInstance );
			Result = SharedDelegateNoexcept.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = SharedDelegateNoexcept.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = SharedDelegateNoexcept.Dispatch( MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
		}
	}
	
	TEST( SharedDelegateTests, SharedDelegate_AllCustomCtors )
	{
		auto MyClassInstance = std::make_shared<MyClass>();
		
		{
			ASD::SharedDelegate<int( ASD_CDECL MyClass::* )( int )> SharedDelegate { &MyClass::DoSmth };

			ASSERT_TRUE( SharedDelegate.GetInstance() == nullptr );
			ASSERT_EQ( &MyClass::DoSmth, SharedDelegate.GetMethod() );
			ASSERT_EQ( true, SharedDelegate.HasMethod() );
			ASSERT_EQ( false, SharedDelegate.HasInstance() );
			ASSERT_EQ( true, SharedDelegate.IsNull() );
		}

		{
			ASD::SharedDelegate<int( ASD_CDECL MyClass::* )( int )> SharedDelegate { &MyClass::DoSmth, MyClassInstance };

			ASSERT_TRUE( SharedDelegate.GetInstance() == MyClassInstance.get() );
			ASSERT_EQ( &MyClass::DoSmth, SharedDelegate.GetMethod() );
			ASSERT_EQ( true, SharedDelegate.HasMethod() );
			ASSERT_EQ( true, SharedDelegate.HasInstance() );
			ASSERT_EQ( false, SharedDelegate.IsNull() );
		}

		{
			ASD::SharedDelegate<int( ASD_CDECL MyClass::* )( int )> SharedDelegate { &MyClass::DoSmth, std::make_shared<MyClass>() };

			ASSERT_TRUE( SharedDelegate.GetInstance() != nullptr );
			ASSERT_EQ( &MyClass::DoSmth, SharedDelegate.GetMethod() );
			ASSERT_EQ( true, SharedDelegate.HasMethod() );
			ASSERT_EQ( true, SharedDelegate.HasInstance() );
			ASSERT_EQ( false, SharedDelegate.IsNull() );
		}
	}

	TEST( SharedDelegateTests, SharedDelegate_Copy )
	{
		auto MyClassInstance = std::make_shared<MyClass>();
		
		{
			const ASD::SharedDelegate<int( ASD_CDECL MyClass::* )( int )> SharedDelegate { &MyClass::DoSmth, MyClassInstance };
			const ASD::SharedDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate2 { SharedDelegate };

			ASSERT_TRUE( SharedDelegate.GetInstance() == RawDelegate2.GetInstance() );
			ASSERT_TRUE( SharedDelegate.GetMethod() == RawDelegate2.GetMethod() );
		}

		{
			const ASD::SharedDelegate<int( ASD_CDECL MyClass::* )( int )> SharedDelegate { &MyClass::DoSmth, MyClassInstance };
			ASD::SharedDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate2 { };

			RawDelegate2 = SharedDelegate;

			ASSERT_TRUE( SharedDelegate.GetInstance() == RawDelegate2.GetInstance() );
			ASSERT_TRUE( SharedDelegate.GetMethod() == RawDelegate2.GetMethod() );
		}
	}
	
	TEST( SharedDelegateTests, SharedDelegate_Move )
	{
		auto MyClassInstance = std::make_shared<MyClass>();

		{
			ASD::SharedDelegate<int( ASD_CDECL MyClass::* )( int )> SharedDelegate { &MyClass::DoSmth, MyClassInstance };
			ASSERT_TRUE( SharedDelegate.GetInstance() == MyClassInstance.get() );
			ASSERT_EQ( &MyClass::DoSmth, SharedDelegate.GetMethod() );

			const ASD::SharedDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate2 { std::move( SharedDelegate ) };
		
			ASSERT_TRUE( SharedDelegate.IsNull() );
			ASSERT_TRUE( RawDelegate2.GetInstance() == MyClassInstance.get() );
			ASSERT_EQ( RawDelegate2.GetMethod(), &MyClass::DoSmth );
		}

		{
			ASD::SharedDelegate<int( ASD_CDECL MyClass::* )( int )> SharedDelegate { &MyClass::DoSmth, MyClassInstance };
			ASSERT_TRUE( SharedDelegate.GetInstance() == MyClassInstance.get() );
			ASSERT_EQ( &MyClass::DoSmth, SharedDelegate.GetMethod() );

			ASD::SharedDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate2;

			RawDelegate2 = std::move( SharedDelegate );
		
			ASSERT_TRUE( SharedDelegate.IsNull() );
			ASSERT_TRUE( RawDelegate2.GetInstance() == MyClassInstance.get() );
			ASSERT_EQ( RawDelegate2.GetMethod(), &MyClass::DoSmth );
		}
	}
}
