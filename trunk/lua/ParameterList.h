#ifndef _IMPPARAMETERLIST_H_
#define _IMPPARAMETERLIST_H_

#include <lua.h>
#include <TParameterList.h>

class ParameterList : public TParameterList<PyObject*> {
public:
  ParameterList(DeclarationManager& dm);
  virtual ~ParameterList();
  virtual bool ProcessParameterList(PyObject* parameterlist);
  virtual void ConvertToSTLStringVector(PyObject* stringArray,
                                        StringVec& stringVector);
  virtual void ConvertToRtIntVector(PyObject* integerArray,
				    RtIntVector& integerVector);
  virtual void ConvertToRtFloatVector(PyObject* floatArray,
                                      RtFloatVector& floatVector);

  friend std::ostream& operator <<(std::ostream &os,
				   const ParameterList &obj);
private:
  void ExtractValue(PyObject* pvalue, int dictIndex, const char* keyString);
};

#endif // _IMPPARAMETERLIST_H_
