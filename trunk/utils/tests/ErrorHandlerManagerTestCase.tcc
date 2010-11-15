// -*- C++ -*-
#include <boost/test/included/unit_test.hpp>
#include <ErrorHandlerManager.h>

BOOST_AUTO_TEST_SUITE (ErrorHandlerManagerTestSuite) // name of the test suite is ErrorHandlerManagerTestSuite

BOOST_AUTO_TEST_CASE ( testCDtor )
{
  ErrorHandlerManager *tc = 0;
  try {
      tc = new ErrorHandlerManager;
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
