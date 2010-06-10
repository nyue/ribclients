// -*- C++ -*-
// Procedural Insight 2007 

// Typemaps and other stuff specific to Java support

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

%typemap(in) (RtFilterFunc)
{
  if ($input != 0) {
    // std::cout << "filtername id is " << $input << std::endl;
    switch ($input) {
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

// Procedural Free Function
%typemap(in) (RtProcFreeFunc)
{
  if ($input != 0) {
    switch ($input) {
    case PROCFREE:
      $1 = RiProcFree;
      break;
    default:
      {
	jclass excCls =
	  jenv->FindClass("java/lang/IllegalArgumentException");
	if (excCls != 0)
	  jenv->ThrowNew(excCls,
			 "thrown from native code [Unknown procedural type]");
	return;
      }
      break;
    }
  }
}

// Procedural Subdivide Function
%typemap(in) (RtProcSubdivFunc)
{
  if ($input != 0) {
    switch ($input) {
    case PROCDELAYEDREADARCHIVE:
      $1 = RiProcDelayedReadArchive;
      break;
    case PROCRUNPROGRAM:
      $1 = RiProcRunProgram;
      break;
    case PROCDYNAMICLOAD:
      $1 = RiProcDynamicLoad;
      break;
    default:
      {
	jclass excCls =
	  jenv->FindClass("java/lang/IllegalArgumentException");
	if (excCls != 0)
	  jenv->ThrowNew(excCls,
			 "thrown from native code [Unknown procedural type]");
	return;
      }
      break;
    }
  }
}

// Parameter list
%typemap(in) (RtInt n, RtToken tokens[], RtPointer params[])
{
  $1 = 0; // initialize to zero tokens/params pair, $1 is == n
  if ($input != NULL) {
    // std::cout << "Parsing parameter" << std::endl;
    g_params.SetJavaEnvironment(jenv);
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
%typemap(jni)    (RtInt n, RtToken tokens[], RtPointer params[]) "jobject"
%typemap(jtype)  (RtInt n, RtToken tokens[], RtPointer params[]) "java.util.Hashtable"
%typemap(jstype) (RtInt n, RtToken tokens[], RtPointer params[]) "java.util.Hashtable"
%typemap(javain) (RtInt n, RtToken tokens[], RtPointer params[]) "$javainput"

// Transformation matrix
%typemap(in) RtMatrix
{
  // Transformation matrix handling 
  if ($input != 0) {
    
    const static std::string floatMatrixStr = "[[F";
    const static std::string FloatObjectMatrixStr = "[[Ljava.lang.Float;";
    
    jclass valueClass = jenv->GetObjectClass($input);
    if (valueClass != 0) {
      
      jclass valueClassClass = jenv->GetObjectClass(valueClass);
      if (valueClassClass != 0) {
	
	//
	// Get the name of the object's class
	//
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
	
	//
	// Process the matrix
	//
	if (className == floatMatrixStr) {
	  int numRows = jenv->GetArrayLength((jarray)$input);
	  // std::cout << "float matrix row size is " << numRows << std::endl;
	  if (numRows!=4) {
	    jclass excCls =
	      jenv->FindClass("java/lang/IllegalArgumentException");
	    if (excCls != 0)
	      jenv->ThrowNew(excCls,
			     "thrown from native code [RtMatrix row count != 4]");
	    return;
	  }
	  for (size_t i=0;i<numRows;i++) {
	    jobject singleRow =
	      jenv->GetObjectArrayElement((jobjectArray)$input, i);

	    // Process a single row
	    int numColumns = jenv->GetArrayLength((jarray)singleRow);
	    if (numColumns!=4) {
	      jclass excCls =
		jenv->FindClass("java/lang/IllegalArgumentException");
	      if (excCls != 0)
		jenv->ThrowNew(excCls,
			       "thrown from native code [RtMatrix column count != 4]");
	      return;
	    }
	    jfloat *element =
	      jenv->GetFloatArrayElements((jfloatArray)singleRow, 0);
	    for (size_t j=0;j<numColumns;j++) {
	      jfloat matrixElementValue = element[j];
	      /*
	      std::cout << "matrix["
			<< i << "]["
			<< j <<"] = "
			<< matrixElementValue << std::endl;
	      */
	      g_transform[i][j] = matrixElementValue;
	    }
	  }
	} else if (className == FloatObjectMatrixStr) {
	}
      }
      $1 = &(g_transform[0]);
    }
  }
}

%typemap(jni)    RtMatrix "jobject"
%typemap(jtype)  RtMatrix "float[][]"
%typemap(jstype) RtMatrix "float[][]"
%typemap(javain) RtMatrix "$javainput"

// Bound
%typemap(in) RtBound
{
  // Bound
  if ($input != 0) {
    const static std::string floatArrayStr = "[F";
    const static std::string FloatObjectArrayStr = "[Ljava.lang.Float;";
    jclass valueClass = jenv->GetObjectClass($input);
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
	
	
	
	
	if (className == floatArrayStr) {
	  int numElements = jenv->GetArrayLength((jarray)$input);
	  // std::cout << "float array size is " << numElements << std::endl;
	  if (numElements!=6) {
	    // throw java exception regarding expected array length
	  }
	  jfloat *element =
	    jenv->GetFloatArrayElements((jfloatArray)$input, 0);
	  for (size_t i=0;i<numElements;i++) {
	    jfloat arrayValue = element[i];
	    // std::cout << "float[" << i << "] = " << arrayValue << std::endl;
	    g_bound[i] = element[i];
	  }
	} else if (className == FloatObjectArrayStr) {
	  int numElements = jenv->GetArrayLength((jarray)$input);
	  // std::cout << "Float array size is " << numElements << std::endl;
	  if (numElements!=6) {
	    // throw java exception regarding expected array length
	  }
	  jclass fclassid = jenv->FindClass("java/lang/Float");
	  const jmethodID floatValue =
	    jenv->GetMethodID(fclassid, "floatValue",
			      "()F");
	  
	  // floatParamStorage.push_back(floatPlaceHolder); // STORAGE
	  // floatParamStorage.back().resize(numElements); // STORAGE
	  
	  for (size_t i=0;i<numElements;i++) {
	    jobject oae =
	      jenv->GetObjectArrayElement((jobjectArray)$input, i);
	    jfloat fValue =
	      (jfloat)jenv->CallFloatMethod(oae,
					    floatValue);
	    // std::cout << "Float[" << i << "] = " << fValue << std::endl;
	    
	    g_bound[i] = fValue;
	    // floatParamStorage.back()[i] = fValue; // STORAGE
	    
	  }
	  // _parms[dictIndex] = &(floatParamStorage.back()[0]); // STORAGE
	}
	
      }
      
      
      

      memcpy($1,g_bound,sizeof(RtBound));
    }
  }
}
%typemap(jni)    RtBound "jobject"
%typemap(jtype)  RtBound "float[]"
%typemap(jstype) RtBound "float[]"
%typemap(javain) RtBound "$javainput"

// ====================
// Point
// ====================
%typemap(in) RtPoint
{
  // Point
  if ($input != 0) {
    const static std::string floatArrayStr = "[F";
    const static std::string FloatObjectArrayStr = "[Ljava.lang.Float;";
    jclass valueClass = jenv->GetObjectClass($input);
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
	
	
	
	
	if (className == floatArrayStr) {
	  int numElements = jenv->GetArrayLength((jarray)$input);
	  // std::cout << "float array size is " << numElements << std::endl;
	  if (numElements!=3) {
	    jclass excCls =
	      jenv->FindClass("java/lang/IllegalArgumentException");
	    if (excCls != 0)
	      jenv->ThrowNew(excCls,
			     "thrown from native code [Array size != 3]");
	    return;
	  }
	  jfloat *element =
	    jenv->GetFloatArrayElements((jfloatArray)$input, 0);
	  for (size_t i=0;i<numElements;i++) {
	    jfloat arrayValue = element[i];
	    // std::cout << "float[" << i << "] = " << arrayValue << std::endl;
	    g_point[i] = element[i];
	  }
	} else if (className == FloatObjectArrayStr) {
	  int numElements = jenv->GetArrayLength((jarray)$input);
	  // std::cout << "Float array size is " << numElements << std::endl;
	  if (numElements!=3) {
	    jclass excCls =
	      jenv->FindClass("java/lang/IllegalArgumentException");
	    if (excCls != 0)
	      jenv->ThrowNew(excCls,
			     "thrown from native code [Array size != 3]");
	    return;
	  }
	  jclass fclassid = jenv->FindClass("java/lang/Float");
	  const jmethodID floatValue =
	    jenv->GetMethodID(fclassid, "floatValue",
			      "()F");
	  
  
	  for (size_t i=0;i<numElements;i++) {
	    jobject oae =
	      jenv->GetObjectArrayElement((jobjectArray)$input, i);
	    jfloat fValue =
	      (jfloat)jenv->CallFloatMethod(oae,
					    floatValue);
	    // std::cout << "Float[" << i << "] = " << fValue << std::endl;
	    
	    g_point[i] = fValue;
	  }
	}
      }
      memcpy($1,g_point,sizeof(RtPoint));
    }
  }
}
%typemap(jni)    RtPoint "jobject"
%typemap(jtype)  RtPoint "float[]"
%typemap(jstype) RtPoint "float[]"
%typemap(javain) RtPoint "$javainput"

//====================
// RtToken array
%typemap(in) RtToken[]
{
  $1 = 0;
  if ($input != NULL) {
    // std::cout << "NEW RtToken[] handler" << std::endl;
    ParameterList::StringVec sv;
    g_params.ConvertToSTLStringVector($input,sv);
    $1 = g_params.AddRtTokenArrayArg(sv);
  }
}
%typemap(jni)    RtToken[] "jobject"
%typemap(jtype)  RtToken[] "String[]"
%typemap(jstype) RtToken[] "String[]"
%typemap(javain) RtToken[] "$javainput"

%apply RtToken[] { RtString[] };

/*
  DO NOT introduce type map for RtInt[] or RtFloat[], these are provided by
  arrays_java.i
*/
