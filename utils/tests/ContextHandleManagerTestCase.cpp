#include "ContextHandleManagerTestCase.h"

CPPUNIT_TEST_SUITE_REGISTRATION( ContextHandleManagerTestCase );

void ContextHandleManagerTestCase::setUp()
{
}

void ContextHandleManagerTestCase::tearDown()
{
}

void ContextHandleManagerTestCase::testCDtor()
{
	try {
		ContextHandleManager tc;
	} catch (...) {
	}
}

