#ifndef _ERRORHANDLERMANAGERTESTCASE_H_
#define _ERRORHANDLERMANAGERTESTCASE_H_
#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <ErrorHandlerManager.h>

class ErrorHandlerManagerTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( ErrorHandlerManagerTestCase );
	CPPUNIT_TEST( testCDtor );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
	void testCDtor();
};

#endif // _ERRORHANDLERMANAGERTESTCASE_H_
