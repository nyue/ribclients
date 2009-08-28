#ifndef _VIEWTRANSFORMTESTSUITE_
#define _VIEWTRANSFORMTESTSUITE_

#include <cppunit/extensions/HelperMacros.h>
#include <VecMatUtils.h>

/*!
 *
 * Templatize Test suite for ViewTransform
 *
 */

template <typename T>
class ViewTransformTestSuite : public CPPUNIT_NS::TestFixture
{
  PI::VecMatUtils<T> utils;
public:
  ViewTransformTestSuite(){};
  void setUp();
  void tearDown();
  void testConstructor();
  void testFromRHCS();
};

class FloatViewTransformTestSuite : public ViewTransformTestSuite<float>
{
  CPPUNIT_TEST_SUITE( FloatViewTransformTestSuite );
  CPPUNIT_TEST( testConstructor );
  // CPPUNIT_TEST( testFromRHCS );
  CPPUNIT_TEST_SUITE_END();
};

class DoubleViewTransformTestSuite : public ViewTransformTestSuite<double>
{
  CPPUNIT_TEST_SUITE( DoubleViewTransformTestSuite );
  CPPUNIT_TEST( testConstructor );
  // CPPUNIT_TEST( testFromRHCS );
  CPPUNIT_TEST_SUITE_END();
};

CPPUNIT_TEST_SUITE_REGISTRATION( FloatViewTransformTestSuite );
CPPUNIT_TEST_SUITE_REGISTRATION( DoubleViewTransformTestSuite );

#endif // _VIEWTRANSFORMTESTSUITE_
