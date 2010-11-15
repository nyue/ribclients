// -*- C++ -*-
#include <boost/test/included/unit_test.hpp>
#include <FilterFuncManager.h>

BOOST_AUTO_TEST_SUITE (FilterFuncManagerTestSuite) // name of the test suite is FilterFuncManagerTestSuite

BOOST_AUTO_TEST_CASE ( testCDtor )
{
  FilterFuncManager *tc = 0;
  try {
      tc = new FilterFuncManager;
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
