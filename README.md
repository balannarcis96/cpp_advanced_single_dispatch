# cpp_advanced_single_dispatch [WIP]
[C++ 17] Advanced Single Dispatch Abstractions

```cpp
  namespace ASD // Advanced Single Dispatch
```

# Available usable types:
```cpp
  ASD::FnPtr < void( void ) >                 // Simple function pointer wrapper type
  ASD::MethodPtr < MyClass, void( void ) >    // Simple class function pointer (method) wrapper type
  ASD::RawDelegate< MyClass, void( void )>    // Raw pointer delegate, holds raw ptr to instace of MyClass and raw ptr to method
  ASD::UniqueDelegate< MyClass, void( void )> // Unique pointer delegate, holds unique ptr to instace of MyClass and raw ptr to method
  ASD::SharedDelegate< MyClass, void( void )> // Shared pointer delegate, holds shared ptr to instace of MyClass and raw ptr to method
```

# How to
  For full usage code see `examples/main.cpp`
 
```cpp
	//!
	//! [Usage Example] FnPtr< ... > 
	//!

	const ASD::FnPtr< int(int) > FunctionPointer1 = GDoSmth;

	ASD::FnPtr< int(int) > FunctionPointer2;
	FunctionPointer2 = GDoSmth;

	if( argc )
	{
		result += FunctionPointer1( 1 );
		result += FunctionPointer2( 1 );
	}
	
	//!
	//! [Usage Example] MethodPtr< ... > 
	//!

	const ASD::MethodPtr< TestType, int(int)> MethodPtr = &TestType::DoSmth;

	ASD::MethodPtr< TestType, int(int)> MethodPtr2;
	MethodPtr2 =  &TestType::DoSmth2;
	
	if( argc )
	{
		result += MethodPtr2( Instance1, 1 );
		result += MethodPtr2( Instance2.get(), 1 );
	}
	
	//!
	//! [Usage Example] RawDelegate< ... >
	//!

	const ASD::RawDelegate< TestType, int(int) > RawDelegate1 = { &TestType::DoSmth, &Instance1 };

	ASD::RawDelegate< TestType, int(int) > RawDelegate2;
	RawDelegate2.SetMethodAndInstance( &TestType::DoSmth, &Instance1 );
	
	if( argc )
	{
		//call method on instance
		result += RawDelegate1( 1 );
		result += RawDelegate2( 1 );
		
		//call method on instance using explicit Dispatch method
		result += RawDelegate1.Dispatch( 2 );
		result += RawDelegate2.Dispatch( 2 );
		
		//call method on specific instance
		result += RawDelegate1.Dispatch( Instance3.get(), 2 );
		result += RawDelegate2.Dispatch( Instance1, 2 );
	}
	
	//!
	//! [Usage Example] UniqueDelegate< ... >
	//!

	const ASD::UniqueDelegate< TestType, int(int) > UniqueDelegate1 = { &TestType::DoSmth, new TestType() };

	ASD::SharedDelegate< TestType, int(int) > UniqueDelegate2;
	UniqueDelegate2.SetMethodAndInstancePointers( &TestType::DoSmth, std::move( Instance2 ) );
	
	if( argc )
	{
		//call method on instance
		result += UniqueDelegate1( 1 );
		result += UniqueDelegate2( 1 );
		
		//call method on instance using explicit Dispatch method
		result += UniqueDelegate1.Dispatch( 2 );
		result += UniqueDelegate2.Dispatch( 2 );
		
		//call method on specific instance
		result += UniqueDelegate1.Dispatch( Instance3.get(), 2 );
		result += UniqueDelegate2.Dispatch( Instance1, 2 );
	}
	
	//!
	//! [Usage Example] SharedDelegate< ... >
	//!

	const ASD::SharedDelegate< TestType, int(int) > SharedDelegate1 = { &TestType::DoSmth, std::make_shared<TestType>() };
	//const ASD::SharedDelegate< TestType, int(int) > SharedDelegate1 = { &TestType::DoSmth, Instance3 };
	//const ASD::SharedDelegate< TestType, int(int) > SharedDelegate1 = { &TestType::DoSmth, std::move( Instance3 ) };

	ASD::SharedDelegate< TestType, int(int) > SharedDelegate2;
	//UniqueDelegate2.SetMethodAndInstancePointers( &TestType::DoSmth, Instance3 );
	SharedDelegate2.SetMethodAndInstancePointers( &TestType::DoSmth, std::move( Instance3 ) );
	
	if( argc )
	{
		//call method on instance
		result += SharedDelegate1( 1 );
		result += SharedDelegate2( 1 );
		
		//call method on instance using explicit Dispatch method
		result += SharedDelegate1.Dispatch( 2 );
		result += SharedDelegate2.Dispatch( 2 );
		
		//call method on specific instance
		result += SharedDelegate1.Dispatch( Instance3.get(), 2 );
		result += SharedDelegate2.Dispatch( Instance1, 2 );
	}
```
# Dependencies
  ```cpp
  <utility>
  <memory>
  <type_traits>
  ```

# Build
Its a header only library!
  - Solution [1]: Copy the `SingleDispatch.h` file into your project, include and use!
  - Solution [2]: `lib` is a CMake static library -> rename the `lib` folder (eg SingleDispatch) and `add_subdirectory` into ur project, link and use
  - Solution [3]: Go bonkers yeah, lose your marbles yeah ;)


  
