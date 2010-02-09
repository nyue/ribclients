#ifndef _ARCHIVEHANDLEMANAGERTESTCASE_H_
#define _ARCHIVEHANDLEMANAGERTESTCASE_H_
#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <ArchiveHandleManager.h>

class ArchiveHandleManagerTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( ArchiveHandleManagerTestCase );
	CPPUNIT_TEST( testCDtor );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
	void testCDtor();
};

#endif // _ARCHIVEHANDLEMANAGERTESTCASE_H_
