#ifndef _DECLARATIONMANAGERTESTCASE_H_
#define _DECLARATIONMANAGERTESTCASE_H_
#include <string>
#include <cppunit/extensions/HelperMacros.h>
#include <DeclarationManager.h>

class DeclarationManagerTestCase : public CPPUNIT_NS::TestFixture
{
  CPPUNIT_TEST_SUITE( DeclarationManagerTestCase );
  CPPUNIT_TEST( testCDtor );
  CPPUNIT_TEST( testDefaultDeclarations );
  CPPUNIT_TEST( testInlineDeclarations );
  CPPUNIT_TEST_SUITE_END();
public:
  void setUp();
  void tearDown();
  void testCDtor();
  void testDefaultDeclarations();
  void testInlineDeclarations();
};

#endif // _DECLARATIONMANAGERTESTCASE_H_
