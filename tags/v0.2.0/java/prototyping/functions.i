// -*- C++ -*-
// Procedural Insight 2007 

%module functions
%include "arrays_java.i"

%{
#include "functions.h"
%}

%typemap(in) float fm[4][4]
{
  // ... 2D arrays ...
}
%typemap(jni)    (float fm[4][4]) "jobject"
%typemap(jtype)  (float fm[4][4]) "float[][]"
%typemap(jstype) (float fm[4][4]) "float[][]"
%typemap(javain) (float fm[4][4]) "$javainput"

extern void SingleFloat(float f);

extern void FloatVector(float fv[3] );

extern void FloatMatrix(float fm[4][4]);
