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
		
		int ASD_STDCALL DoSmth_StdCall( int a )
		{
			return a + 1;
		}

		int ASD_THISCALL DoSmth_ThisCall( int a )
		{
			return a + 1;
		}
		
		int ASD_FASTCALL DoSmth_FastCall( int a )
		{
			return a + 1;
		}

		int ASD_VECTORCALL DoSmth_VectorCall( int a )
		{
			return a + 1;
		}
		
		int ASD_STDCALL DoSmth_StdCall_Noexcept( int a ) noexcept
		{
			return a + 1;
		}
		
		int DoSmth_Noexcept( int a ) noexcept
		{
			return a + 1;
		}

		int ASD_THISCALL DoSmth_ThisCall_Noexcept( int a ) noexcept
		{
			return a + 1;
		}
		
		int ASD_FASTCALL DoSmth_FastCall_Noexcept( int a ) noexcept
		{
			return a + 1;
		}

		int ASD_VECTORCALL DoSmth_VectorCall_Noexcept( int a ) noexcept
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
		{
			const ASD::MethodPtr<void( ASD_CDECL MyClass::* )( void )> MethodPtr;
			ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()
			
			const ASD::MethodPtr<void( ASD_CDECL MyClass::* )( void ) noexcept> MethodPtrNoexcept;
			ASSERT_TRUE( true == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
		}

		if constexpr( ASD::CallingConventions::HasThiscall )
		{
			const ASD::MethodPtr<void( ASD_THISCALL MyClass::* )( void )> MethodPtr;
			ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()
			
			const ASD::MethodPtr<void( ASD_THISCALL MyClass::* )( void ) noexcept> MethodPtrNoexcept;
			ASSERT_TRUE( true == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasStdcall )
		{
			const ASD::MethodPtr<void( ASD_STDCALL MyClass::* )( void )> MethodPtr;
			ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()
			
			const ASD::MethodPtr<void( ASD_STDCALL MyClass::* )( void ) noexcept> MethodPtrNoexcept;
			ASSERT_TRUE( true == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasFastcall )
		{
			const ASD::MethodPtr<void( ASD_FASTCALL MyClass::* )( void )> MethodPtr;
			ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()
			
			const ASD::MethodPtr<void( ASD_FASTCALL MyClass::* )( void ) noexcept> MethodPtrNoexcept;
			ASSERT_TRUE( true == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasVectorcall )
		{
			const ASD::MethodPtr<void( ASD_VECTORCALL MyClass::* )( void )> MethodPtr;
			ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()
			
			const ASD::MethodPtr<void( ASD_VECTORCALL MyClass::* )( void ) noexcept> MethodPtrNoexcept;
			ASSERT_TRUE( true == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
		}
	}

	TEST( MethodPtrTests, MethodPtr_CustomCtor )
	{
		{
			const ASD::MethodPtr<int( ASD_CDECL MyClass::* )( int )> MethodPtr { &MyClass::DoSmth };
			ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()

			const ASD::MethodPtr<int( ASD_CDECL MyClass::* )( int ) noexcept> MethodPtrNoexcept { &MyClass::DoSmth_Noexcept };
			ASSERT_TRUE( false == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
		}

		if constexpr( ASD::CallingConventions::HasThiscall )
		{
			const ASD::MethodPtr<int( ASD_THISCALL MyClass::* )( int )> MethodPtr { &MyClass::DoSmth_ThisCall };
			ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()

			const ASD::MethodPtr<int( ASD_THISCALL MyClass::* )( int ) noexcept> MethodPtrNoexcept { &MyClass::DoSmth_ThisCall_Noexcept };
			ASSERT_TRUE( false == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasStdcall )
		{
			const ASD::MethodPtr<int( ASD_STDCALL MyClass::* )( int )> MethodPtr { &MyClass::DoSmth_StdCall };
			ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()

			const ASD::MethodPtr<int( ASD_STDCALL MyClass::* )( int ) noexcept> MethodPtrNoexcept { &MyClass::DoSmth_StdCall_Noexcept };
			ASSERT_TRUE( false == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasFastcall )
		{
			const ASD::MethodPtr<int( ASD_FASTCALL MyClass::* )( int )> MethodPtr { &MyClass::DoSmth_FastCall };
			ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()

			const ASD::MethodPtr<int( ASD_FASTCALL MyClass::* )( int ) noexcept> MethodPtrNoexcept { &MyClass::DoSmth_FastCall_Noexcept };
			ASSERT_TRUE( false == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
		}
		
		if constexpr( ASD::CallingConventions::HasVectorcall )
		{
			const ASD::MethodPtr<int( ASD_VECTORCALL MyClass::* )( int )> MethodPtr { &MyClass::DoSmth_VectorCall };
			ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()

			const ASD::MethodPtr<int( ASD_VECTORCALL MyClass::* )( int ) noexcept> MethodPtrNoexcept { &MyClass::DoSmth_VectorCall_Noexcept };
			ASSERT_TRUE( false == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
		}
	}

	TEST( MethodPtrTests, MethodPtr_AssignmentOperator )
	{
		{
			ASD::MethodPtr<int( ASD_CDECL MyClass::* )( int )> MethodPtr;
			ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()
			MethodPtr = &MyClass::DoSmth;
			ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()
			ASSERT_TRUE( MethodPtr == &MyClass::DoSmth ); //operator ==
			
			ASD::MethodPtr<int( ASD_CDECL MyClass::* )( int )> MethodPtrNoexcept;
			ASSERT_TRUE( true == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
			MethodPtrNoexcept = &MyClass::DoSmth_Noexcept;
			ASSERT_TRUE( false == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
			ASSERT_TRUE( MethodPtrNoexcept == &MyClass::DoSmth_Noexcept ); //operator ==
		}

		if constexpr( ASD::CallingConventions::HasThiscall )
		{
			ASD::MethodPtr<int( ASD_THISCALL MyClass::* )( int )> MethodPtr;
			ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()
			MethodPtr = &MyClass::DoSmth_ThisCall;
			ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()
			ASSERT_TRUE( MethodPtr == &MyClass::DoSmth_ThisCall ); //operator ==
			
			ASD::MethodPtr<int( ASD_THISCALL MyClass::* )( int )> MethodPtrNoexcept;
			ASSERT_TRUE( true == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
			MethodPtrNoexcept = &MyClass::DoSmth_ThisCall_Noexcept;
			ASSERT_TRUE( false == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
			ASSERT_TRUE( MethodPtrNoexcept == &MyClass::DoSmth_ThisCall_Noexcept ); //operator ==
		}

		if constexpr( ASD::CallingConventions::HasStdcall )
		{
			ASD::MethodPtr<int( ASD_STDCALL MyClass::* )( int )> MethodPtr;
			ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()
			MethodPtr = &MyClass::DoSmth_StdCall;
			ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()
			ASSERT_TRUE( MethodPtr == &MyClass::DoSmth_StdCall ); //operator ==
			
			ASD::MethodPtr<int( ASD_STDCALL MyClass::* )( int )> MethodPtrNoexcept;
			ASSERT_TRUE( true == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
			MethodPtrNoexcept = &MyClass::DoSmth_StdCall_Noexcept;
			ASSERT_TRUE( false == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
			ASSERT_TRUE( MethodPtrNoexcept == &MyClass::DoSmth_StdCall_Noexcept ); //operator ==
		}

		if constexpr( ASD::CallingConventions::HasFastcall )
		{
			ASD::MethodPtr<int( ASD_FASTCALL MyClass::* )( int )> MethodPtr;
			ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()
			MethodPtr = &MyClass::DoSmth_FastCall;
			ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()
			ASSERT_TRUE( MethodPtr == &MyClass::DoSmth_FastCall ); //operator ==
			
			ASD::MethodPtr<int( ASD_FASTCALL MyClass::* )( int )> MethodPtrNoexcept;
			ASSERT_TRUE( true == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
			MethodPtrNoexcept = &MyClass::DoSmth_FastCall_Noexcept;
			ASSERT_TRUE( false == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
			ASSERT_TRUE( MethodPtrNoexcept == &MyClass::DoSmth_FastCall_Noexcept ); //operator ==
		}

		if constexpr( ASD::CallingConventions::HasVectorcall )
		{
			ASD::MethodPtr<int( ASD_VECTORCALL MyClass::* )( int )> MethodPtr;
			ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()
			MethodPtr = &MyClass::DoSmth_VectorCall;
			ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()
			ASSERT_TRUE( MethodPtr == &MyClass::DoSmth_VectorCall ); //operator ==
			
			ASD::MethodPtr<int( ASD_VECTORCALL MyClass::* )( int )> MethodPtrNoexcept;
			ASSERT_TRUE( true == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
			MethodPtrNoexcept = &MyClass::DoSmth_VectorCall_Noexcept;
			ASSERT_TRUE( false == MethodPtrNoexcept.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtrNoexcept ) ); //operator bool()
			ASSERT_TRUE( MethodPtrNoexcept == &MyClass::DoSmth_VectorCall_Noexcept ); //operator ==
		}
	}
	
	TEST( MethodPtrTests, MethodPtr_CallOperator )
	{
		{
			ASD::MethodPtr<int( ASD_CDECL MyClass::* )( int )> MethodPtr;

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

		{
			ASD::MethodPtr<int( ASD_CDECL MyClass::* )( int ) noexcept> MethodPtr;

			ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()

			MethodPtr = &MyClass::DoSmth_Noexcept;

			ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
			ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()

			MyClass MyClassInstance;
			MyClass2 MyClass2Instance;

			int DirectResult = MyClassInstance.DoSmth_Noexcept( 1 );
			int PtrResult = MethodPtr( MyClassInstance, 1 );

			ASSERT_EQ( DirectResult, PtrResult );

			DirectResult = MyClass2Instance.DoSmth_Noexcept( 1 );
			PtrResult = MethodPtr( MyClass2Instance, 1 );

			ASSERT_EQ( DirectResult, PtrResult );
		}

		if( ASD::CallingConventions::HasThiscall )
		{
			{
				ASD::MethodPtr<int( ASD_THISCALL MyClass::* )( int )> MethodPtr;

				ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
				ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()

				MethodPtr = &MyClass::DoSmth_ThisCall;

				ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
				ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()

				MyClass MyClassInstance;
				MyClass2 MyClass2Instance;

				int DirectResult = MyClassInstance.DoSmth_ThisCall( 1 );
				int PtrResult = MethodPtr( MyClassInstance, 1 );

				ASSERT_EQ( DirectResult, PtrResult );

				DirectResult = MyClass2Instance.DoSmth_ThisCall( 1 );
				PtrResult = MethodPtr( MyClass2Instance, 1 );

				ASSERT_EQ( DirectResult, PtrResult );
			}

			{
				ASD::MethodPtr<int( ASD_THISCALL MyClass::* )( int ) noexcept> MethodPtr;

				ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
				ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()

				MethodPtr = &MyClass::DoSmth_ThisCall_Noexcept;

				ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
				ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()

				MyClass MyClassInstance;
				MyClass2 MyClass2Instance;

				int DirectResult = MyClassInstance.DoSmth_ThisCall_Noexcept( 1 );
				int PtrResult = MethodPtr( MyClassInstance, 1 );

				ASSERT_EQ( DirectResult, PtrResult );

				DirectResult = MyClass2Instance.DoSmth_ThisCall_Noexcept( 1 );
				PtrResult = MethodPtr( MyClass2Instance, 1 );

				ASSERT_EQ( DirectResult, PtrResult );
			}
		}

		if( ASD::CallingConventions::HasStdcall )
		{
			{
				ASD::MethodPtr<int( ASD_STDCALL MyClass::* )( int )> MethodPtr;

				ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
				ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()

				MethodPtr = &MyClass::DoSmth_StdCall;

				ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
				ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()

				MyClass MyClassInstance;
				MyClass2 MyClass2Instance;

				int DirectResult = MyClassInstance.DoSmth_StdCall( 1 );
				int PtrResult = MethodPtr( MyClassInstance, 1 );

				ASSERT_EQ( DirectResult, PtrResult );

				DirectResult = MyClass2Instance.DoSmth_StdCall( 1 );
				PtrResult = MethodPtr( MyClass2Instance, 1 );

				ASSERT_EQ( DirectResult, PtrResult );
			}

			{
				ASD::MethodPtr<int( ASD_STDCALL MyClass::* )( int ) noexcept> MethodPtr;

				ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
				ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()

				MethodPtr = &MyClass::DoSmth_StdCall_Noexcept;

				ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
				ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()

				MyClass MyClassInstance;
				MyClass2 MyClass2Instance;

				int DirectResult = MyClassInstance.DoSmth_StdCall_Noexcept( 1 );
				int PtrResult = MethodPtr( MyClassInstance, 1 );

				ASSERT_EQ( DirectResult, PtrResult );

				DirectResult = MyClass2Instance.DoSmth_StdCall_Noexcept( 1 );
				PtrResult = MethodPtr( MyClass2Instance, 1 );

				ASSERT_EQ( DirectResult, PtrResult );
			}
		}
		
		if( ASD::CallingConventions::HasFastcall )
		{
			{
				ASD::MethodPtr<int( ASD_FASTCALL MyClass::* )( int )> MethodPtr;

				ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
				ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()

				MethodPtr = &MyClass::DoSmth_FastCall;

				ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
				ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()

				MyClass MyClassInstance;
				MyClass2 MyClass2Instance;

				int DirectResult = MyClassInstance.DoSmth_FastCall( 1 );
				int PtrResult = MethodPtr( MyClassInstance, 1 );

				ASSERT_EQ( DirectResult, PtrResult );

				DirectResult = MyClass2Instance.DoSmth_FastCall( 1 );
				PtrResult = MethodPtr( MyClass2Instance, 1 );

				ASSERT_EQ( DirectResult, PtrResult );
			}

			{
				ASD::MethodPtr<int( ASD_FASTCALL MyClass::* )( int ) noexcept> MethodPtr;

				ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
				ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()

				MethodPtr = &MyClass::DoSmth_FastCall_Noexcept;

				ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
				ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()

				MyClass MyClassInstance;
				MyClass2 MyClass2Instance;

				int DirectResult = MyClassInstance.DoSmth_FastCall_Noexcept( 1 );
				int PtrResult = MethodPtr( MyClassInstance, 1 );

				ASSERT_EQ( DirectResult, PtrResult );

				DirectResult = MyClass2Instance.DoSmth_FastCall_Noexcept( 1 );
				PtrResult = MethodPtr( MyClass2Instance, 1 );

				ASSERT_EQ( DirectResult, PtrResult );
			}
		}
		
		if( ASD::CallingConventions::HasVectorcall )
		{
			{
				ASD::MethodPtr<int( ASD_VECTORCALL MyClass::* )( int )> MethodPtr;

				ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
				ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()

				MethodPtr = &MyClass::DoSmth_VectorCall;

				ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
				ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()

				MyClass MyClassInstance;
				MyClass2 MyClass2Instance;

				int DirectResult = MyClassInstance.DoSmth_VectorCall( 1 );
				int PtrResult = MethodPtr( MyClassInstance, 1 );

				ASSERT_EQ( DirectResult, PtrResult );

				DirectResult = MyClass2Instance.DoSmth_VectorCall( 1 );
				PtrResult = MethodPtr( MyClass2Instance, 1 );

				ASSERT_EQ( DirectResult, PtrResult );
			}

			{
				ASD::MethodPtr<int( ASD_VECTORCALL MyClass::* )( int ) noexcept> MethodPtr;

				ASSERT_TRUE( true == MethodPtr.IsNull(  ) );
				ASSERT_TRUE( false == static_cast<bool>( MethodPtr ) ); //operator bool()

				MethodPtr = &MyClass::DoSmth_VectorCall_Noexcept;

				ASSERT_TRUE( false == MethodPtr.IsNull(  ) );
				ASSERT_TRUE( true == static_cast<bool>( MethodPtr ) ); //operator bool()

				MyClass MyClassInstance;
				MyClass2 MyClass2Instance;

				int DirectResult = MyClassInstance.DoSmth_VectorCall_Noexcept( 1 );
				int PtrResult = MethodPtr( MyClassInstance, 1 );

				ASSERT_EQ( DirectResult, PtrResult );

				DirectResult = MyClass2Instance.DoSmth_VectorCall_Noexcept( 1 );
				PtrResult = MethodPtr( MyClass2Instance, 1 );

				ASSERT_EQ( DirectResult, PtrResult );
			}
		}
	}
}
