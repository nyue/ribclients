// -*- C++ -*-
#include <boost/test/included/unit_test.hpp>
#include <DeclarationManager.h>

BOOST_AUTO_TEST_SUITE ( DeclarationManagerTestCase )

BOOST_AUTO_TEST_CASE ( testCDtor )
{
  try {
    DeclarationManager tc;
  } catch (...) {
  }
}

BOOST_AUTO_TEST_CASE ( testDefaultDeclarations )
{
  DeclarationManager dm;

  DeclarationManager::DeclarationInfo di;
  // std::cout << "testDefaultDeclarations() START" << std::endl;

  di = dm.GetDeclarationInfo("Ka");
  // std::cout << di << std::endl;
  BOOST_CHECK(di._class == DeclarationManager::DeclarationInfo::VARYING);
  BOOST_CHECK(di._type == DeclarationManager::DeclarationInfo::FLOAT);
  BOOST_CHECK(di._arraysize == 0);

  di = dm.GetDeclarationInfo("st");
  // std::cout << di << std::endl;
  BOOST_CHECK(di._class == DeclarationManager::DeclarationInfo::VARYING);
  BOOST_CHECK(di._type == DeclarationManager::DeclarationInfo::FLOAT);
  BOOST_CHECK(di._arraysize == 2);

  di = dm.GetDeclarationInfo("from");
  // std::cout << di << std::endl;
  BOOST_CHECK(di._class == DeclarationManager::DeclarationInfo::VARYING);
  BOOST_CHECK(di._type == DeclarationManager::DeclarationInfo::FLOAT);
  BOOST_CHECK(di._arraysize == 3);

  // std::cout << "testDefaultDeclarations() END" << std::endl;
}

BOOST_AUTO_TEST_CASE ( testInlineDeclarations )
{
  DeclarationManager dm;

  DeclarationManager::DeclarationInfo di;
  std::cout << "testInlineDeclarations() START" << std::endl;

  di = dm.GetDeclarationInfo("uniform float nicholas");
  std::cout << di << std::endl;
  BOOST_CHECK(di._class == DeclarationManager::DeclarationInfo::UNIFORM);
  BOOST_CHECK(di._type == DeclarationManager::DeclarationInfo::FLOAT);
  BOOST_CHECK(di._arraysize == 0);

  di = dm.GetDeclarationInfo("varying float nicholas");
  std::cout << di << std::endl;
  BOOST_CHECK(di._class == DeclarationManager::DeclarationInfo::VARYING);
  BOOST_CHECK(di._type == DeclarationManager::DeclarationInfo::FLOAT);
  BOOST_CHECK(di._arraysize == 0);

  di = dm.GetDeclarationInfo("uniform vector nicholas");
  std::cout << di << std::endl;
  BOOST_CHECK(di._class == DeclarationManager::DeclarationInfo::UNIFORM);
  BOOST_CHECK(di._type == DeclarationManager::DeclarationInfo::VECTOR);
  BOOST_CHECK(di._arraysize == 0);

  di = dm.GetDeclarationInfo("uniform point nicholas");
  std::cout << di << std::endl;
  BOOST_CHECK(di._class == DeclarationManager::DeclarationInfo::UNIFORM);
  BOOST_CHECK(di._type == DeclarationManager::DeclarationInfo::POINT);
  BOOST_CHECK(di._arraysize == 0);

  di = dm.GetDeclarationInfo("uniform string nicholas");
  std::cout << di << std::endl;
  BOOST_CHECK(di._class == DeclarationManager::DeclarationInfo::UNIFORM);
  BOOST_CHECK(di._type == DeclarationManager::DeclarationInfo::STRING);
  BOOST_CHECK(di._arraysize == 0);

  std::cout << "testInlineDeclarations() END" << std::endl;
}

BOOST_AUTO_TEST_SUITE_END( )
