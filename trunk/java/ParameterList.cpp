#include "ParameterList.h"
#include <jni.h>

ParameterList::ParameterList(DeclarationManager& dm)
  : TParameterList<jobject>(dm)
{
}

ParameterList::~ParameterList()
{
}

bool ParameterList::ProcessParameterList(jobject parameterlist)
{
  // std::cout << "ProcessParameterList START" << std::endl;
  const jclass hashtable = jenv->FindClass("java/util/Hashtable");

  if (!jenv->IsInstanceOf(parameterlist,hashtable))
    return true;

  const static std::string IntegerObjectArrayStr = "[Ljava.lang.Integer;";
  const static std::string FloatObjectArrayStr = "[Ljava.lang.Float;";
  const static std::string DoubleObjectArrayStr = "[Ljava.lang.Double;";
  const static std::string intArrayStr = "[I";
  const static std::string floatArrayStr = "[F";
  const static std::string doubleArrayStr = "[D";
  const static std::string stringArrayStr = "[Ljava.lang.String;";

  // Local temp storage
  std::vector<RtFloat> floatPlaceHolder;
  std::vector<std::string> stringPlaceHolder;
  std::vector<RtInt> integerPlaceHolder;
  FloatParamStorageIter fIter;
  IntegerParamStorageIter iIter;
  StringParamStorageIter sIter;

  if (hashtable != 0) {
    const jclass enumeration = jenv->FindClass("java/util/Enumeration");
    const jclass iclassid = jenv->FindClass("java/lang/Integer");
    const jmethodID keys =
      jenv->GetMethodID(hashtable, "keys",
			"()Ljava/util/Enumeration;");
    const jmethodID get =
      jenv->GetMethodID(hashtable, "get",
			"(Ljava/lang/Object;)Ljava/lang/Object;");
    const jmethodID size =
      jenv->GetMethodID(hashtable, 
			"size", "()I");
    const jmethodID intValue =
      jenv->GetMethodID(iclassid, "intValue",
			"()I");

    int dictIndex = 0;
    jobject sizeObject = jenv->CallObjectMethod(parameterlist, size);
    jint hashtablesize = (jint)jenv->CallIntMethod(sizeObject, intValue);
    // std::cout << "hashtablesize " << hashtablesize << std::endl;
    if (hashtablesize > 0) {
      Init(hashtablesize); // so the parameterlist knows how much to allocate
      if (enumeration != 0) {
	const jmethodID hasMoreElements =
	  jenv->GetMethodID(enumeration, 
			    "hasMoreElements", "()Z");
	const jmethodID nextElement =
	  jenv->GetMethodID(enumeration,
			    "nextElement", "()Ljava/lang/Object;");
	
	for (jobject keyset = jenv->CallObjectMethod(parameterlist, keys);
	     jenv->CallBooleanMethod(keyset, hasMoreElements) == JNI_TRUE;) {
	  
	  // Process the Hashtable's key
	  jstring key = (jstring)jenv->CallObjectMethod(keyset, nextElement);
	  const char *keyptr = jenv->GetStringUTFChars(key, 0);
	  std::string keyString = keyptr;
	  _tokenStorage[dictIndex] = keyString;
	  // std::cout << "key is " << keyptr << std::endl;
	  jenv->ReleaseStringUTFChars(key, keyptr);
	  
	  // Retrieve an value with the given key and process the value
	  jarray value = (jarray)jenv->CallObjectMethod(parameterlist, get, key);
	  if (value != 0) {
	    jclass valueClass = jenv->GetObjectClass(value);
	    if (valueClass != 0) {
	      jclass valueClassClass = jenv->GetObjectClass(valueClass);
	      if (valueClassClass != 0) {
		const jmethodID getName =
		  jenv->GetMethodID(valueClassClass,
				    "getName",
				    "()Ljava/lang/String;");
		// std::cout << "getName() called" << std::endl;
		
		jstring valueClassClassName =
		  (jstring)jenv->CallObjectMethod(valueClass, getName);
		const char *classNameStr =
		  jenv->GetStringUTFChars(valueClassClassName,
					  0);
		// Make a copy of the string for ease of use/processing
		std::string className(classNameStr);
		jenv->ReleaseStringUTFChars(valueClassClassName,
					    classNameStr);
		// std::cout << "className is " << className.c_str() << std::endl;
		
		/*
		  From the class name, determine the array base type and
		  process as appropriate
		*/
		if (className == IntegerObjectArrayStr) {
		  int numElements = jenv->GetArrayLength(value);
		  // std::cout << "Integer array size is " << numElements << std::endl;
		  jclass iclassid = jenv->FindClass("java/lang/Integer");
		  const jmethodID intValue =
		    jenv->GetMethodID(iclassid, "intValue",
				      "()I");
		  _integerParamStorage.push_back(integerPlaceHolder); // STORAGE
		  _integerParamStorage.back().resize(numElements); // STORAGE
		  for (size_t i=0;i<numElements;i++) {
		    jobject oae =
		      jenv->GetObjectArrayElement((jobjectArray)value, i);
		    jint iValue = (jint)jenv->CallIntMethod(oae, intValue);
		    // std::cout << "Integer[" << i << "] = " << iValue << std::endl;
		    _integerParamStorage.back()[i] = iValue;
		  }
		  _parms[dictIndex] = &(_integerParamStorage.back()[0]);
		} else if (className == FloatObjectArrayStr) {
		  int numElements = jenv->GetArrayLength(value);
		  // std::cout << "Float array size is " << numElements << std::endl;
		  jclass fclassid = jenv->FindClass("java/lang/Float");
		  const jmethodID floatValue =
		    jenv->GetMethodID(fclassid, "floatValue",
				      "()F");
		  
		  _floatParamStorage.push_back(floatPlaceHolder); // STORAGE
		  _floatParamStorage.back().resize(numElements); // STORAGE
		  
		  for (size_t i=0;i<numElements;i++) {
		    jobject oae =
		      jenv->GetObjectArrayElement((jobjectArray)value, i);
		    jfloat fValue =
		      (jfloat)jenv->CallFloatMethod(oae,
						    floatValue);
		    // std::cout << "Float[" << i << "] = " << fValue << std::endl;
		    
		    _floatParamStorage.back()[i] = fValue; // STORAGE
		    
		  }
		  _parms[dictIndex] = &(_floatParamStorage.back()[0]); // STORAGE
		} else if (className == DoubleObjectArrayStr) {
		  int numElements = jenv->GetArrayLength(value);
		  // std::cout << "Double array size is " << numElements << std::endl;
		  
		  jclass dclassid = jenv->FindClass("java/lang/Double");
		  const jmethodID doubleValue =
		    jenv->GetMethodID(dclassid, "doubleValue",
				      "()D");
		  _floatParamStorage.push_back(floatPlaceHolder); // STORAGE
		  _floatParamStorage.back().resize(numElements); // STORAGE
		  for (size_t i=0;i<numElements;i++) {
		    jobject oae =
		      jenv->GetObjectArrayElement((jobjectArray)value, i);
		    jdouble dValue =
		      (jdouble)jenv->CallDoubleMethod(oae,
						      doubleValue);
		    // std::cout << "Double[" << i << "] = " << dValue << std::endl;
		    _floatParamStorage.back()[i] = static_cast<jfloat>(dValue);
		  }
		  _parms[dictIndex] = &(_floatParamStorage.back()[0]);
		} else if (className == intArrayStr) {
		  int numElements = jenv->GetArrayLength(value);
		  // std::cout << "int array size is " << numElements << std::endl;
		  jint *element =
		    jenv->GetIntArrayElements((jintArray)value, 0);
		  _integerParamStorage.push_back(integerPlaceHolder); // STORAGE
		  _integerParamStorage.back().resize(numElements); // STORAGE
		  for (size_t i=0;i<numElements;i++) {
		    jint arrayValue = element[i];
		    // std::cout << "int[" << i << "] = " << arrayValue << std::endl;
		    _integerParamStorage.back()[i] = arrayValue;
		  }
		  _parms[dictIndex] = &(_integerParamStorage.back()[0]);
		} else if (className == floatArrayStr) {
		  int numElements = jenv->GetArrayLength(value);
		  // std::cout << "float array size is " << numElements << std::endl;
		  jfloat *element =
		    jenv->GetFloatArrayElements((jfloatArray)value, 0);
		  
		  _floatParamStorage.push_back(floatPlaceHolder); // STORAGE
		  _floatParamStorage.back().resize(numElements); // STORAGE
		  
		  for (size_t i=0;i<numElements;i++) {
		    jfloat arrayValue = element[i];
		    // std::cout << "float[" << i << "] = " << arrayValue << std::endl;
		    _floatParamStorage.back()[i] = arrayValue;
		  }
		  _parms[dictIndex] = &(_floatParamStorage.back()[0]);
		} else if (className == doubleArrayStr) {
		  int numElements = jenv->GetArrayLength(value);
		  // std::cout << "double array size is " << numElements << std::endl;
		  jdouble *element =
		    jenv->GetDoubleArrayElements((jdoubleArray)value, 0);
		  _floatParamStorage.push_back(floatPlaceHolder); // STORAGE
		  _floatParamStorage.back().resize(numElements); // STORAGE
		  for (size_t i=0;i<numElements;i++) {
		    jdouble arrayValue = element[i];
		    // std::cout << "double[" << i << "] = " << arrayValue << std::endl;
		    _floatParamStorage.back()[i] = static_cast<jfloat>(arrayValue);
		  }
		  _parms[dictIndex] = &(_floatParamStorage.back()[0]);
		} else if (className == stringArrayStr) {
		  int numElements = jenv->GetArrayLength(value);
		  // std::cout << "String array size is " << numElements << std::endl;
		  _stringParamStorage.push_back(stringPlaceHolder);
		  _stringParamStorage.back().resize(numElements);
		  for (size_t i=0;i<numElements;i++) {
		    jstring sValue =
		      (jstring)jenv->GetObjectArrayElement((jobjectArray)value,
							   i);
		    const char *sptr = jenv->GetStringUTFChars(sValue, 0);
		    std::string sParm(sptr);
		    // std::cout << "String[" << i << "] = " << sptr << std::endl;
		    jenv->ReleaseStringUTFChars(sValue, sptr);
		    _stringParamStorage.back()[i] = sParm;
		  }
		  /*!
		    \todo Fragile coding?
		  */
		  _parms[dictIndex] = &(_stringParamStorage.back()[0]);
		} else {
		  std::cerr << "ProcessParameterList: "
		    "encountered unsupported type" << std::endl;
		  return false;
		}
	      }
	    }
	  } // if (value!=0)
	  _tokens[dictIndex] =
	    const_cast<char*>(_tokenStorage[dictIndex].c_str());
	  dictIndex++;
	} // for-loop for each element in the hashtable
      } // if (enumeration != 0)
    } // if (hashtablesize > 0)
  } // if (hashtable != 0)
  // std::cout << "ProcessParameterList END" << std::endl;
  return true;
}

void ParameterList::SetJavaEnvironment(JNIEnv* jni_env)
{
  jenv = jni_env;
}

/*
void ParameterList::NewRtStringVector(jobject stringArray,
				      RtStringVector& stringVector)
{
}
*/

void ParameterList::ConvertToSTLStringVector(jobject stringArray,
					     StringVec& stringVector)
{
  if (stringArray != NULL) {
    // Process token array
    const static std::string stringArrayStr = "[Ljava.lang.String;";
    const jclass stringClass = jenv->FindClass("java/lang/String");
    jclass valueClass = jenv->GetObjectClass(stringArray);
    if (valueClass != 0) {
      jclass valueClassClass = jenv->GetObjectClass(valueClass);
      if (valueClassClass != 0) {
	const jmethodID getName =
	  jenv->GetMethodID(valueClassClass,
			    "getName",
			    "()Ljava/lang/String;");
	
	
	jstring valueClassClassName =
	  (jstring)jenv->CallObjectMethod(valueClass, getName);
	const char *classNameStr =
	  jenv->GetStringUTFChars(valueClassClassName,
				  0);
	// Make a copy of the string for ease of use/processing
	std::string className(classNameStr);
	jenv->ReleaseStringUTFChars(valueClassClassName,
				    classNameStr);
	// std::cout << "className is " << className.c_str() << std::endl;
	
	if (className == stringArrayStr) {
	  int numElements = jenv->GetArrayLength((jobjectArray)stringArray);
	  // std::cout << "String array size is " << numElements << std::endl;
	  
	  stringVector.clear();
	  stringVector.resize(numElements);
	  
	  for (size_t i=0;i<numElements;i++) {
	    jstring sValue =
	      (jstring)jenv->GetObjectArrayElement((jobjectArray)stringArray,
						   i);
	    const char *sptr = jenv->GetStringUTFChars(sValue, 0);
	    std::string sParm(sptr);
	    // std::cout << "String[" << i << "] = " << sptr << std::endl;
	    jenv->ReleaseStringUTFChars(sValue, sptr);
	    stringVector[i] = sParm;
	  }
	} else {
	  jclass excCls =
	    jenv->FindClass("java/lang/IllegalArgumentException");
	  if (excCls != 0)
	    jenv->ThrowNew(excCls,
			   "thrown from native code [Expecting String Array]");
	  return;
	}
      }
    }
  }
}

void ParameterList::ConvertToRtIntVector(jobject integerArray,
					 RtIntVector& integerVector)
{
  if (integerArray != NULL) {
    const static std::string IntegerObjectArrayStr = "[Ljava.lang.Integer;";
    const static std::string intArrayStr = "[I";

    // Process token array
    jclass valueClass = jenv->GetObjectClass(integerArray);
    if (valueClass != 0) {
      jclass valueClassClass = jenv->GetObjectClass(valueClass);
      if (valueClassClass != 0) {
	const jmethodID getName =
	  jenv->GetMethodID(valueClassClass,
			    "getName",
			    "()Ljava/lang/String;");
	jstring valueClassClassName =
	  (jstring)jenv->CallObjectMethod(valueClass, getName);
	const char *classNameStr =
	  jenv->GetStringUTFChars(valueClassClassName,
				  0);
	// Make a copy of the integer for ease of use/processing
	std::string className(classNameStr);
	jenv->ReleaseStringUTFChars(valueClassClassName,
				    classNameStr);
	// std::cout << "className is " << className.c_str() << std::endl;
	
	if (className == IntegerObjectArrayStr) {
	  
	  int numElements = jenv->GetArrayLength((jobjectArray)integerArray);
	  // std::cout << "Integer array size is " << numElements << std::endl;
	  jclass iclassid = jenv->FindClass("java/lang/Integer");
	  const jmethodID intValue =
	    jenv->GetMethodID(iclassid, "intValue",
			      "()I");
	  integerVector.clear();
	  integerVector.resize(numElements);
	  for (size_t i=0;i<numElements;i++) {
	    jobject oae =
	      jenv->GetObjectArrayElement((jobjectArray)integerArray, i);
	    jint iValue = (jint)jenv->CallIntMethod(oae, intValue);
	    // std::cout << "Integer[" << i << "] = " << iValue << std::endl;
	    integerVector[i] = iValue;
	  }
	} else if (className == intArrayStr) {
	  int numElements = jenv->GetArrayLength((jobjectArray)integerArray);
	  // std::cout << "int array size is " << numElements << std::endl;
	  jint *element =
	    jenv->GetIntArrayElements((jintArray)integerArray, 0);
	  integerVector.clear();
	  integerVector.resize(numElements);
	  for (size_t i=0;i<numElements;i++) {
	    jint iValue = element[i];
	    // std::cout << "int[" << i << "] = " << iValue << std::endl;
	    integerVector[i] = iValue;
	  }
	} else {
	  jclass excCls =
	    jenv->FindClass("java/lang/IllegalArgumentException");
	  if (excCls != 0)
	    jenv->ThrowNew(excCls,
			   "thrown from native code [Expecting Integer Array]");
	  return;
	}
      }
    }
  }
}

void ParameterList::ConvertToRtFloatVector(jobject floatArray,
					   RtFloatVector& floatVector)
{
  if (floatArray != NULL) {
    const static std::string FloatObjectArrayStr = "[Ljava.lang.Float;";
    const static std::string DoubleObjectArrayStr = "[Ljava.lang.Double;";
    const static std::string floatArrayStr = "[F";
    const static std::string doubleArrayStr = "[D";
    
    // Process token array
    jclass valueClass = jenv->GetObjectClass(floatArray);
    if (valueClass != 0) {
      jclass valueClassClass = jenv->GetObjectClass(valueClass);
      if (valueClassClass != 0) {
	const jmethodID getName =
	  jenv->GetMethodID(valueClassClass,
			    "getName",
			    "()Ljava/lang/String;");
	jstring valueClassClassName =
	  (jstring)jenv->CallObjectMethod(valueClass, getName);
	const char *classNameStr =
	  jenv->GetStringUTFChars(valueClassClassName,
				  0);
	// Make a copy of the float for ease of use/processing
	std::string className(classNameStr);
	jenv->ReleaseStringUTFChars(valueClassClassName,
				    classNameStr);
	// std::cout << "className is " << className.c_str() << std::endl;
	
	if (className == FloatObjectArrayStr) {
	  int numElements = jenv->GetArrayLength((jobjectArray)floatArray);
	  // std::cout << "Float array size is " << numElements << std::endl;
	  jclass fclassid = jenv->FindClass("java/lang/Float");
	  const jmethodID floatValue =
	    jenv->GetMethodID(fclassid, "floatValue",
			      "()F");
	  floatVector.clear();
	  floatVector.resize(numElements);
	  for (size_t i=0;i<numElements;i++) {
	    jobject oae =
	      jenv->GetObjectArrayElement((jobjectArray)floatArray, i);
	    jfloat fValue =
	      (jfloat)jenv->CallFloatMethod(oae,
					    floatValue);
	    // std::cout << "Float[" << i << "] = " << fValue << std::endl;
	    
	    floatVector[i] = fValue; // STORAGE
	  }
	} else if (className == floatArrayStr) {
	  int numElements = jenv->GetArrayLength((jarray)floatArray);
	  // std::cout << "float array size is " << numElements << std::endl;
	  jfloat *element =
	    jenv->GetFloatArrayElements((jfloatArray)floatArray, 0);
	  
	  floatVector.clear();
	  floatVector.resize(numElements);
	  
	  for (size_t i=0;i<numElements;i++) {
	    jfloat arrayValue = element[i];
	    // std::cout << "float[" << i << "] = " << arrayValue << std::endl;
	    floatVector[i] = arrayValue;
	  }
	} else if (className == DoubleObjectArrayStr) {
	  int numElements = jenv->GetArrayLength((jobjectArray)floatArray);
	  // std::cout << "Double array size is " << numElements << std::endl;
	  
	  jclass dclassid = jenv->FindClass("java/lang/Double");
	  const jmethodID doubleValue =
	    jenv->GetMethodID(dclassid, "doubleValue",
			      "()D");
	  floatVector.clear();
	  floatVector.resize(numElements); // STORAGE
	  for (size_t i=0;i<numElements;i++) {
	    jobject oae =
	      jenv->GetObjectArrayElement((jobjectArray)floatArray, i);
	    jdouble dValue =
	      (jdouble)jenv->CallDoubleMethod(oae,
					      doubleValue);
	    // std::cout << "Double[" << i << "] = " << dValue << std::endl;
	    floatVector[i] = static_cast<jfloat>(dValue);
	  }
	} else if (className == doubleArrayStr) {
	  int numElements = jenv->GetArrayLength((jarray)floatArray);
	  // std::cout << "double array size is " << numElements << std::endl;
	  jdouble *element =
	    jenv->GetDoubleArrayElements((jdoubleArray)floatArray, 0);
	  floatVector.clear();
	  floatVector.resize(numElements); // STORAGE
	  for (size_t i=0;i<numElements;i++) {
	    jdouble arrayValue = element[i];
	    // std::cout << "double[" << i << "] = " << arrayValue << std::endl;
	    floatVector[i] = static_cast<jfloat>(arrayValue);
	  }
	} else {
	  jclass excCls =
	    jenv->FindClass("java/lang/IllegalArgumentException");
	  if (excCls != 0)
	    jenv->ThrowNew(excCls,
			   "Expecting Float/Double object array or native float/double array]");
	  return;
	}
      }
    }
  }
}

std::ostream& operator <<(std::ostream &os,
			  const ParameterList &obj)
{
  return os;
}
