#pragma once

namespace MethodPtrTests
{
	class MyClass
	{
	public:
		virtual ~MyClass() = default;

		int DoSmth( int a )
		{
			return a + 1;
		}

		virtual int DoSmth2( int a )
		{
			return a + 2;
		}
	};

	class MyClass2 : public MyClass
	{
	public:
		int DoSmth2( int a ) override
		{
			return a + 3;
		}

		int Call_Base_DoSmth2( int a ) 
		{
			return MyClass::DoSmth2( a );
		}
	};

	TEST( MethodPtrTests, MethodPtr_DefaultCtor )
	{
		const ASD::MethodPtr<MyClass, void(void)> MethodPtr;

		ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
		ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()
	}

	TEST( MethodPtrTests, MethodPtr_CustomCtor )
	{
		const ASD::MethodPtr<MyClass, int(int)> MethodPtr = { &MyClass::DoSmth };

		ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
		ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()
	}

	TEST( MethodPtrTests, MethodPtr_AssignmentOperator )
	{
		ASD::MethodPtr<MyClass, int(int)> MethodPtr;

		ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
		ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()

		MethodPtr = &MyClass::DoSmth2;

		ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
		ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()
	}
	
	TEST( MethodPtrTests, MethodPtr_ValueTest )
	{
		ASD::MethodPtr<MyClass, int(int)> MethodPtr;

		ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
		ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()
		ASSERT_TRUE( MethodPtr == nullptr ); //operator ==

		MethodPtr = &MyClass::DoSmth2;

		ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
		ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()
		ASSERT_TRUE( MethodPtr == &MyClass::DoSmth2 ); //operator ==
	}

	TEST( MethodPtrTests, MethodPtr_CallOperator )
	{
		ASD::MethodPtr<MyClass, int(int)> MethodPtr;

		ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
		ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()

		MethodPtr = &MyClass::DoSmth;

		ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
		ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()

		MyClass MyClassInstance;
		MyClass2 MyClass2Instance;

		int DirectResult = MyClassInstance.DoSmth( 1 );
		int PtrResult = MethodPtr( MyClassInstance, 1 );

		ASSERT_EQ( DirectResult, PtrResult );

		DirectResult = MyClass2Instance.DoSmth( 1 );
		PtrResult = MethodPtr( MyClass2Instance, 1 );

		ASSERT_EQ( DirectResult, PtrResult );
	}

	TEST( MethodPtrTests, MethodPtr_AcceptsBaseClassMethod )
	{
		ASD::MethodPtr<MyClass2, int(int)> MethodPtr = { &MyClass2::DoSmth2 };

		ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
		ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()

		MyClass2 MyClass2Instance;

		int DirectResult = MyClass2Instance.DoSmth2( 1 );
		int PtrResult = MethodPtr( MyClass2Instance, 1 );

		ASSERT_EQ( DirectResult, PtrResult );

		MethodPtr = &MyClass::DoSmth2;

		DirectResult = MyClass2Instance.Call_Base_DoSmth2( 1 );
		PtrResult = MethodPtr( MyClass2Instance, 1 );

		ASSERT_EQ( DirectResult, PtrResult );
	}
}
