# Top level CMake configuration file
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT ( ribclients )

INCLUDE (FindSWIG)
INCLUDE (UseSWIG)
INCLUDE (FindLog4cxx)

IF ( CMAKE_BUILD_TYPE MATCHES "Debug")
    ADD_DEFINITIONS ( -DDEBUG )
ENDIF ( CMAKE_BUILD_TYPE MATCHES "Debug")

# Renderer specific options
IF ( RENDERER MATCHES "PRMan" )
  INCLUDE_DIRECTORIES ( $ENV{RMANTREE}/include )
  LINK_DIRECTORIES ( $ENV{RMANTREE}/lib . )
  IF (WIN32)
    ADD_DEFINITIONS ( -DPRMAN_RIBCLIENT )
  ELSE (WIN32)
    ADD_DEFINITIONS ( -DPRMAN_RIBCLIENT -fPIC )
  ENDIF (WIN32)
  SET ( RIBCLIENT_LIBRARIES prman )
ELSEIF ( RENDERER MATCHES "3Delight" )
  INCLUDE_DIRECTORIES ( $ENV{DELIGHT}/include )
  LINK_DIRECTORIES ( $ENV{DELIGHT}/lib )
  IF (WIN32)
    ADD_DEFINITIONS ( -DDELIGHT -DDELIGHT_RIBCLIENT -DLOG4CXX_STATIC)
  ELSE (WIN32)
    ADD_DEFINITIONS ( -DDELIGHT -DDELIGHT_RIBCLIENT -fPIC )
  ENDIF (WIN32)
  SET ( RIBCLIENT_LIBRARIES 3delight )
ELSE ( RENDERER MATCHES "3Delight" )
ENDIF ( RENDERER MATCHES "PRMan")

INCLUDE_DIRECTORIES ( ./utils )
# INCLUDE_DIRECTORIES ( $ENV{CPPUNIT_ROOT}/include )

# LINK_DIRECTORIES ( $ENV{CPPUNIT_ROOT}/lib )

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
