// Standard JNI required headers
#include <jni.h>
#include <sys/types.h>
#ifndef _WIN32
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <unistd.h>
#endif // !_WIN32
#include <sys/stat.h>
#include <fcntl.h>
// Application specific headers
#include <ri.h>
#include <DeclarationManager.h>
// #include "ParameterList.h"
#include <BasisManager.h>
#include <FilterFuncManager.h>
#include <LightHandleManager.h>
#include <ObjectHandleManager.h>
#include <ArchiveHandleManager.h>
#include <ErrorHandlerManager.h>

extern "C" {

  BasisManager bm;
  FilterFuncManager ffm;
  LightHandleManager lhm;
  ObjectHandleManager ohm;
  ArchiveHandleManager ahm;
  ErrorHandlerManager ehm;

  /*!
    Prototyping code area
    \todo To remove when code goes in to maintance mode
  */
  // ==========================================================================
  // Integral data
  // ==========================================================================
  JNIEXPORT void JNICALL
  Java_RIBClient_ProtoIntParam (JNIEnv * env, jobject jobj, int intValue)
  {
    std::cout << "ProtoIntParam : " << intValue << std::endl;
  }

  JNIEXPORT void JNICALL
  Java_RIBClient_ProtoFloatParam (JNIEnv * env, jobject jobj, float floatValue)
  {
    std::cout << "ProtoFloatParam : " << floatValue << std::endl;
  }

  JNIEXPORT void JNICALL
  Java_RIBClient_ProtoDoubleParam (JNIEnv * env, jobject jobj, double doubleValue)
  {
    std::cout << "ProtoDoubleParam : " << doubleValue << std::endl;
  }

  JNIEXPORT void JNICALL
  Java_RIBClient_ProtoStringParam (JNIEnv *env, jobject jobj,
				   jstring stringValue)
  {
    const char *str = (env)->GetStringUTFChars(stringValue,0);
    std::cout << "ProtoStringParam : " << str << std::endl;
    (env)->ReleaseStringUTFChars(stringValue,str);
  }

  // ==========================================================================
  // Array data
  // ==========================================================================
  JNIEXPORT void JNICALL
  Java_RIBClient_ProtoIntArrayParam (JNIEnv * env, jobject jobj,
				     jintArray intArray)
  {
    int numElements = env->GetArrayLength(intArray);
    std::cout << "ProtoIntArrayParam length is : " << numElements << std::endl;
    if (numElements > 0) {
      jint *carr;
      carr = env->GetIntArrayElements(intArray,NULL);
      for (int i=0;i<numElements;i++) {
	std::cout << "IntArray[" << i << "] = " << carr[i] << std::endl;
      }
      env->ReleaseIntArrayElements(intArray,carr,0);
    }
  }

  JNIEXPORT void JNICALL
  Java_RIBClient_ProtoFloatArrayParam (JNIEnv * env, jobject jobj,
				       jfloatArray floatArray)
  {
    int numElements = env->GetArrayLength(floatArray);
    std::cout << "ProtoFloatArrayParam length is : " << numElements << std::endl;
    if (numElements > 0) {
      jfloat *carr;
      carr = env->GetFloatArrayElements(floatArray,NULL);
      for (int i=0;i<numElements;i++) {
	std::cout << "FloatArray[" << i << "] = " << carr[i] << std::endl;
      }
      env->ReleaseFloatArrayElements(floatArray,carr,0);
    }
  }

  JNIEXPORT void JNICALL
  Java_RIBClient_ProtoDoubleArrayParam (JNIEnv * env, jobject jobj,
					jdoubleArray doubleArray)
  {
    int numElements = env->GetArrayLength(doubleArray);
    std::cout << "ProtoDoubleArrayParam length is : " << numElements << std::endl;
    if (numElements > 0) {
      jdouble *carr;
      carr = env->GetDoubleArrayElements(doubleArray,NULL);
      for (int i=0;i<numElements;i++) {
	std::cout << "DoubleArray[" << i << "] = " << carr[i] << std::endl;
      }
      env->ReleaseDoubleArrayElements(doubleArray,carr,0);
    }
  }
  // Integral object
  JNIEXPORT void JNICALL
  Java_RIBClient_ProtoObjectParam (JNIEnv * env, jobject obj,
				   jobject objectValue)
  {
    /* Check of class type is not necessary because we have already prototyped
       the code with Hashtable as it's argument
     */
    jclass hc = env->FindClass("java/util/Hashtable");
    jboolean isHashtable = env->IsInstanceOf(objectValue,hc);
    if (isHashtable) {
      jclass cls = (env)->GetObjectClass(objectValue);
      if (cls == NULL ) {
	std::cerr << "Failed to get object class" << std::endl;
	return;
      }
      jmethodID mid;
      // Get the size (debugging)
      mid = (env)->GetMethodID(cls, "size", "()I"); 
      if (mid == NULL) { 
	return; /* method not found */ 
      } 
      jint size = (env)->CallIntMethod(objectValue, mid);
      // Get the keys [Enumeration]
      mid = (env)->GetMethodID(cls,
			       "keys",
			       "()Ljava/util/Enumeration;");
      if (mid == NULL) { 
	return; /* method not found */ 
      } 
      jobject eobj = (env)->CallObjectMethod(objectValue, mid);

      // Get the hasMoreElements method (for iterating)
      jclass ecls = (env)->GetObjectClass(eobj);
      if (ecls != NULL ) {
	jmethodID hme_mid = (env)->GetMethodID(ecls,
					       "hasMoreElements",
					       "()Z");
	jmethodID ne_mid = (env)->GetMethodID(ecls,
					      "nextElement",
					      "()Ljava/lang/Object;");
	/* For future reference if we do need it
	  mHashPut = env->GetMethodID
	  (clsHash, "put",
	  "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
	 */
	jmethodID get_mid = (env)->GetMethodID(cls,
					       "get",
					       "(Ljava/lang/Object;)Ljava/lang/Object;");
	if (hme_mid != NULL && ne_mid != NULL && get_mid != NULL) {
	  while ((env)->CallBooleanMethod(eobj, hme_mid)) {

	    jobject key = (env)->CallObjectMethod(eobj, ne_mid);
	    std::cout << "after calling ne_mid" << std::endl;
	    jstring key_string = (jstring)key;
	    if (key_string != NULL) {
	      const char* str;
	      str = (env)->GetStringUTFChars(key_string, NULL);
	      if (str == NULL) {
		return; /* OutOfMemoryError already thrown */
	      } else {
		std::cout << "Key is " << str << std::endl;
	      }
	      (env)->ReleaseStringUTFChars(key_string, str);
	    }

	    std::cout << "before calling get_mid" << std::endl;
	    jobject value = (env)->CallObjectMethod(obj, get_mid, key);
	    std::cout << "after calling get_mid" << std::endl;

	    jclass intArrayClass = (env)->FindClass("[I"); 
	    jclass floatArrayClass = (env)->FindClass("[F"); 
	    jclass doubleArrayClass = (env)->FindClass("[D"); 
	    jclass arrayClass = (env)->FindClass("Ljava/lang/reflect/Array;"); 

	    jboolean isIntArray = (env)->IsInstanceOf(value,intArrayClass);
	    if (isIntArray) {
	      std::cout << "Value is array of integer" << std::endl;
	    }
	    jboolean isFloatArray = (env)->IsInstanceOf(value,floatArrayClass);
	    if (isFloatArray) {
	      std::cout << "Value is array of float" << std::endl;
	    }
	    jboolean isDoubleArray = (env)->IsInstanceOf(value,doubleArrayClass);
	    if (isDoubleArray) {
	      std::cout << "Value is array of double" << std::endl;
	    }
	    jboolean isArray = (env)->IsInstanceOf(value,arrayClass);
	    if (isArray) {
	      std::cout << "Value is array of stuff" << std::endl;
	    }
	    // jboolean isFloatArray = (env)->IsInstanceOf(value,"[I");
	    // jboolean isDoubleArray = (env)->IsInstanceOf(value,"[I");
	    // jboolean isStringArray = IsInstanceOf(value,"[I");
	    std::cout << "Value array determination done" << std::endl;
    
	  }
	} else {
	  std::cerr << "Get method failed" << std::endl;
	}
      }
      for (jint index=0; index<size; index++) {
	// Get the token value pair
	std::cout << "Object size : " << size << std::endl;
	// Get the token, must be String
	
	// Get the value, must be an array of int, float/double or String

	// Get them into a suitable form for updating
      }
    } else {
      std::cerr << "Expecting Hashtable as parameter" << std::endl;
    }
  }

  //===========================================================================
  // End of prototyping code
  //===========================================================================
  /*===========================================================================
    Graphics State
    --------------
    RiBegin( RtToken name )
    RiEnd( void )
    RtContextHandle RiGetContext ( void )
    RiContext ( RtContextHandle handle )
    RiFrameBegin( RtInt frame )
    RiFrameEnd( void )
    RiWorldBegin()
    RiWorldEnd()  
    RiFormat( RtInt xresolution, RtInt yresolution, RtFloat pixelaspectratio )
    RiFrameAspectRatio( RtFloat frameaspectratio )
    RiScreenWindow( RtFloat left, RtFloat right, RtFloat bottom, RtFloat top ) 
    RiCropWindow( RtFloat xmin, RtFloat xmax, RtFloat ymin, RtFloat ymax )
    RiProjection( RtToken name, ...parameterlist... ) 
    RiClipping( RtFloat near, RtFloat far ) 
    RiClippingPlane ( RtFloat nx, RtFloat ny, RtFloat nz,
    RtFloat x, RtFloat y, RtFloat z)
    RiDepthOfField( RtFloat fstop, RtFloat focallength, RtFloat focaldistance )
    RiShutter( RtFloat min, RtFloat max )
    RiPixelVariance ( RtFloat variation )
    RiPixelSamples( RtFloat xsamples, RtFloat ysamples )
    RiPixelFilter( RtFilterFunc filterfunc, RtFloat xwidth, RtFloat ywidth )
    RiExposure( RtFloat gain, RtFloatgamma )
    RiImager( RtToken name, parameterlist )
    RiQuantize( RtToken type, RtInt one, RtInt min, RtInt max,
    RtFloat ditheramplitude )
    RiDisplayChannel( RtToken channel, ...parameterlist... )
    RiDisplay( RtToken name, RtToken type, RtToken mode, ...parameterlist... )
    RiHider( RtToken type, ...parameterlist... )
    RiColorSamples( RtInt n, RtFloat nRGB[], RtFloat RGBn[] )
    RiRelativeDetail( RtFloat relativedetail )
    RiOption( RtToken name, parameterlist )
    RiAttributeBegin()
    RiAttributeEnd()
    RiColor( RtColor color )
    RiOpacity( RtColor color )
    RiTextureCoordinates(RtFloat s1,RtFloat t1,RtFloat s2,RtFloat t2,
    RtFloat s3,RtFloat t3,RtFloat s4,RtFloat t4 )
    RtLightHandle RiLightSource(RtToken shadername, ...parameterlist... )
    RtLightHandle RiAreaLightSource( RtToken shadername, ...parameterlist... )
    RiIlluminate( RtLightHandle light, RtBoolean onoff )
    RiSurface( RtToken shadername, ...parameterlist... )
    RiDisplacement( RtToken shadername, ...parameterlist...)
    RiAtmosphere( RtToken shadername, ...parameterlist... )
    RiInterior( RtToken shadername, ...parameterlist... )
    RiExterior( RtToken shadername, ...parameterlist... )
    RiShadingRate( RtFloat size )
    RiShadingInterpolation( RtToken type )
    RiMatte( RtBoolean onoff )
    RiBound( RtBound bound )
    RiDetail( RtBound bound )
    RiDetailRange( RtFloat minvisible, RtFloat lowertransition,
    RtFloat uppertransition, RtFloat maxvisible )
    RiGeometricApproximation( RtToken type, RtFloat value )
    RiOrientation( RtToken orientation )
    RiReverseOrientation()
    RiSides( RtInt sides )
    RiIdentity()
    RiTransform( RtMatrix transform )
    RiConcatTransform( RtMatrix transform )
    RiPerspective( RtFloat fov )
    RiTranslate( RtFloat dx, RtFloat dy, RtFloat dz )
    RiRotate( RtFloat angle, RtFloat dx, RtFloat dy, RtFloat dz )
    RiScale( RtFloat sx, RtFloat sy, RtFloat sz )
    RiSkew( RtFloat angle, RtFloat dx1, RtFloat dy1, RtFloat dz1, 
    RtFloat dx2, RtFloat dy2, RtFloat dz2 )
    RiCoordinateSystem( RtToken space )
    RiScopedCoordinateSystem( RtToken name )
    RiCoordSysTransform ( RtToken name )
    RtPoint *RiTransformPoints( RtToken fromspace, RtToken tospace, 
    RtInt n, RtPoint points )
    RiTransformBegin()
    RiTransformEnd()
    RiResource( RtToken handle,  RtToken type, ...)
    RiResourceBegin()
    RiResourceEnd()
    RiAttribute( RtToken name, ...parameterlist... )
    =========================================================================*/
	
  JNIEXPORT void JNICALL
  Java_RIBClient_Begin (JNIEnv * env, jobject jobj, jstring name)
  {
    RiBegin(RI_NULL);
  }

  JNIEXPORT void JNICALL Java_RIBClient_End (JNIEnv * env, jobject jobj)
  {
    RiEnd();
  }

  JNIEXPORT void JNICALL
  Java_RIBClient_FrameBegin (JNIEnv * env, jobject jobj, int frame)
  {
    RiFrameBegin(frame);
  }

  JNIEXPORT void JNICALL Java_RIBClient_FrameEnd (JNIEnv * env, jobject jobj)
  {
    RiFrameEnd();
  }

  JNIEXPORT void JNICALL Java_RIBClient_WorldBegin (JNIEnv * env, jobject jobj)
  {
    RiWorldBegin();
  }

  JNIEXPORT void JNICALL Java_RIBClient_WorldEnd (JNIEnv * env, jobject jobj)
  {
    RiWorldEnd();
  }

  JNIEXPORT void JNICALL
  Java_RIBClient_Format(JNIEnv * env, jobject jobj,
			int xresolution, int yresolution,
			int pixelaspectratio )
  {
    RiFormat(xresolution,yresolution,pixelaspectratio);
  }

  JNIEXPORT void JNICALL 
  Java_RIBClient_FrameAspectRatio(JNIEnv * env, jobject jobj,
				  float frameaspectratio )
  {
    RiFrameAspectRatio(frameaspectratio);
  }

  JNIEXPORT void JNICALL
  Java_RIBClient_ScreenWindow(JNIEnv * env, jobject jobj,
			      float left, float right,
			      float bottom, float top )
  {
    RiScreenWindow(left,right,bottom,top);
  }

  JNIEXPORT void JNICALL Java_RIBClient_CropWindow(JNIEnv * env, jobject jobj,
						   float xmin, float xmax,
						   float ymin, float ymax )
  {
    RiCropWindow(xmin,xmax,ymin,ymax);
  }

  void ProcessParameterList(jobject params)
  {
  }

  JNIEXPORT void JNICALL Java_RIBClient_Projection(JNIEnv * env,
						   jobject jobj,
						   jstring name,
						   jobject parameterlist) 
  {
    ProcessParameterList(parameterlist);
    RiProjection(RI_PERSPECTIVE,RI_NULL);
  }

}
