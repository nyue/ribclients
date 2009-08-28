#ifndef _OBJECTHANDLEMANAGERTESTCASE_H_
#define _OBJECTHANDLEMANAGERTESTCASE_H_
#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <ObjectHandleManager.h>

class ObjectHandleManagerTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( ObjectHandleManagerTestCase );
	CPPUNIT_TEST( testCDtor );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
	void testCDtor();
};

#endif // _OBJECTHANDLEMANAGERTESTCASE_H_
