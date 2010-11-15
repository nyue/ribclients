// -*- C++ -*-
#include <boost/test/included/unit_test.hpp>
#include <BasisManager.h>

BOOST_AUTO_TEST_SUITE (BasisManagerTestSuite) // name of the test suite is BasisManagerTestSuite

BOOST_AUTO_TEST_CASE ( testCDtor )
{
  BasisManager *tc = 0;
  try {
      tc = new BasisManager;
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
