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
#include <rx.h>
#include <ParameterList.h>
 }%

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
