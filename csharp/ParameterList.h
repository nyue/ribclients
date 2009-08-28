#ifndef _IMPPARAMETERLIST_H_
#define _IMPPARAMETERLIST_H_

#include <TParameterList.h>

class ParameterList : public TParameterList<void*> {
public:
  ParameterList(DeclarationManager& dm);
  virtual ~ParameterList();
  virtual bool ProcessParameterList(void* parameterlist);
  virtual void NewRtStringVector(void* stringArray,
				 RtStringVector& stringVector);
  virtual void ConvertToSTLStringVector(void* stringArray,
                                        StringVec& stringVector);
  friend std::ostream& operator <<(std::ostream &os,
				   const ParameterList &obj);
private:
  // void ExtractValue(void* pvalue, int dictIndex, const char* keyString);
};

#endif // _IMPPARAMETERLIST_H_
