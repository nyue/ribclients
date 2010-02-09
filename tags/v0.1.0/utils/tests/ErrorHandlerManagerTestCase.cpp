#include "ErrorHandlerManagerTestCase.h"

CPPUNIT_TEST_SUITE_REGISTRATION( ErrorHandlerManagerTestCase );

void ErrorHandlerManagerTestCase::setUp()
{
}

void ErrorHandlerManagerTestCase::tearDown()
{
}

void ErrorHandlerManagerTestCase::testCDtor()
{
	try {
		ErrorHandlerManager tc;
	} catch (...) {
	}
}

