// -*- C++ -*-
// Procedural Insight 2007 

// Typemaps and other stuff specific to C# support

%typemap(in) (RtColor)
{
  // C# SWIG typemap for RtColor
  memcpy($1, $input, sizeof(RtColor));
}

%typemap(in) (RtBound)
{
  // Ruby SWIG typemap for RtBound
  memcpy($1, $input, sizeof(RtBound));
}

%typemap(in) (RtMatrix)
{
  // C# SWIG typemap for RtMatrix
  memcpy($1, $input, sizeof(RtMatrix));
}

%typemap(in) (RtPoint)
{
  // C# SWIG typemap for RtPoint
  memcpy($1, $input, sizeof(RtPoint));
}

%typemap(in) (RtBasis)
{
  if ($input != 0) {
    int* chosenBasis = (int *)($input);
    switch (*chosenBasis) {
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

%typemap(in) (RtInt n, RtToken tokens[], RtPointer params[])
{
  // Parameter list handling
}

%typemap(in) RtFilterFunc
{
  if ($input != 0) {
    int filterValue = 0;
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
