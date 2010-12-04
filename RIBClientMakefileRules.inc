#
# Pixie
#
ifeq ($(RIBCLIENT),PIXIE)
  RMAN_INC	= -I"$(PIXIEHOME)/include"
ifneq (,$(findstring CYGWIN_NT,$(OSNAME)))
  RMAN_DEF	= -DPIXIE_RIBCLIENT -DWIN32
  RMAN_LIB	= "$(PIXIEHOME)\lib\ri_static.lib" "$(PIXIEHOME)\lib\common_static.lib" ws2_32.lib "C:\devtools\tiff-3.8.2\libtiff\libtiff.lib"
else
  RMAN_DEF	= -DPIXIE_RIBCLIENT
  RMAN_SWIG_DEF	= -DPIXIE_RIBCLIENT
ifneq (,$(findstring Linux,$(OSNAME)))
  RMAN_LIB	= $(PIXIEHOME)/lib/libri.a $(PIXIEHOME)/lib/libpixiecommon.a /usr/lib/libtiff.a /usr/lib/libjpeg.a /usr/lib/libz.a
else
  RMAN_LIB	= $(PIXIEHOME)/lib/libri.a $(PIXIEHOME)/lib/libpixiecommon.a /opt/local/lib/libtiff.a /opt/local/lib/libjpeg.a /opt/local/lib/libz.a
endif
endif
endif

#
# Pixar PRMan
#
ifeq ($(RIBCLIENT),PRMAN)
  RMAN_INC	= -I$(RMANTREE)/include
  RMAN_DEF	= -DPRMAN_RIBCLIENT
ifneq (,$(findstring CYGWIN_NT,$(OSNAME)))
  RMAN_DEF	= -DPRMAN_RIBCLIENT -DWIN32
  RMAN_LIB	= /libpath:$(RMANTREE)/lib rib.lib target.lib zip.lib prmutil.lib
else
  RMAN_DEF	= -DPRMAN_RIBCLIENT
  RMAN_LIB	= -L$(RMANTREE)/lib -lrib -ltarget -lzip -lprmutil
endif
endif

#
# 3Delight
#
ifeq ($(RIBCLIENT),DELIGHT)
  RMAN_INC	= -I"$(DELIGHT)/include"
ifneq (,$(findstring CYGWIN_NT,$(OSNAME)))
  RMAN_DEF	= /DDELIGHT_RIBCLIENT
  RMAN_SWIG_DEF	= -DDELIGHT_RIBCLIENT
  RMAN_LIB	= /libpath:"$(DELIGHT)/lib" 3delight.lib
else
  RMAN_DEF	= -DDELIGHT_RIBCLIENT
  RMAN_LIB	= -L$(DELIGHT)/lib -l3delight
endif
endif

#
# Aqsis
#
ifeq ($(RIBCLIENT),AQSIS)
  RMAN_INC	= -I"$(AQSISHOME)/include/aqsis"
  RMAN_DEF	= -DAQSIS_RIBCLIENT
endif

#
# RenderDotC
#
ifeq ($(RIBCLIENT),RDC)
  RMAN_INC	= -I"$(RDCROOT)/include"
  RMAN_DEF	= -DRDC_RIBCLIENT
endif

ifeq ($(RMAN_DEF),)
	echo "No RIB client defined"
endif
