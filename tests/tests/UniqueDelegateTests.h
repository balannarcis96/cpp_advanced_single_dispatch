#pragma once

namespace UniqueDelegateTests
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

	TEST( UniqueDelegateTests, UniqueDelegate_DefaultCtor )
	{
		{
			const ASD::UniqueDelegate<void( ASD_CDECL MyClass::* )( void )> UniqueDelegate;
			ASSERT_TRUE( true == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			
			const ASD::UniqueDelegate<void( ASD_CDECL MyClass::* )( void ) noexcept> UniqueDelegateNoexcept;
			ASSERT_TRUE( true == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
		}

		if constexpr( ASD::CallingConventions::HasThiscall )
		{
			const ASD::UniqueDelegate<void( ASD_THISCALL MyClass::* )( void )> UniqueDelegate;
			ASSERT_TRUE( true == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			
			const ASD::UniqueDelegate<void( ASD_THISCALL MyClass::* )( void ) noexcept> UniqueDelegateNoexcept;
			ASSERT_TRUE( true == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasStdcall )
		{
			const ASD::UniqueDelegate<void( ASD_STDCALL MyClass::* )( void )> UniqueDelegate;
			ASSERT_TRUE( true == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			
			const ASD::UniqueDelegate<void( ASD_STDCALL MyClass::* )( void ) noexcept> UniqueDelegateNoexcept;
			ASSERT_TRUE( true == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasFastcall )
		{
			const ASD::UniqueDelegate<void( ASD_FASTCALL MyClass::* )( void )> UniqueDelegate;
			ASSERT_TRUE( true == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			
			const ASD::UniqueDelegate<void( ASD_FASTCALL MyClass::* )( void ) noexcept> UniqueDelegateNoexcept;
			ASSERT_TRUE( true == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasVectorcall )
		{
			const ASD::UniqueDelegate<void( ASD_VECTORCALL MyClass::* )( void )> UniqueDelegate;
			ASSERT_TRUE( true == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			
			const ASD::UniqueDelegate<void( ASD_VECTORCALL MyClass::* )( void ) noexcept> UniqueDelegateNoexcept;
			ASSERT_TRUE( true == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
		}
	}
	
	TEST( UniqueDelegateTests, UniqueDelegate_CustomCtor )
	{
		{
			const ASD::UniqueDelegate<int( ASD_CDECL MyClass::* )( int )> UniqueDelegate{ &MyClass::DoSmth, std::make_unique<MyClass>() };
			ASSERT_TRUE( false == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			
			const ASD::UniqueDelegate<int( ASD_CDECL MyClass::* )( int ) noexcept> UniqueDelegateNoexcept{ &MyClass::DoSmth_Noexcept, std::make_unique<MyClass>() };
			ASSERT_TRUE( false == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
		}

		if constexpr( ASD::CallingConventions::HasThiscall )
		{
			const ASD::UniqueDelegate<int( ASD_THISCALL MyClass::* )( int )> UniqueDelegate{ &MyClass::DoSmth_ThisCall, std::make_unique<MyClass>() };
			ASSERT_TRUE( false == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			
			const ASD::UniqueDelegate<int( ASD_THISCALL MyClass::* )( int ) noexcept> UniqueDelegateNoexcept{ &MyClass::DoSmth_ThisCall_Noexcept, std::make_unique<MyClass>() };
			ASSERT_TRUE( false == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasStdcall )
		{
			const ASD::UniqueDelegate<int( ASD_STDCALL MyClass::* )( int )> UniqueDelegate{ &MyClass::DoSmth_StdCall, std::make_unique<MyClass>() };
			ASSERT_TRUE( false == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			
			const ASD::UniqueDelegate<int( ASD_STDCALL MyClass::* )( int ) noexcept> UniqueDelegateNoexcept{ &MyClass::DoSmth_StdCall_Noexcept, std::make_unique<MyClass>() };
			ASSERT_TRUE( false == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasFastcall )
		{
			const ASD::UniqueDelegate<int( ASD_FASTCALL MyClass::* )( int )> UniqueDelegate{ &MyClass::DoSmth_FastCall, std::make_unique<MyClass>() };
			ASSERT_TRUE( false == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			
			const ASD::UniqueDelegate<int( ASD_FASTCALL MyClass::* )( int ) noexcept> UniqueDelegateNoexcept{ &MyClass::DoSmth_FastCall_Noexcept, std::make_unique<MyClass>() };
			ASSERT_TRUE( false == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasVectorcall )
		{
			const ASD::UniqueDelegate<int( ASD_VECTORCALL MyClass::* )( int )> UniqueDelegate{ &MyClass::DoSmth_VectorCall, std::make_unique<MyClass>() };
			ASSERT_TRUE( false == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			
			const ASD::UniqueDelegate<int( ASD_VECTORCALL MyClass::* )( int ) noexcept> UniqueDelegateNoexcept{ &MyClass::DoSmth_VectorCall_Noexcept, std::make_unique<MyClass>() };
			ASSERT_TRUE( false == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
		}
	}
	
	TEST( UniqueDelegateTests, UniqueDelegate_AssignmentOperator )
	{
		{
			ASD::UniqueDelegate<int( ASD_CDECL MyClass::* )( int )> UniqueDelegate;
			ASSERT_TRUE( true == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			UniqueDelegate.SetMethodAndInstance( &MyClass::DoSmth, std::make_unique<MyClass>() );
			ASSERT_TRUE( false == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			
			ASD::UniqueDelegate<int( ASD_CDECL MyClass::* )( int ) noexcept> UniqueDelegateNoexcept;
			ASSERT_TRUE( true == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
			UniqueDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_Noexcept,std::make_unique<MyClass>() );
			ASSERT_TRUE( false == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
		}

		if constexpr( ASD::CallingConventions::HasThiscall )
		{
			ASD::UniqueDelegate<int( ASD_THISCALL MyClass::* )( int )> UniqueDelegate;
			ASSERT_TRUE( true == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			UniqueDelegate.SetMethodAndInstance( &MyClass::DoSmth_ThisCall, std::make_unique<MyClass>() );
			ASSERT_TRUE( false == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			
			ASD::UniqueDelegate<int( ASD_THISCALL MyClass::* )( int ) noexcept> UniqueDelegateNoexcept;
			ASSERT_TRUE( true == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
			UniqueDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_ThisCall_Noexcept, std::make_unique<MyClass>() );
			ASSERT_TRUE( false == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasStdcall )
		{
			ASD::UniqueDelegate<int( ASD_STDCALL MyClass::* )( int )> UniqueDelegate;
			ASSERT_TRUE( true == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			UniqueDelegate.SetMethodAndInstance( &MyClass::DoSmth_StdCall, std::make_unique<MyClass>() );
			ASSERT_TRUE( false == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			
			ASD::UniqueDelegate<int( ASD_STDCALL MyClass::* )( int ) noexcept> UniqueDelegateNoexcept;
			ASSERT_TRUE( true == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
			UniqueDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_StdCall_Noexcept, std::make_unique<MyClass>() );
			ASSERT_TRUE( false == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasFastcall )
		{
			ASD::UniqueDelegate<int( ASD_FASTCALL MyClass::* )( int )> UniqueDelegate;
			ASSERT_TRUE( true == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			UniqueDelegate.SetMethodAndInstance( &MyClass::DoSmth_FastCall, std::make_unique<MyClass>() );
			ASSERT_TRUE( false == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			
			ASD::UniqueDelegate<int( ASD_FASTCALL MyClass::* )( int ) noexcept> UniqueDelegateNoexcept;
			ASSERT_TRUE( true == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
			UniqueDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_FastCall_Noexcept, std::make_unique<MyClass>() );
			ASSERT_TRUE( false == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasVectorcall )
		{
			ASD::UniqueDelegate<int( ASD_VECTORCALL MyClass::* )( int )> UniqueDelegate;
			ASSERT_TRUE( true == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			UniqueDelegate.SetMethodAndInstance( &MyClass::DoSmth_VectorCall, std::make_unique<MyClass>() );
			ASSERT_TRUE( false == UniqueDelegate.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegate ) ); //operator bool()
			
			ASD::UniqueDelegate<int( ASD_VECTORCALL MyClass::* )( int ) noexcept> UniqueDelegateNoexcept;
			ASSERT_TRUE( true == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
			UniqueDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_VectorCall_Noexcept, std::make_unique<MyClass>() );
			ASSERT_TRUE( false == UniqueDelegateNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( UniqueDelegateNoexcept ) ); //operator bool()
		}
	}
	
	TEST( UniqueDelegateTests, UniqueDelegate_API )
	{
		ASD::UniqueDelegate<int( ASD_CDECL MyClass::* )( int )> UniqueDelegate;
		ASSERT_TRUE( UniqueDelegate.GetInstance() == nullptr );
		ASSERT_EQ( nullptr, UniqueDelegate.GetMethod() );
		ASSERT_EQ( false, UniqueDelegate.HasMethod() );
		ASSERT_EQ( false, UniqueDelegate.HasInstance() );
		ASSERT_EQ( true, UniqueDelegate.IsNull() );

		UniqueDelegate.SetMethodAndInstance( &MyClass::DoSmth, std::make_unique<MyClass>() );
		ASSERT_TRUE( UniqueDelegate.GetInstance() != nullptr );
		ASSERT_EQ( &MyClass::DoSmth, UniqueDelegate.GetMethod() );
		ASSERT_EQ( true, UniqueDelegate.HasMethod() );
		ASSERT_EQ( true, UniqueDelegate.HasInstance() );
		ASSERT_EQ( false, UniqueDelegate.IsNull() );

		UniqueDelegate.SetMethodAndInstance( nullptr, nullptr );
		ASSERT_TRUE( UniqueDelegate.GetInstance() == nullptr );
		ASSERT_EQ( nullptr, UniqueDelegate.GetMethod() );
		ASSERT_EQ( false, UniqueDelegate.HasMethod() );
		ASSERT_EQ( false, UniqueDelegate.HasInstance() );
		ASSERT_EQ( true, UniqueDelegate.IsNull() );

		UniqueDelegate.SetInstance( std::make_unique<MyClass>() );
		ASSERT_TRUE( UniqueDelegate.GetInstance() != nullptr );
		ASSERT_EQ( nullptr, UniqueDelegate.GetMethod() );
		ASSERT_EQ( false, UniqueDelegate.HasMethod() );
		ASSERT_EQ( true, UniqueDelegate.HasInstance() );
		ASSERT_EQ( true, UniqueDelegate.IsNull() );
		
		UniqueDelegate.SetMethod( &MyClass::DoSmth );
		ASSERT_TRUE( UniqueDelegate.GetInstance() != nullptr );
		ASSERT_EQ( &MyClass::DoSmth, UniqueDelegate.GetMethod() );
		ASSERT_EQ( true, UniqueDelegate.HasMethod() );
		ASSERT_EQ( true, UniqueDelegate.HasInstance() );
		ASSERT_EQ( false, UniqueDelegate.IsNull() );

		UniqueDelegate.SetInstance( nullptr );
		UniqueDelegate.SetMethod( nullptr );
		ASSERT_TRUE( UniqueDelegate.GetInstance() == nullptr );
		ASSERT_EQ( nullptr, UniqueDelegate.GetMethod() );
		ASSERT_EQ( false, UniqueDelegate.HasMethod() );
		ASSERT_EQ( false, UniqueDelegate.HasInstance() );
		ASSERT_EQ( true, UniqueDelegate.IsNull() );

		ASSERT_TRUE( UniqueDelegate.ReleaseInstance() == nullptr );
		ASSERT_TRUE( UniqueDelegate.ResetInstance( std::make_unique<MyClass>() ) == nullptr );
		ASSERT_TRUE( UniqueDelegate.GetInstance() != nullptr);
		ASSERT_TRUE( UniqueDelegate.ReleaseInstance() != nullptr );
		ASSERT_TRUE( UniqueDelegate.GetInstance() == nullptr );
		ASSERT_TRUE( UniqueDelegate.ReleaseInstance() == nullptr );
		ASSERT_EQ( false, UniqueDelegate.HasMethod() );
		ASSERT_EQ( false, UniqueDelegate.HasInstance() );
		ASSERT_EQ( true, UniqueDelegate.IsNull() );
	}

	TEST( UniqueDelegateTests, UniqueDelegate_Dispatch )
	{
		MyClass MyClassInstance2;

		{
			ASD::UniqueDelegate<int( ASD_CDECL MyClass::* )( int )> UniqueDelegate;
			UniqueDelegate.SetMethodAndInstance( &MyClass::DoSmth, std::make_unique<MyClass>() );
			auto Result = UniqueDelegate.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = UniqueDelegate.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = UniqueDelegate.Dispatch( &MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
			
			ASD::UniqueDelegate<int( ASD_CDECL MyClass::* )( int ) noexcept> UniqueDelegateNoexcept;
			UniqueDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_Noexcept, std::make_unique<MyClass>() );
			Result = UniqueDelegateNoexcept.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = UniqueDelegateNoexcept.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = UniqueDelegateNoexcept.Dispatch( &MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
		}

		if constexpr( ASD::CallingConventions::HasThiscall )
		{
			ASD::UniqueDelegate<int( ASD_THISCALL MyClass::* )( int )> UniqueDelegate;
			UniqueDelegate.SetMethodAndInstance( &MyClass::DoSmth_ThisCall, std::make_unique<MyClass>() );
			auto Result = UniqueDelegate.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = UniqueDelegate.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = UniqueDelegate.Dispatch( &MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
			
			ASD::UniqueDelegate<int( ASD_THISCALL MyClass::* )( int ) noexcept> UniqueDelegateNoexcept;
			UniqueDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_ThisCall_Noexcept, std::make_unique<MyClass>() );
			Result = UniqueDelegateNoexcept.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = UniqueDelegateNoexcept.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = UniqueDelegateNoexcept.Dispatch( &MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
		}
		
		if constexpr( ASD::CallingConventions::HasStdcall )
		{
			ASD::UniqueDelegate<int( ASD_STDCALL MyClass::* )( int )> UniqueDelegate;
			UniqueDelegate.SetMethodAndInstance( &MyClass::DoSmth_StdCall, std::make_unique<MyClass>() );
			auto Result = UniqueDelegate.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = UniqueDelegate.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = UniqueDelegate.Dispatch( &MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
			
			ASD::UniqueDelegate<int( ASD_STDCALL MyClass::* )( int ) noexcept> UniqueDelegateNoexcept;
			UniqueDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_StdCall_Noexcept, std::make_unique<MyClass>() );
			Result = UniqueDelegateNoexcept.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = UniqueDelegateNoexcept.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = UniqueDelegateNoexcept.Dispatch( &MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
		}
		
		if constexpr( ASD::CallingConventions::HasFastcall )
		{
			ASD::UniqueDelegate<int( ASD_FASTCALL MyClass::* )( int )> UniqueDelegate;
			UniqueDelegate.SetMethodAndInstance( &MyClass::DoSmth_FastCall, std::make_unique<MyClass>() );
			auto Result = UniqueDelegate.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = UniqueDelegate.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = UniqueDelegate.Dispatch( &MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
			
			ASD::UniqueDelegate<int( ASD_FASTCALL MyClass::* )( int ) noexcept> UniqueDelegateNoexcept;
			UniqueDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_FastCall_Noexcept, std::make_unique<MyClass>() );
			Result = UniqueDelegateNoexcept.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = UniqueDelegateNoexcept.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = UniqueDelegateNoexcept.Dispatch( &MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
		}
		
		if constexpr( ASD::CallingConventions::HasVectorcall )
		{
			ASD::UniqueDelegate<int( ASD_VECTORCALL MyClass::* )( int )> UniqueDelegate;
			UniqueDelegate.SetMethodAndInstance( &MyClass::DoSmth_VectorCall, std::make_unique<MyClass>() );
			auto Result = UniqueDelegate.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = UniqueDelegate.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = UniqueDelegate.Dispatch( &MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
			
			ASD::UniqueDelegate<int( ASD_VECTORCALL MyClass::* )( int ) noexcept> UniqueDelegateNoexcept;
			UniqueDelegateNoexcept.SetMethodAndInstance( &MyClass::DoSmth_VectorCall_Noexcept, std::make_unique<MyClass>() );
			Result = UniqueDelegateNoexcept.Dispatch( 1 );
			ASSERT_TRUE( Result == 2 );
			Result = UniqueDelegateNoexcept.Dispatch( MyClassInstance2, 2 );
			ASSERT_TRUE( Result == 3 );
			Result = UniqueDelegateNoexcept.Dispatch( &MyClassInstance2, 3 );
			ASSERT_TRUE( Result == 4 );
		}
	}
	
	TEST( UniqueDelegateTests, UniqueDelegate_AllCustomCtors )
	{
		MyClass MyClassInstance{ 0, false };
		
		{
			ASD::UniqueDelegate<int( ASD_CDECL MyClass::* )( int )> UniqueDelegate { &MyClass::DoSmth };

			ASSERT_TRUE( UniqueDelegate.GetInstance() == nullptr );
			ASSERT_EQ( &MyClass::DoSmth, UniqueDelegate.GetMethod() );
			ASSERT_EQ( true, UniqueDelegate.HasMethod() );
			ASSERT_EQ( false, UniqueDelegate.HasInstance() );
			ASSERT_EQ( true, UniqueDelegate.IsNull() );
		}

		{
			ASD::UniqueDelegate<int( ASD_CDECL MyClass::* )( int )> UniqueDelegate { &MyClass::DoSmth, std::make_unique<MyClass>() };

			ASSERT_TRUE( UniqueDelegate.GetInstance() != nullptr );
			ASSERT_EQ( &MyClass::DoSmth, UniqueDelegate.GetMethod() );
			ASSERT_EQ( true, UniqueDelegate.HasMethod() );
			ASSERT_EQ( true, UniqueDelegate.HasInstance() );
			ASSERT_EQ( false, UniqueDelegate.IsNull() );
		}
	}

	//TEST( UniqueDelegateTests, UniqueDelegate_Copy ) -> can't copy std::unique_ptr
	
	TEST( UniqueDelegateTests, UniqueDelegate_Move )
	{
		{
			ASD::UniqueDelegate<int( ASD_CDECL MyClass::* )( int )> UniqueDelegate { &MyClass::DoSmth, std::make_unique<MyClass>() };
			ASSERT_TRUE( UniqueDelegate.GetInstance() != nullptr );
			ASSERT_EQ( &MyClass::DoSmth, UniqueDelegate.GetMethod() );

			const ASD::UniqueDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate2 { std::move( UniqueDelegate ) };
		
			ASSERT_TRUE( UniqueDelegate.IsNull() );
			ASSERT_TRUE( RawDelegate2.GetInstance() != nullptr );
			ASSERT_EQ( RawDelegate2.GetMethod(), &MyClass::DoSmth );
		}

		{
			ASD::UniqueDelegate<int( ASD_CDECL MyClass::* )( int )> UniqueDelegate { &MyClass::DoSmth, std::make_unique<MyClass>() };
			ASSERT_TRUE( UniqueDelegate.GetInstance() != nullptr );
			ASSERT_EQ( &MyClass::DoSmth, UniqueDelegate.GetMethod() );

			ASD::UniqueDelegate<int( ASD_CDECL MyClass::* )( int )> RawDelegate2;

			RawDelegate2 = std::move( UniqueDelegate );
		
			ASSERT_TRUE( UniqueDelegate.IsNull() );
			ASSERT_TRUE( RawDelegate2.GetInstance() != nullptr );
			ASSERT_EQ( RawDelegate2.GetMethod(), &MyClass::DoSmth );
		}
	}
}
