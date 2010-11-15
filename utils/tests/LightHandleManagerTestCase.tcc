// -*- C++ -*-
#include <boost/test/included/unit_test.hpp>
#include <LightHandleManager.h>

BOOST_AUTO_TEST_SUITE (LightHandleManagerTestSuite) // name of the test suite is LightHandleManagerTestSuite

BOOST_AUTO_TEST_CASE ( testCDtor )
{
  LightHandleManager *tc = 0;
  try {
      tc = new LightHandleManager;
      BOOST_CHECK (tc != 0);
      if (tc != 0)
      {
          try {
              delete tc;
          }
          catch (...)
          {
              BOOST_ERROR ( "Exception in deleting ARchiveHandleManager object" );
          }
      }
  } catch (...) {
      BOOST_ERROR ( "Exception in creating ARchiveHandleManager object" );
  }
}

BOOST_AUTO_TEST_SUITE_END( )
