#ifndef _TPARAMETERLISTTESTCASE_H_
#define _TPARAMETERLISTTESTCASE_H_
#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <TParameterList.h>

class TParameterListTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( TParameterListTestCase );
	CPPUNIT_TEST( testCDtor );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
	void testCDtor();
};

#endif // _TPARAMETERLISTTESTCASE_H_
