#ifndef _LIGHTHANDLEMANAGERTESTCASE_H_
#define _LIGHTHANDLEMANAGERTESTCASE_H_
#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <LightHandleManager.h>

class LightHandleManagerTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( LightHandleManagerTestCase );
	CPPUNIT_TEST( testCDtor );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
	void testCDtor();
};

#endif // _LIGHTHANDLEMANAGERTESTCASE_H_
