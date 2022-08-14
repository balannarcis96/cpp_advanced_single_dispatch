#pragma once

namespace FunctorWrapperTests
{
	class MyClass
	{
	public:
		int DoSmth( int a )
		{
			return a + 1;
		}
		
		int DoSmth_Noexcept( int a ) noexcept
		{
			return a + 1;
		}

		int  AdditionalValue { 0 };
	};

	struct MyFunctor
	{
		int operator()(int x) noexcept
		{
			return static_cast<int>( SPtr->AdditionalValue ) + x;
		}

		std::shared_ptr<MyClass> SPtr;
	};

	TEST( FunctorWrapperTests, TrivialFunctorWrapper_BasicAPI )
	{
		ASD::TrivialFunctorWrapper<8, int(*)(int) noexcept> TrivialFunctor;
		
		ASSERT_TRUE( true == TrivialFunctor.IsNull() );

		size_t a = 55;
		size_t b = 22;

		TrivialFunctor += [&a](int x) noexcept -> int
		{
			return static_cast<int> ( a ) + x;
		};

		ASSERT_TRUE( false == TrivialFunctor.IsNull() );
	
		ASSERT_TRUE( TrivialFunctor( 5 ) == a + 5 );

		TrivialFunctor += [&a](int x) noexcept -> int
		{
			return static_cast<int> ( a ) + x + 1;
		};

		ASSERT_TRUE( TrivialFunctor( 5 ) == a + 5 + 1 );

		TrivialFunctor.Destroy();

		TrivialFunctor += [&a](int x) noexcept -> int
		{
			return static_cast<int> ( a ) + x + 1;
		};

		ASSERT_TRUE( TrivialFunctor( 5 ) == a + 5 + 1 );

		TrivialFunctor.Destroy();

		ASSERT_TRUE( true == TrivialFunctor.IsNull() );
	}

	TEST( FunctorWrapperTests, UniqueFunctorWrapper_BasicAPI )
	{
		ASD::UniqueFunctorWrapper<16, int(*)(int)> UniqueFunctor;
		
		ASSERT_TRUE( true == UniqueFunctor.IsNull() );

		size_t a = 55;
		size_t b = 22;
		auto SPtr = std::make_shared<MyClass>();
		SPtr->AdditionalValue = static_cast<int>( a );

		ASSERT_TRUE( SPtr.use_count() == 1 );

		UniqueFunctor += [&a](int x) -> int
		{
			return static_cast<int> ( a ) + x;
		};

		ASSERT_TRUE( false == UniqueFunctor.IsNull() );
		ASSERT_TRUE( true == UniqueFunctor.IsTrivial() );
	
		ASSERT_TRUE( UniqueFunctor( 5 ) == a + 5 );

		UniqueFunctor += [SPtr](int x) -> int
		{
			return static_cast<int> ( SPtr->AdditionalValue ) + x + 1;
		};

		ASSERT_TRUE( false == UniqueFunctor.IsNull() );
		ASSERT_TRUE( false == UniqueFunctor.IsTrivial() );
		ASSERT_TRUE( SPtr.use_count() == 2 ); //2 shared refs

		ASSERT_TRUE( UniqueFunctor( 5 ) == a + 5 + 1 );

		UniqueFunctor.Destroy();

		ASSERT_TRUE( SPtr.use_count() == 1 ); //back to 2 shared ref, the ref inside the functor was destroyed
		ASSERT_TRUE( true == UniqueFunctor.IsNull() );

		const auto NewFunctor = [SPtr](int x) -> int
		{
			return static_cast<int> ( SPtr->AdditionalValue ) + x + 1;
		};

		ASSERT_TRUE( SPtr.use_count() == 2 ); //2 shared refs

		//pass by copy
		UniqueFunctor.SetFunctor( NewFunctor );

		ASSERT_TRUE( false == UniqueFunctor.IsNull() );
		ASSERT_TRUE( false == UniqueFunctor.IsTrivial() );
		ASSERT_TRUE( SPtr.use_count() == 3 ); //2 shared refs

		UniqueFunctor.Destroy();

		ASSERT_TRUE( true == UniqueFunctor.IsNull() );
		ASSERT_TRUE( SPtr.use_count() == 2 ); //2 shared refs
	}

	TEST( FunctorWrapperTests, CopyFunctorWrapper_BasicAPI )
	{
		ASD::CopyFunctorWrapper<16, int(*)(int)> CopyFunctor;
		
		ASSERT_TRUE( true == CopyFunctor.IsNull() );

		size_t a = 55;
		auto SPtr = std::make_shared<MyClass>();
		SPtr->AdditionalValue = static_cast<int>( a );

		ASSERT_TRUE( SPtr.use_count() == 1 );
			
		MyFunctor NewFunctor { SPtr };

		ASSERT_TRUE( SPtr.use_count() == 2 ); 

		//pass by copy
		CopyFunctor.SetFunctor( NewFunctor );

		ASSERT_TRUE( CopyFunctor( 5 ) == SPtr->AdditionalValue + 5 );

		ASSERT_TRUE( false == CopyFunctor.IsNull() );
		ASSERT_TRUE( false == CopyFunctor.IsTrivial() );
		ASSERT_TRUE( SPtr.use_count() == 3 ); 

		CopyFunctor.Destroy();

		ASSERT_TRUE( true == CopyFunctor.IsNull() );
		ASSERT_TRUE( SPtr.use_count() == 2 );

		MyFunctor NewFunctor2 { SPtr };

		ASSERT_TRUE( SPtr.use_count() == 3 );

		//pass by copy
		CopyFunctor.SetFunctor( NewFunctor );

		ASSERT_TRUE( CopyFunctor( 5 ) == SPtr->AdditionalValue + 5 );

		ASSERT_TRUE( false == CopyFunctor.IsNull() );
		ASSERT_TRUE( false == CopyFunctor.IsTrivial() );
		ASSERT_TRUE( SPtr.use_count() == 4 ); 

		CopyFunctor.Destroy();

		ASSERT_TRUE( true == CopyFunctor.IsNull() );
		ASSERT_TRUE( SPtr.use_count() == 3 );

	}

	TEST( FunctorWrapperTests, MoveFunctorWrapper_BasicAPI )
	{
		ASD::MoveFunctorWrapper<16, int(*)(int) noexcept> MoveFunctor;
		
		ASSERT_TRUE( true == MoveFunctor.IsNull() );

		size_t a = 55;
		auto SPtr = std::make_shared<MyClass>();
		SPtr->AdditionalValue = static_cast<int>( a );

		ASSERT_TRUE( SPtr.use_count() == 1 );

		MyFunctor NewFunctor { SPtr };

		ASSERT_TRUE( SPtr.use_count() == 2 ); 

		//pass by copy
		MoveFunctor += std::move( NewFunctor );

		ASSERT_TRUE( SPtr.use_count() == 2 ); 

		ASSERT_TRUE( MoveFunctor( 5 ) == SPtr->AdditionalValue + 5 );

		ASSERT_TRUE( false == MoveFunctor.IsNull() );
		ASSERT_TRUE( false == MoveFunctor.IsTrivial() );

		MoveFunctor.Destroy();

		ASSERT_TRUE( true == MoveFunctor.IsNull() );
		ASSERT_TRUE( SPtr.use_count() == 1 );
	}
}
