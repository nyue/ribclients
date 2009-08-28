#include "FilterFuncManager.h"

FilterFuncManager::FilterFuncManager()
  : _lastUserFilterFuncID(0)
{
  Initialize();
}

FilterFuncManager::~FilterFuncManager()
{
}

void FilterFuncManager::Initialize()
{
  Set(&RiBoxFilter,            BOXFILTER);
  Set(&RiTriangleFilter,       TRIANGLEFILTER);
  Set(&RiCatmullRomFilter,     CATMULLROMFILTER);
#if (defined VERIFY_RIBCLIENT) || (defined DELIGHT_RIBCLIENT)
  Set(&RiBesselFilter,         BESSELFILTER);
#endif 
  Set(&RiGaussianFilter,       GAUSSIANFILTER);
  Set(&RiSincFilter,           SINCFILTER);
  Set(&RiBlackmanHarrisFilter, BLACKMANHARRISFILTER);
  Set(&RiMitchellFilter,       MITCHELLFILTER);
}

void FilterFuncManager::DebugPrintAll()
{
}

size_t FilterFuncManager::size() const
{
  return _filterfunc.size();
}

void FilterFuncManager::Get(RtFilterFunc& filterFunc, int filterFuncID)
{
  filterFunc = _filterfunc[filterFuncID];
}

void FilterFuncManager::Set(RtFilterFunc newFilterfunc, int filterFuncID)
{
  _filterfunc[filterFuncID] = newFilterfunc;
}
