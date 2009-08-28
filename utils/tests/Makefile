.SUFFIXES: .cpp .obj .o

VECMATH		= ../../../../general/vecmath
VPATH		= ../../src
INCLUDES	= -I.. -I$(CPPUNIT_ROOT)/include -I$(RMANTREE)/include \
		  -I$(VECMATH)
LIBRARIES	= -L$(CPPUNIT_ROOT)/lib -lcppunit -L.. -lutils \
		  -L$(RMANTREE)/lib -lrib -ltarget -lzip -lprmutil

OSNAME		= $(shell uname)

.cpp.o:
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $<

CPP_SOURCES =					\
	ArchiveHandleManagerTestCase.cpp	\
	BasisManagerTestCase.cpp		\
	ContextHandleManagerTestCase.cpp	\
	DeclarationManagerTestCase.cpp		\
	ErrorHandlerManagerTestCase.cpp		\
	FilterFuncManagerTestCase.cpp		\
	LightHandleManagerTestCase.cpp		\
	ObjectHandleManagerTestCase.cpp		\
	TParameterListTestCase.cpp		\
	ViewTransformTestSuite.cpp		\
	main.cpp


CPP_OBJECTS = $(CPP_SOURCES:.cpp=.o)

all: TestUtils
	@echo $(OSNAME)
	@echo $(RMANTREE)

TestUtils: $(CPP_OBJECTS)
	$(CXX) -o $@ $(CPP_OBJECTS) $(LIBRARIES)

utils:
	(cd ../utils;env DEBUG=1 RIBCLIENT=PRMAN make clean all)

clean:
	$(RM) *~ *.o TestUtils *.xml
