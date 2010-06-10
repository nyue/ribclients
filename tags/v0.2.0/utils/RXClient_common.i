// -*- C++ -*-
// Visual Information Insight 2010

%{
#if _MSC_VER < 1300
#pragma warning(disable:4786)
#undef read
#undef write
#endif
    %}

%module rxclient

%{
#include <ri.h> 
#include <rx.h>
#include <iostream>
#include <ParameterList.h>
    %}

#if (defined SWIGJAVA)
// %include "RIBClient_java.i"

typedef float RtFloat;
typedef int RtInt;
typedef char* RtToken;
typedef int RtFilterFunc;
typedef int RtArchiveCallback;
typedef int RtBasis;
typedef float RtMatrix[4][4];
typedef float RtColor[];
typedef bool RtBoolean;

#elif defined(SWIGPYTHON)

typedef long RtFilterFunc;
typedef void* RtArchiveCallback;
typedef float RtFloat;
typedef char* RtToken;
typedef char* RtString;
typedef bool RtBoolean;

// %include "RIBClient_python.i"

#elif defined(SWIGRUBY)

typedef char* RtToken;
typedef char* RtString;
typedef float RtFloat;
typedef bool RtBoolean;
typedef int RtInt;

#elif defined(SWIGCSHARP)
#else
#endif

%rename (Texture) RxTextureV;
RtInt
RxTextureV(RtString i_fileName,
	   RtInt i_firstChannel,
	   RtInt i_nChannels,
	   RtFloat i_s0,
	   RtFloat i_t0,
	   RtFloat i_s1,
	   RtFloat i_t1,
	   RtFloat i_s2,
	   RtFloat i_t2,
	   RtFloat i_s3,
	   RtFloat i_t3,
	   RtFloat *o_result,
	   RtInt i_n,
	   RtToken i_tokens[],
	   RtPointer i_parms[]);

%rename (Option) RxOption;
RtInt RxOption (RtToken i_name,
                RtPointer o_result,
                RtInt i_resultLen,
                RxInfoType_t *o_resulttype,
                RtInt *o_resultcount);
