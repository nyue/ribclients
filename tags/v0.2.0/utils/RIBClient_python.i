// -*- C++ -*-
// Procedural Insight 2007 

// Typemaps and other stuff specific to Python support

%typemap(in) (RtColor)
{
  // Python SWIG typemap for RtColor
  ParameterList::RtFloatVector fv;
  g_params.ConvertToRtFloatVector($input,fv);
#if defined(__GNUC__)
  if (fv.size() != 3)
    throw std::runtime_error("Color must have exactly 3 floating point components, we do not support different color samples yet");
#endif // (__GNUC__)
  memcpy($1, &(fv[0]), sizeof(RtColor));
}

%typemap(in) (RtBound)
{
  // Python SWIG typemap for RtBound
  ParameterList::RtFloatVector fv;
  g_params.ConvertToRtFloatVector($input,fv);
#if defined(__GNUC__)
  if (fv.size() != 6)
    throw std::runtime_error("Bounds must have exactly 6 floating point components");
#endif // (__GNUC__)
  memcpy($1, &(fv[0]), sizeof(RtBound));
}

%typemap(in) (RtMatrix)
{
  // Python SWIG typemap for RtMatrix
  ParameterList::RtFloatVector fv;
  g_params.ConvertToRtFloatVector($input,fv);
#if defined(__GNUC__)
  if (fv.size() != 16)
    throw std::runtime_error("Matrix must have exactly 16 floating point components");
#endif // (__GNUC__)
  memcpy($1, &(fv[0]), sizeof(RtMatrix));
}

%typemap(in) (RtBasis)
{
  if ($input != 0) {
    int basisIndex = (int) PyLong_AsLong($input);
    switch (basisIndex) {
    case BEZIERBASIS:
      memcpy($1, RiBezierBasis, sizeof(RtBasis));
      break;
    case BSPLINEBASIS:
      memcpy($1, RiBSplineBasis, sizeof(RtBasis));
      break;
    case CATMULLROMBASIS:
      memcpy($1, RiCatmullRomBasis, sizeof(RtBasis));
      break;
    case HERMITEBASIS:
      memcpy($1, RiHermiteBasis, sizeof(RtBasis));
      break;
    case POWERBASIS:
      memcpy($1, RiPowerBasis, sizeof(RtBasis));
      break;
    default:
      memcpy($1, RiBezierBasis, sizeof(RtBasis));
      break;
    }
  }
}

%typemap(in) (RtPoint)
{
  // Python SWIG typemap for RtPoint
  ParameterList::RtFloatVector fv;
  g_params.ConvertToRtFloatVector($input,fv);
#if defined(__GNUC__)
  if (fv.size() != 3)
    throw std::runtime_error("Point must have exactly 3 floating point components");
#endif // (__GNUC__)
  memcpy($1, &(fv[0]), sizeof(RtPoint));
}

%typemap(in) (RtInt n, RtToken tokens[], RtPointer params[])
{
  $1 = 0; // initialize to zero tokens/params pair, $1 is == n
  if ($input != NULL) {
    g_params.Reinitialize();
    g_params.ProcessParameterList($input);
    $1 = g_params.size();
    // std::cout << "g_params.size() returned " << $1 << std::endl;
    if ($1 > 0) {
      $2 = g_params.GetRIBClientCompatibleTokens();
      $3 = g_params.GetRIBClientCompatibleParms();
    } else {
      $2 = (RtToken *)0;
      $3 = (RtPointer *)0;
    }
  }
}

%typemap(in) RtInt
{
  $1 = 0;
  if ($input != 0) {
    $1 = (int) PyLong_AsLong($input);
  }
}

// RtLightHandle
%typemap(in) RtLightHandle
{
  // Python RtLightHandle processing
  PyInt_Check($input);
  int lhID = PyLong_AsLong($input);
  $1 = g_lhm.Get(lhID);
}

%typemap(ret) RtLightHandle
{
  // Python RtLightHandle processing
  int lhID = g_lhm.Add(result);
  resultobj = Py_BuildValue("i",lhID);

  // My clean up code for each call returning void
  g_params.CleanUpArgStorage();
}

// RtArchiveHandle
%typemap(in) RtArchiveHandle
{
  // Python RtArchiveHandle processing
  PyInt_Check($input);
  int ahID = PyLong_AsLong($input);
  $1 = g_ahm.Get(lhID);
}

%typemap(ret) RtArchiveHandle
{
  // Python RtArchiveHandle processing
  int ahID = g_ahm.Add(result);
  resultobj = Py_BuildValue("i",ahID);

  // My clean up code for each call returning void
  g_params.CleanUpArgStorage();
}

// RtObjectHandle
%typemap(in) RtObjectHandle
{
  // Python RtObjectHandle processing
  PyInt_Check($input);
  int ohID = PyLong_AsLong($input);
  $1 = g_ohm.Get(ohID);
}

%typemap(ret) RtObjectHandle
{
  // Python RtObjectHandle processing
  int ohID = g_ohm.Add(result);
  resultobj = Py_BuildValue("i",ohID);

  // My clean up code for each call returning void
  g_params.CleanUpArgStorage();
}

%typemap(in) RtArchiveCallback
{
}

%typemap(in) RtFilterFunc
{
  if ($input != 0) {
    int filterValue = (int) PyLong_AsLong($input);
    switch (filterValue) {
    case BOXFILTER:
      $1 = RiBoxFilter;
      break;
    case TRIANGLEFILTER:
      $1 = RiTriangleFilter;
      break;
    case CATMULLROMFILTER:
      $1 = RiCatmullRomFilter;
      break;
#if defined(PRMAN_RIBCLIENT) || defined(DELIGHT_RIBCLIENT)
    case BESSELFILTER:
      $1 = RiBesselFilter;
      break;
#endif
    case GAUSSIANFILTER:
      $1 = RiGaussianFilter;
      break;
    case SINCFILTER:
      $1 = RiSincFilter;
      break;
    case BLACKMANHARRISFILTER:
      $1 = RiBlackmanHarrisFilter;
      break;
    case MITCHELLFILTER:
      $1 = RiMitchellFilter;
      break;
    default:
      $1 = RiBoxFilter; // Check the RI Spec to find what is the default
      break;
    }
  }
}

%typemap(in) (RtInt[])
{
  // Python SWIG typemap for RtInt[]
  ParameterList::RtIntVector iv;
  g_params.ConvertToRtIntVector($input,iv);
  $1 = g_params.AddRtIntArrayArg(iv);
}

%typemap(in) (RtFloat[])
{
  // Python SWIG typemap for RtFloat[]
  ParameterList::RtFloatVector fv;
  g_params.ConvertToRtFloatVector($input,fv);
  $1 = g_params.AddRtFloatArrayArg(fv);
}

%typemap(in) (RtToken[])
{
  // Python SWIG typemap for RtToken[]
  ParameterList::StringVec sv;
  g_params.ConvertToSTLStringVector($input,sv);
  $1 = g_params.AddRtTokenArrayArg(sv);
}

