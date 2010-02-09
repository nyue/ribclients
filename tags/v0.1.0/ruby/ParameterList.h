#ifndef _IMPPARAMETERLIST_H_
#define _IMPPARAMETERLIST_H_

#include "ruby.h"
#ifdef RUBY_VERSION_POST_180
#include "ruby/st.h"
#else
#include "st.h"
#endif //

/*
  This is required due to a change in Ruby around 1.8.4 where 
  rb_read was change to read
  rb_write was change to write
  http://blade.nagaokaut.ac.jp/cgi-bin/scat.rb/ruby/ruby-core/9784
*/
#ifdef WIN32
#undef write
#undef read
#endif // WIN32

#include <TParameterList.h>

class ParameterList : public TParameterList<VALUE> {
public:
  ParameterList(DeclarationManager& dm);
  virtual ~ParameterList();
  virtual bool ProcessParameterList(VALUE parameterlist);
  virtual bool ProcessParameterListEx(VALUE parameterlist);
  virtual void ConvertToSTLStringVector(VALUE stringArray,
					StringVec& stringVector);
  virtual void ConvertToRtIntVector(VALUE integerArray,
				    RtIntVector& integerVector);
  virtual void ConvertToRtFloatVector(VALUE floatArray,
                                      RtFloatVector& floatVector);

  RtFloat VALUE2RtFloat(VALUE number);
  void VALUE2RtFloatVector(VALUE numberArray,
			   RtFloatVector& floatVector);
  void VALUE2RtIntVector(VALUE numberArray,
			 RtIntVector& integerVector);
  void VALUE2RtMatrix(VALUE numberArray,
		      RtMatrix matrix);
  /*!
    \todo deprecated, remove
   */
  void VALUE2STLStringVector(VALUE stringArray,
			     StringVec& stringVector);
  friend std::ostream& operator <<(std::ostream &os,
				   const ParameterList &obj);
private:
  VALUE parm_hash_iter(VALUE arg1, VALUE arg2);
  VALUE eRIBError;
};

#endif // _IMPPARAMETERLIST_H_
