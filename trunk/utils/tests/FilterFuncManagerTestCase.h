#ifndef _FILTERFUNCMANAGERTESTCASE_H_
#define _FILTERFUNCMANAGERTESTCASE_H_
#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <FilterFuncManager.h>

class FilterFuncManagerTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( FilterFuncManagerTestCase );
	CPPUNIT_TEST( testCDtor );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
	void testCDtor();
};

#endif // _FILTERFUNCMANAGERTESTCASE_H_
