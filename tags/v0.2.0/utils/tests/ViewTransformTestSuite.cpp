#include "ViewTransformTestSuite.h"
#include <iostream>
#include <cmath>

#include <Point3.h>
#include <Matrix4.h>
#include <ViewTransform>

template <typename T>
void ViewTransformTestSuite<T>::setUp()
{
}

template <typename T>
void ViewTransformTestSuite<T>::tearDown()
{
}

template <typename T>
void ViewTransformTestSuite<T>::testConstructor()
{
  try {
    ViewTransform<T> vt;
  }
  catch (...) {
    CPPUNIT_FAIL("Exception raised while constructing ViewTransform object");
  }
}

template <typename T>
void ViewTransformTestSuite<T>::testFromRHCS()
{
  T eye[3] = {0,0,20};
  T target[3] = {-6,0,-5};
  T upPt[3] = {0,10,0};
  T up[3] = {upPt[0]-eye[0],
	     upPt[1]-eye[1],
	     upPt[2]-eye[2]};
  T matrix[4][4];
  ViewTransform<T> vt;
  try {
    vt.FromRHCS(eye,target,up,matrix);
    T expected_matrix[4][4] = {
      {  0.8811342,    0.4112658,  0.23337298, -0},
      {-0.42294448,    0.9061555,          -0, -0},
      {-0.21147221, -0.098703795,   0.9723874, -0},
      {         -0,           -0,          -0,  1}
    };
    PI::Matrix4<T> expectedMatrix4(expected_matrix);
    PI::Matrix4<T> calculatedMatrix4(matrix);
    std::cout << "expectedMatrix4 : " << expectedMatrix4 << std::endl;
    std::cout << "calculatedMatrix4 : " << calculatedMatrix4 << std::endl;
    CPPUNIT_ASSERT(calculatedMatrix4.isEquivalent(expectedMatrix4,0.00000001));
  }
  catch (...) {
    CPPUNIT_FAIL("Exception raised in call to method FromRHCS()");
  }
}
