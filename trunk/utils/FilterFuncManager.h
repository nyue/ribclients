#ifndef _FILTERFUNCMANAGER_H_
#define _FILTERFUNCMANAGER_H_

#include <ri.h>
#include <map>

/*!
  \brief Manages the filter function but more importantly, this is designed
  to allow for additional filter function via static member method (?)
 */
class FilterFuncManager
{
  typedef std::map<int, RtFilterFunc> RtFilterFuncContainer;
public:
  // Pre-defined filters
  enum {
    BOXFILTER            = -1,
    TRIANGLEFILTER       = -2,
    CATMULLROMFILTER     = -3,
    BESSELFILTER         = -4,
    GAUSSIANFILTER       = -5,
    SINCFILTER           = -6,
    BLACKMANHARRISFILTER = -7,
    MITCHELLFILTER       = -8
  };
  FilterFuncManager();
  virtual ~FilterFuncManager();
  void Get(RtFilterFunc& filterFunc, int filterFuncID);
protected:
  void Set(RtFilterFunc newFilterfunc, int filterFuncID);
  RtFilterFuncContainer _filterfunc;

private:
  void Initialize();

  void DebugPrintAll();

  size_t size() const;

  int _lastUserFilterFuncID;

};

#endif //  _FILTERFUNCMANAGER_H_
