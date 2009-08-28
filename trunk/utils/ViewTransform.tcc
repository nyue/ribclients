// -*- C++ -*-                                                                 
//                                                                             
// Procedural Insight 2007                                                     
// 

#include <Point3.h>
#include <Vector3.h>
#include <Matrix4.h>

template <typename T> const PI::VecMatUtils<T> ViewTransform<T>::utils = PI::VecMatUtils<T>();

template <typename T>
ViewTransform<T>::ViewTransform()
{
}

template <typename T>
ViewTransform<T>::~ViewTransform()
{
}

template <typename T>
void ViewTransform<T>::FromRHCS(const T eye_[3], const T target_[3],
				const T upVector_[3], T matrix_1[4][4])
{
  PI::Point3<T> eye(eye_[0],eye_[1],eye_[2]);
  PI::Point3<T> target(target_[0],target_[1],target_[2]);
  PI::Vector3<T> upvector(upVector_[0],upVector_[1],upVector_[2]);
  upvector.normalize();

  std::cout << "camera : " << eye << std::endl;
  std::cout << "aim : " << target << std::endl;
  std::cout << "aim_up : " << upvector << std::endl;

  PI::Vector3<T> v3 = eye - target;

  v3.normalize();
  PI::Vector3<T> v1 = upvector ^ v3;
  v1.normalize();
  PI::Vector3<T> v2 = v1 ^ v3;
  v2.normalize();

  std::cout << v3 << std::endl;
  std::cout << v1 << std::endl;
  std::cout << v2 << std::endl;

  T matrix[4][4] = {
    { v1.x, v1.y, v1.z, 0},
    { v2.x, v2.y, v2.z, 0},
    { v3.x, v3.y, v3.z, 0},
    { 0   , 0   , 0   , 1}
  };
  PI::Matrix4<T> m(matrix);

  std::cout << m << std::endl;

  PI::Matrix4<T> m_1 = m.inverse();

  std::cout << m_1 << std::endl;

  m_1.get(matrix_1);
  matrix_1[0][1] = -matrix_1[0][1];
  matrix_1[1][1] = -matrix_1[1][1];
  matrix_1[2][1] = -matrix_1[2][1];

  /*
  RiScale(1,1,-1);
  RiCoordinateSystem("RHCS_Camera");
  RiConcatTransform(matrix_1);
  RiTranslate(-eye.x,eye.y,-eye.z);
  */
}
