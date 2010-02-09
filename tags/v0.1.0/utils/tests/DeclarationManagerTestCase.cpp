#include "DeclarationManagerTestCase.h"

CPPUNIT_TEST_SUITE_REGISTRATION( DeclarationManagerTestCase );

void DeclarationManagerTestCase::setUp()
{
}

void DeclarationManagerTestCase::tearDown()
{
}

void DeclarationManagerTestCase::testCDtor()
{
  try {
    DeclarationManager tc;
  } catch (...) {
  }
}

void DeclarationManagerTestCase::testDefaultDeclarations()
{
  DeclarationManager dm;

  DeclarationManager::DeclarationInfo di;
  // std::cout << "testDefaultDeclarations() START" << std::endl;

  di = dm.GetDeclarationInfo("Ka");
  // std::cout << di << std::endl;
  CPPUNIT_ASSERT(di._class == DeclarationManager::DeclarationInfo::VARYING);
  CPPUNIT_ASSERT(di._type == DeclarationManager::DeclarationInfo::FLOAT);
  CPPUNIT_ASSERT(di._arraysize == 0);

  di = dm.GetDeclarationInfo("st");
  // std::cout << di << std::endl;
  CPPUNIT_ASSERT(di._class == DeclarationManager::DeclarationInfo::VARYING);
  CPPUNIT_ASSERT(di._type == DeclarationManager::DeclarationInfo::FLOAT);
  CPPUNIT_ASSERT(di._arraysize == 2);

  di = dm.GetDeclarationInfo("from");
  // std::cout << di << std::endl;
  CPPUNIT_ASSERT(di._class == DeclarationManager::DeclarationInfo::VARYING);
  CPPUNIT_ASSERT(di._type == DeclarationManager::DeclarationInfo::FLOAT);
  CPPUNIT_ASSERT(di._arraysize == 3);

  // std::cout << "testDefaultDeclarations() END" << std::endl;
}

void DeclarationManagerTestCase::testInlineDeclarations()
{
  DeclarationManager dm;

  DeclarationManager::DeclarationInfo di;
  std::cout << "testInlineDeclarations() START" << std::endl;

  di = dm.GetDeclarationInfo("uniform float nicholas");
  std::cout << di << std::endl;
  CPPUNIT_ASSERT(di._class == DeclarationManager::DeclarationInfo::UNIFORM);
  CPPUNIT_ASSERT(di._type == DeclarationManager::DeclarationInfo::FLOAT);
  CPPUNIT_ASSERT(di._arraysize == 0);

  di = dm.GetDeclarationInfo("varying float nicholas");
  std::cout << di << std::endl;
  CPPUNIT_ASSERT(di._class == DeclarationManager::DeclarationInfo::VARYING);
  CPPUNIT_ASSERT(di._type == DeclarationManager::DeclarationInfo::FLOAT);
  CPPUNIT_ASSERT(di._arraysize == 0);

  di = dm.GetDeclarationInfo("uniform vector nicholas");
  std::cout << di << std::endl;
  CPPUNIT_ASSERT(di._class == DeclarationManager::DeclarationInfo::UNIFORM);
  CPPUNIT_ASSERT(di._type == DeclarationManager::DeclarationInfo::VECTOR);
  CPPUNIT_ASSERT(di._arraysize == 0);

  di = dm.GetDeclarationInfo("uniform point nicholas");
  std::cout << di << std::endl;
  CPPUNIT_ASSERT(di._class == DeclarationManager::DeclarationInfo::UNIFORM);
  CPPUNIT_ASSERT(di._type == DeclarationManager::DeclarationInfo::POINT);
  CPPUNIT_ASSERT(di._arraysize == 0);

  di = dm.GetDeclarationInfo("uniform string nicholas");
  std::cout << di << std::endl;
  CPPUNIT_ASSERT(di._class == DeclarationManager::DeclarationInfo::UNIFORM);
  CPPUNIT_ASSERT(di._type == DeclarationManager::DeclarationInfo::STRING);
  CPPUNIT_ASSERT(di._arraysize == 0);

  std::cout << "testInlineDeclarations() END" << std::endl;
}
