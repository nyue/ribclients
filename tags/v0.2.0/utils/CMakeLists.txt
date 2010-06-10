# RIBClient Utils library CMake configuration file

PROJECT ( utils )

INCLUDE_DIRECTORIES (
  $ENV{CPPUNIT_ROOT}/include
  $ENV{OPENEXR_ROOT}/include
  $ENV{ILMBASE_ROOT}/include
  $ENV{DELIGHT}/include
  /usr/share/swig1.3
  $ENV{PYTHON_INCLUDE}
  $ENV{RUBY_INCLUDE}
  $ENV{JAVA_INCLUDE} )

LINK_DIRECTORIES (
  $ENV{CPPUNIT_ROOT}/lib
  $ENV{OPENEXR_ROOT}/lib
  $ENV{ILMBASE_ROOT}/lib
  $ENV{DELIGHT}/lib )

ADD_LIBRARY ( utils STATIC
  DeclarationManager.cpp
  BasisManager.cpp
  FilterFuncManager.cpp
  LightHandleManager.cpp
  ObjectHandleManager.cpp
  ContextHandleManager.cpp
  ArchiveHandleManager.cpp
  ErrorHandlerManager.cpp )

ADD_EXECUTABLE ( unitTest
  ./tests/main.cpp
  ./tests/ArchiveHandleManagerTestCase.cpp
  ./tests/BasisManagerTestCase.cpp
  ./tests/ContextHandleManagerTestCase.cpp
  ./tests/DeclarationManagerTestCase.cpp
  ./tests/ErrorHandlerManagerTestCase.cpp
  ./tests/FilterFuncManagerTestCase.cpp
  ./tests/LightHandleManagerTestCase.cpp
  ./tests/ObjectHandleManagerTestCase.cpp
  ./tests/TParameterListTestCase.cpp
  #  ./tests/ViewTransformTestSuite.cpp // Need to migrate code to use IMath
  )

TARGET_LINK_LIBRARIES ( unitTest utils ${LOG4CXX_LIBRARIES} apr-1 aprutil-1 cppunit ${RIBCLIENT_LIBRARIES} )

ADD_TEST ( UnitTest unitTest )
