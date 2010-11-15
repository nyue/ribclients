// -*- C++ -*-
#include <boost/test/included/unit_test.hpp>
#include <ContextHandleManager.h>

BOOST_AUTO_TEST_SUITE (ContextHandleManagerTestSuite) // name of the test suite is ContextHandleManagerTestSuite

BOOST_AUTO_TEST_CASE ( testCDtor )
{
  ContextHandleManager *tc = 0;
  try {
      tc = new ContextHandleManager;
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
