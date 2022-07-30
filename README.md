# cpp_advanced_single_dispatch [WIP]
[C++ 17 and later] Advanced Single Dispatch Abstractions

  Function Pointer, Method Pointer and Delegate abtractions header only library.<br/>
  Function Pointer, Method Pointer and Delegate types are sensitive to the calling convention of the function type and presence of `noexcept`.<br/>
  Supported calling convetions: `__cdecl, __stdcall, __thiscall, __fastcall, __vectorcall`, other can be added.<br/>
  Code compiled on gcc 12.1, clang 14.0.0, msvc 19 -> arch: x64.<br/>
  UTs are provided. UTs compiled and all pass on [Windows + msvc 19]<br/>

```cpp
  namespace ASD // Advanced Single Dispatch
```

# Available usable types:
```cpp
  ASD::FnPtr<void(/*__cdecl*/*)( void )/*noexcept*/>        	       // Simple function pointer wrapper type 
  ASD::MethodPtr<void(/*__cdecl*/MyClass::*)( void )/*noexcept*/>      // Simple class function pointer (method) wrapper type 
  ASD::RawDelegate<void(/*__cdecl*/MyClass::*)( void )/*noexcept*/>    // Raw pointer delegate, holds raw ptr to instace of MyClass and raw ptr to method 
  ASD::UniqueDelegate<void(/*__cdecl*/MyClass::*)( void )/*noexcept*/> // Unique pointer delegate, holds unique ptr to instace of MyClass and raw ptr to method 
  ASD::SharedDelegate<void(/*__cdecl*/MyClass::*)( void )/*noexcept*/> // Shared pointer delegate, holds shared ptr to instace of MyClass and raw ptr to method 
  
  //sizeof( FnPtr<...> )          = sizeof( void* )
  //sizeof( MethodPtr<...> )      = sizeof( void* )
  //sizeof( RawDelegate<...> )    = sizeof( void* ) * 2
  //sizeof( UniqueDelegate<...> ) = sizeof( void* ) * 2
  //sizeof( SharedDelegate<...> ) = sizeof( void* ) * 2
```

# How to
 
```cpp
	//!
	//! [Usage Example] FnPtr< ... > 
	//!

	const ASD::FnPtr<int( /*calling convention goes here, if needed*/ *)(int)> FunctionPointer1 = GDoSmth;

	ASD::FnPtr< int(int) > FunctionPointer2;
	FunctionPointer2 = DoSomthingFreeFunction;

	if( argc )
	{
		result += FunctionPointer1( 1 );
		result += FunctionPointer2( 1 );
	}
	
	//!
	//! [Usage Example] MethodPtr< ... > 
	//!

	const ASD::MethodPtr<TestType, int(MyClass::*)(int)> MethodPtr = &MyClass::DoSmth;

	ASD::MethodPtr<int(MyClass::*)(int)> MethodPtr2;
	MethodPtr2 =  &MyClass::DoSmth2;
	
	if( argc )
	{
		result += MethodPtr2( MyClassInstance1, 1 );
		result += MethodPtr2( MyClassInstance2.get(), 1 );
	}
	
	//!
	//! [Usage Example] RawDelegate< ... >
	//!

	const ASD::RawDelegate<int(MyClass::*)(int)> RawDelegate1 = { &MyClass::DoSmth, &MyClassInstance1 };

	ASD::RawDelegate<int(MyClass::*)(int)> RawDelegate2;
	RawDelegate2.SetMethodAndInstance( &MyClass::DoSmth, &MyClassInstance1 );
	
	if( argc )
	{
		//call method on instance
		result += RawDelegate1( 1 );
		result += RawDelegate2( 1 );
		
		//call method on instance using explicit Dispatch method
		result += RawDelegate1.Dispatch( 2 );
		result += RawDelegate2.Dispatch( 2 );
		
		//call method on specific instance
		result += RawDelegate1.Dispatch( MyClassInstance3.get(), 2 );
		result += RawDelegate2.Dispatch( MyClassInstance1, 2 );
	}
	
	//!
	//! [Usage Example] UniqueDelegate< ... >
	//!

	const ASD::UniqueDelegate<int(MyClass::*)(int)> UniqueDelegate1 = { &MyClass::DoSmth, std::make_unique<MyClass>() };

	ASD::UniqueDelegate<int(MyClass::*)(int)> UniqueDelegate2;
	UniqueDelegate2.SetMethodAndInstancePointers( &MyClass::DoSmth, std::move( MyClassUniquePtrInstance2 ) );
	
	if( argc )
	{
		//call method on instance
		result += UniqueDelegate1( 1 );
		result += UniqueDelegate2( 1 );
		
		//call method on instance using explicit Dispatch method
		result += UniqueDelegate1.Dispatch( 2 );
		result += UniqueDelegate2.Dispatch( 2 );
		
		//call method on specific instance
		result += UniqueDelegate1.Dispatch( MyClassInstance3.get(), 2 );
		result += UniqueDelegate2.Dispatch( MyClassInstance1, 2 );
	}
	
	//!
	//! [Usage Example] SharedDelegate< ... >
	//!

	const ASD::SharedDelegate<int(MyClass::*)(int)> SharedDelegate1 = { &MyClass::DoSmth, std::make_shared<MyClass>() };
	//const ASD::SharedDelegate<int(MyClass::*)(int)> SharedDelegate1 = { &MyClass::DoSmth, MyClassInstance3 };
	//const ASD::SharedDelegate<int(MyClass::*)(int)> SharedDelegate1 = { &MyClass::DoSmth, std::move( MyClassInstance3 ) };

	ASD::SharedDelegate<int(MyClass::*)(int)> SharedDelegate2;
	//UniqueDelegate2.SetMethodAndInstancePointers( &MyClass::DoSmth, MyClassInstance3 );
	SharedDelegate2.SetMethodAndInstancePointers( &MyClass::DoSmth, std::move( MyClassInstance3 ) );
	
	if( argc )
	{
		//call method on instance
		result += SharedDelegate1( 1 );
		result += SharedDelegate2( 1 );
		
		//call method on instance using explicit Dispatch method
		result += SharedDelegate1.Dispatch( 2 );
		result += SharedDelegate2.Dispatch( 2 );
		
		//call method on specific instance
		result += SharedDelegate1.Dispatch( MyClassInstance3.get(), 2 );
		result += SharedDelegate2.Dispatch( MyClassInstance1, 2 );
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
  - Solution [1]: Copy the `AdvancedSingleDispatch.h` file into your project, include and use!
  - Solution [2]: `lib` is a CMake static library -> rename the `lib` folder (eg SingleDispatch) and `add_subdirectory` into ur project, link and use
  - Solution [3]: Go bonkers yeah, lose your marbles yeah ;)


  
