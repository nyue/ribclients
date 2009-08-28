# Top level CMake configuration file
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT ( ribclients )

INCLUDE (FindSWIG)
INCLUDE (UseSWIG)

INCLUDE_DIRECTORIES ( ./utils )
INCLUDE_DIRECTORIES ( $ENV{CPPUNIT_ROOT}/include )
INCLUDE_DIRECTORIES ( $ENV{OPENEXR_ROOT}/include )
INCLUDE_DIRECTORIES ( $ENV{ILMBASE_ROOT}/include )
INCLUDE_DIRECTORIES ( $ENV{DELIGHT}/include )

LINK_DIRECTORIES ( $ENV{CPPUNIT_ROOT}/lib )
LINK_DIRECTORIES ( $ENV{OPENEXR_ROOT}/lib )
LINK_DIRECTORIES ( $ENV{ILMBASE_ROOT}/lib )
LINK_DIRECTORIES ( $ENV{DELIGHT}/lib . )

ADD_DEFINITIONS ( -DDELIGHT -DDELIGHT_RIBCLIENT -fPIC )

ADD_LIBRARY ( utils STATIC
  utils/DeclarationManager.cpp
  utils/BasisManager.cpp
  utils/FilterFuncManager.cpp
  utils/LightHandleManager.cpp
  utils/ObjectHandleManager.cpp
  utils/ContextHandleManager.cpp
  utils/ArchiveHandleManager.cpp
  utils/ErrorHandlerManager.cpp
  )

# ADD_SUBDIRECTORY ( java )

ADD_SUBDIRECTORY ( python )

# ADD_SUBDIRECTORY ( ruby )
