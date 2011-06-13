# RIBClient Utils library CMake configuration file

PROJECT ( utils )

IF (WIN32)
  SET (CMAKE_BUILD_TYPE "Release")
ENDIF (WIN32)

FIND_PACKAGE( Boost COMPONENTS unit_test_framework )

INCLUDE_DIRECTORIES ( ${Boost_INCLUDE_DIRS} )
LINK_DIRECTORIES ( ${Boost_LIBRARY_DIRS} )

INCLUDE_DIRECTORIES (
  $ENV{CPPUNIT_ROOT}/include
  $ENV{OPENEXR_ROOT}/include
  $ENV{ILMBASE_ROOT}/include
  $ENV{DELIGHT}/include
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

# ADD_EXECUTABLE ( unitTest
#   ./tests/main.cpp
#   ./tests/ArchiveHandleManagerTestCase.cpp
#   ./tests/BasisManagerTestCase.cpp
#   ./tests/ContextHandleManagerTestCase.cpp
#   ./tests/DeclarationManagerTestCase.cpp
#   ./tests/ErrorHandlerManagerTestCase.cpp
#   ./tests/FilterFuncManagerTestCase.cpp
#   ./tests/LightHandleManagerTestCase.cpp
#   ./tests/ObjectHandleManagerTestCase.cpp
#   ./tests/TParameterListTestCase.cpp
#   #  ./tests/ViewTransformTestSuite.cpp // Need to migrate code to use IMath
#   )

ADD_EXECUTABLE ( boostTest
  ./tests/BoostTestMain.cpp
  # Note: All the test code are in *.tcc templatize form and include in the
  # main entry BoostTestMain.cpp
  )

# TARGET_LINK_LIBRARIES ( unitTest utils log4cxx apr-1 aprutil-1 cppunit ${RIBCLIENT_LIBRARIES} )

TARGET_LINK_LIBRARIES ( boostTest utils ${RIBCLIENT_LIBRARIES} ${Boost_LIBRARIES} glog)

# ADD_TEST ( UnitTest unitTest )

ADD_TEST ( BoostTest boostTest )
