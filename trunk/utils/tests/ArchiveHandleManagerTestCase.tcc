// -*- C++ -*-
#include <boost/test/included/unit_test.hpp>
#include <ArchiveHandleManager.h>

BOOST_AUTO_TEST_SUITE (ArchiveHandleManagerTestSuite) // name of the test suite is ArchiveHandleManagerTestSuite

BOOST_AUTO_TEST_CASE ( testCDtor )
{
  ArchiveHandleManager *tc = 0;
  try {
      tc = new ArchiveHandleManager;
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

