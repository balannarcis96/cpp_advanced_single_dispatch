#include <gtest/gtest.h>

//Tests target types
#include <SingleDispatch.h>

#include "tests/FnPtrTests.h"
#include "tests/MethodPtrTests.h"
#include "tests/RawDelegateTests.h"
#include "tests/UniqueDelegateTests.h"
#include "tests/SharedDelegateTests.h"

int main( int argc, char** argv )
{
	testing::InitGoogleTest( &argc, argv );
	return RUN_ALL_TESTS( );
}