// -*- C++ -*-
#include <boost/test/included/unit_test.hpp>
#include <ObjectHandleManager.h>

BOOST_AUTO_TEST_SUITE (ObjectHandleManagerTestSuite) // name of the test suite is ObjectHandleManagerTestSuite

BOOST_AUTO_TEST_CASE ( testCDtor )
{
  ObjectHandleManager *tc = 0;
  try {
      tc = new ObjectHandleManager;
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
