.SUFFIXES: .cxx .cpp .obj .i

OSNAME		= $(shell uname)

include ../utils/RIBClientRules.inc

SWIG			= swig
VPATH			= .

ifneq (,$(findstring CYGWIN_NT,$(OSNAME)))
  CC		=
  CXX		= cl.exe
  LINK		= link.exe
  CFLAGS	=
  CXXFLAGS	= /EHsc /MT $(RMAN_DEF)
  INCLUDES	= /I"..\utils" $(RMAN_INC)
  LIBRARIES	= /libpath:"..\utils" libutils.lib $(RMAN_LIB)
  EXT		= dll
  OEXT		= obj
  SHAREFLAG	= /DLL
  LIBOUT	= /OUT:
else
  CC		= gcc
  CXX		= g++
  LINK		= g++
  CFLAGS	=
  CXXFLAGS	= -ggdb3 $(RMAN_DEF)
  OEXT		= o
  LIBOUT	= -o # There is a space after the character 'o', keep it there
  LIBPREFIX	= lib
  ifneq (,$(findstring Linux,$(OSNAME)))
    INCLUDES	= -I../utils $(RMAN_INC) -I$(BOOST_INCLUDE)
    LIBRARIES	= -L../utils -lutils $(RMAN_LIB)
    EXT		= dll
    SHAREFLAG	= -shared
  else
    INCLUDES	= -I../utils $(RMAN_INC) -I$(BOOST_INCLUDE)
    LIBRARIES	= -L../utils -lutils $(RMAN_LIB)
    EXT		= so
    # SHAREFLAG	= -Wl,-F. -bundle -undefined dynamic_lookup # -dynamiclib
    SHAREFLAG	= -dynamiclib
  endif
endif

.cpp.$(OEXT):
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $<

SOURCES = 			\
	RIBClient_wrap.cxx	\
	ParameterList.cpp

CPP_OBJECTS = $(SOURCES:.cpp=.$(OEXT))
CXX_OBJECTS = $(SOURCES:.cxx=.$(OEXT))

all: RIBClient_wrap.cxx prib

prib: $(LIBPREFIX)ribclient.$(EXT)

utils:
	(cd ../utils;make clean all)

RIBClient_wrap.cxx : ../utils/RIBClient.i
	$(SWIG) -o $@ -c++ -csharp $(RMAN_SWIG_DEF) $<

RIBClient_wrap.$(OEXT) : RIBClient_wrap.cxx
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<

$(LIBPREFIX)ribclient.$(EXT): RIBClient_wrap.$(OEXT) ParameterList.$(OEXT)
	$(LINK) $(SHAREFLAG) $? $(LIBRARIES) $(LIBOUT)$@

clean:
	$(RM) *~ *.$(OEXT) *.$(EXT) *.lib *_wrap.cxx SWIGTYPE* *.rib *.a *.exp *PINVOKE.cs ribclient.cs *.exe *.dll

# Prototyping learning code
