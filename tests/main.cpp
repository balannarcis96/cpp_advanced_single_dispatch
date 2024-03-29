#include <gtest/gtest.h>

//Tests target types
#if ASD_HEADER_ONLY
#include <HeaderOnly/AdvancedSingleDispatch.h>
#else
#include <SingleDispatch.h>
#endif

#include "tests/FnPtrTests.h"
#include "tests/MethodPtrTests.h"
#include "tests/RawDelegateTests.h"
#include "tests/UniqueDelegateTests.h"
#include "tests/SharedDelegateTests.h"
#include "tests/FunctorWrapperTests.h"
#include "tests/TaskTests.h"

int main( int argc, char** argv )
{
	testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS( );
}