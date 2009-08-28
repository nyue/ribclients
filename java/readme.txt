


WINDOWS compilation and test

% make clean all

% javac -classpath . TestProto.java
% java -classpath . TestProto

% javac -classpath . TestRIBClient.java
% java -classpath . TestRIBClient

This is the expected output

Testing Java RIBClient library
##RenderMan RIB
version 3.04
FrameBegin 4
Projection "perspective"
WorldBegin
WorldEnd
FrameEnd

NOTES:
1. API.i is a simple SWIG file for learning about SWIG
2. functions.cpp/functions.h is a set of API function which we are wrapping
   as a practice.

TODO:
Implement ProcessParameterList method. Possible strategy is
1. Treat parameterlist as hashtable (as like PostHorizon) i.e. Key/Value pair
2. Key is a string token (matching Java's native string if possible)
3. Value is a standard Java homogeneous collection/array of either string,
   integer or float
4. The basic setup code can be copied from other language binding, the
   difficulty is probably around understanding how to map a "jobject" to
   various Java container/data types.

DESIGN
1. After speaking to Brendan Donovan at Animal Logic, I have decided to *not*
   handle Float/Double/Integer and only allow primitive types like
   float/double/int. There is a performance penalty in the first class object
   version of the primitive types. As I am not benefiting from the object
   incarnation of the primitive type, I do not wish to pay the performance
   penalty.
