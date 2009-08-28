#include "ObjectHandleManagerTestCase.h"

CPPUNIT_TEST_SUITE_REGISTRATION( ObjectHandleManagerTestCase );

void ObjectHandleManagerTestCase::setUp()
{
}

void ObjectHandleManagerTestCase::tearDown()
{
}

void ObjectHandleManagerTestCase::testCDtor()
{
	try {
		ObjectHandleManager tc;
	} catch (...) {
	}
}

