#ifndef _CONTEXTHANDLEMANAGERTESTCASE_H_
#define _CONTEXTHANDLEMANAGERTESTCASE_H_
#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <ContextHandleManager.h>

class ContextHandleManagerTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( ContextHandleManagerTestCase );
	CPPUNIT_TEST( testCDtor );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
	void testCDtor();
};

#endif // _CONTEXTHANDLEMANAGERTESTCASE_H_
