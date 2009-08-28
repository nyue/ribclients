# RIBClient CMake configuration file

PROJECT ( utils )

INCLUDE_DIRECTORIES ( $ENV{CPPUNIT_ROOT}/include $ENV{OPENEXR_ROOT}/include $ENV{ILMBASE_ROOT}/include $ENV{DELIGHT}/include /usr/share/swig1.3 $ENV{PYTHON_INCLUDE} $ENV{RUBY_INCLUDE} $ENV{JAVA_INCLUDE} )

LINK_DIRECTORIES ( $ENV{CPPUNIT_ROOT}/lib $ENV{OPENEXR_ROOT}/lib $ENV{ILMBASE_ROOT}/lib $ENV{DELIGHT}/lib )

ADD_LIBRARY ( utils STATIC DeclarationManager.cpp BasisManager.cpp FilterFuncManager.cpp LightHandleManager.cpp ObjectHandleManager.cpp ContextHandleManager.cpp ArchiveHandleManager.cpp ErrorHandlerManager.cpp )
