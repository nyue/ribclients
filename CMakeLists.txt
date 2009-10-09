# Top level CMake configuration file
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT ( ribclients )

INCLUDE (FindSWIG)
INCLUDE (UseSWIG)

INCLUDE_DIRECTORIES ( ./utils )
INCLUDE_DIRECTORIES ( $ENV{CPPUNIT_ROOT}/include )
INCLUDE_DIRECTORIES ( $ENV{OPENEXR_ROOT}/include )
INCLUDE_DIRECTORIES ( $ENV{ILMBASE_ROOT}/include )

LINK_DIRECTORIES ( $ENV{CPPUNIT_ROOT}/lib )
LINK_DIRECTORIES ( $ENV{OPENEXR_ROOT}/lib )
LINK_DIRECTORIES ( $ENV{ILMBASE_ROOT}/lib )

# Renderer specific options
IF ( RENDERER MATCHES "PRMan" )
  INCLUDE_DIRECTORIES ( $ENV{RMANTREE}/include )
  LINK_DIRECTORIES ( $ENV{RMANTREE}/lib . )
  ADD_DEFINITIONS ( -DPRMAN_RIBCLIENT -fPIC )
  SET ( RIBCLIENT_LIBRARIES prman )
ELSEIF ( RENDERER MATCHES "3Delight" )
  INCLUDE_DIRECTORIES ( $ENV{DELIGHT}/include )
  LINK_DIRECTORIES ( $ENV{DELIGHT}/lib . )
  ADD_DEFINITIONS ( -DDELIGHT -DDELIGHT_RIBCLIENT -fPIC )
  SET ( RIBCLIENT_LIBRARIES 3delight )
ELSE ( RENDERER MATCHES "3Delight" )
ENDIF ( RENDERER MATCHES "PRMan")


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
