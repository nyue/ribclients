// -*- C++ -*-
// Procedural Insight 2007 

// Typemaps and other stuff specific to Ruby support

%typemap(in) (RtColor)
{
  // Ruby SWIG typemap for RtColor
  ParameterList::RtFloatVector fv;
  g_params.VALUE2RtFloatVector($input,fv);
  memcpy($1, &(fv[0]), sizeof(RtColor));
}

%typemap(in) (RtBound)
{
  // Ruby SWIG typemap for RtBound
  ParameterList::RtFloatVector fv;
  g_params.VALUE2RtFloatVector($input,fv);
  memcpy($1, &(fv[0]), sizeof(RtBound));
}

%typemap(in) (RtMatrix)
{
  // Ruby SWIG typemap for RtMatrix
  RtMatrix m;
  g_params.VALUE2RtMatrix($input,m);
  memcpy($1, m, sizeof(RtMatrix));
}

%typemap(in) (RtBasis)
{
  if ($input != 0) {
    switch ($input) {
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
  // Ruby SWIG typemap for RtPoint
  ParameterList::RtFloatVector fv;
  g_params.VALUE2RtFloatVector($input,fv);
  memcpy($1, &(fv[0]), sizeof(RtPoint));
}

%typemap(in) (RtInt n, RtToken tokens[], RtPointer params[])
{
  $1 = 0; // initialize to zero tokens/params pair, $1 is == n
  if (!NIL_P($input)) {
    Check_Type($input, T_HASH);
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

// RtLightHandle
%typemap(in) RtLightHandle
{
  // Ruby RtLightHandle processing
  if (TYPE($input) == T_FIXNUM || TYPE($input) == T_BIGNUM)
  {
    int lhID = NUM2INT($input);
    $1 = g_lhm.Get(lhID);
  }
  else
  {
    throw std::runtime_error("Integer value expected for light handle");
  }
}

%typemap(ret) RtLightHandle
{
  // Ruby RtLightHandle processing
  int lhID = g_lhm.Add(result);
  vresult = ULONG2NUM(lhID);

  // My clean up code for each call returning void
  g_params.CleanUpArgStorage();
}

// RtObjectHandle
%typemap(in) RtObjectHandle
{
  // Ruby RtObjectHandle processing
  if (TYPE($input) == T_FIXNUM || TYPE($input) == T_BIGNUM)
  {
    int ohID = NUM2INT($input);
    $1 = g_ohm.Get(ohID);
  }
  else
  {
    throw std::runtime_error("Integer value expected for object handle");
  }
}

%typemap(ret) RtObjectHandle
{
  // Ruby RtObjectHandle processing
  int ohID = g_ohm.Add(result);
  vresult = ULONG2NUM(ohID);

  // My clean up code for each call returning void
  g_params.CleanUpArgStorage();
}

%typemap(in) RtFilterFunc
{
  if (TYPE($input) != T_FIXNUM && TYPE($input) != T_BIGNUM)
  {
    throw std::runtime_error("Integer value expected for filter function");
  }
  if ($input != 0) {
    int filterValue = NUM2INT($input);
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
  // Ruby SWIG typemap for RtInt[]
  // std::cout << "SWIG_RUBY RtInt[]" << std::endl;
  ParameterList::RtIntVector iv;
  g_params.VALUE2RtIntVector($input,iv);
  $1 = g_params.AddRtIntArrayArg(iv);
}

%typemap(in) (RtFloat[])
{
  // Ruby SWIG typemap for RtFloat[]
  // std::cout << "SWIG_RUBY RtFloat[]" << std::endl;
  ParameterList::RtFloatVector fv;
  g_params.VALUE2RtFloatVector($input,fv);
  // g_RtFloatArrayStorage = fv;
  // $1 = &(g_RtFloatArrayStorage[0]);
  $1 = g_params.AddRtFloatArrayArg(fv);
}

%typemap(in) (RtToken[])
{
  // Ruby SWIG typemap for RtToken[]
  // std::cout << "SWIG_RUBY RtToken[]" << std::endl;
  ParameterList::StringVec sv;
  g_params.ConvertToSTLStringVector($input,sv);
  $1 = g_params.AddRtTokenArrayArg(sv);
}

%typemap(in) (RtString[])
{
  // Ruby SWIG typemap for RtString[]
  // std::cout << "SWIG_RUBY RtString[]" << std::endl;
  ParameterList::StringVec sv;
  g_params.ConvertToSTLStringVector($input,sv);
  $1 = g_params.AddRtTokenArrayArg(sv);
}
