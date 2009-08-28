#ifndef _PARAMETERLIST_H_
#define _PARAMETERLIST_H_

#include <TParameterList.h>
#include <jni.h>

class ParameterList : public TParameterList<jobject> {
public:
  ParameterList(DeclarationManager& dm);
  virtual ~ParameterList();
  virtual bool ProcessParameterList(jobject parameterlist);
  /*
  virtual void NewRtStringVector(jobject stringArray,
				 RtStringVector& stringVector);
  */
  virtual void ConvertToSTLStringVector(jobject stringArray,
                                        StringVec& stringVector);
  virtual void ConvertToRtIntVector(jobject integerArray,
                                    RtIntVector& integerVector);
  virtual void ConvertToRtFloatVector(jobject floatArray,
                                      RtFloatVector& floatVector);

  void SetJavaEnvironment(JNIEnv* jni_env);
  friend std::ostream& operator <<(std::ostream &os,
				   const ParameterList &obj);
private:
  // void ExtractValue(jobject pvalue, int dictIndex, const char* keyString);
  JNIEnv* jenv;
};

#endif // _PARAMETERLIST_H_
