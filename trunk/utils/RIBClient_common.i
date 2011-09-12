// -*- C++ -*-
// Procedural Insight 2007 

#define EXTERN

%{
#if _MSC_VER < 1300
#pragma warning(disable:4786)
#undef read
#undef write
#endif
  %}

#if (defined SWIGJAVA)
%module ribclient
%include "arrays_java.i"
#elif defined(SWIGPYTHON)
%module ribclient
#elif defined(SWIGRUBY)
%module ribclient
#elif defined(SWIGCSHARP)
%module ribclient
#endif
 // %include "std_map.i"
 // %include "std_vector.i"


%{ 
#include <ri.h>
#include <iostream>
#include <DeclarationManager.h>
#include <ArchiveHandleManager.h>
#include <LightHandleManager.h>
#include <ObjectHandleManager.h>
#include <ParameterList.h>

  // global variable
  DeclarationManager g_dm;
  ArchiveHandleManager g_ahm;
  LightHandleManager g_lhm;
  ObjectHandleManager g_ohm;
  ParameterList g_params(g_dm);
  float g_transform[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
  float g_bound[6] = {0,1,0,1,0,1};
  float g_point[3] = {0,0,0};
  // global variable to handle special case of an array of RtToken
  /*
  std::vector<std::string> g_stringPlaceHolder;
  std::vector<RtToken> g_RtTokenStorage;
  std::vector<RtInt> g_RtIntArrayStorage;
  std::vector<RtFloat> g_RtFloatArrayStorage;
  std::vector<RtString> g_RtStringArrayStorage;
  */
%} 

/*
%constant int BOXFILTER            = -1;
%constant int TRIANGLEFILTER       = -2;
%constant int CATMULLROMFILTER     = -3;
%constant int BESSELFILTER         = -4;
%constant int GAUSSIANFILTER       = -5;
%constant int SINCFILTER           = -6;
%constant int BLACKMANHARRISFILTER = -7;
%constant int MITCHELLFILTER       = -8;
*/

/*
  We use the convention of negative value for predefined/internal stuff
  user defined stuff starts from one, zero is use as a sentinel/error-marker
*/
#define BOXFILTER            -1
#define TRIANGLEFILTER       -2
#define CATMULLROMFILTER     -3
#define BESSELFILTER         -4
#define GAUSSIANFILTER       -5
#define SINCFILTER           -6
#define BLACKMANHARRISFILTER -7
#define MITCHELLFILTER       -8

#define BEZIERBASIS     -1
#define BSPLINEBASIS    -2
#define CATMULLROMBASIS -3
#define HERMITEBASIS    -4
#define POWERBASIS      -5

#define PROCDELAYEDREADARCHIVE -1
#define PROCRUNPROGRAM         -2
#define PROCDYNAMICLOAD        -3

#define PROCFREE -1

// Constant tokens
%constant const char* FRAMEBUFFER = "framebuffer";
%constant const char* FILE = "file";
%constant const char* ZFILE = "zfile";
%constant const char* RGB = "rgb";
%constant const char* RGBA = "rgba";
%constant const char* RGBZ = "rgbz";
%constant const char* RGBAZ = "rgbaz";
%constant const char* A = "a";
%constant const char* Z = "z";
%constant const char* AZ = "az";
%constant const char* PERSPECTIVE = "perspective";
%constant const char* ORTHOGRAPHIC = "orthographic";
%constant const char* HIDDEN = "hidden";
%constant const char* PAINT = "paint";
%constant const char* RAYTRACE = "raytrace";
%constant const char* PHOTON = "photon";
%constant const char* CONSTANT = "constant";
%constant const char* SMOOTH = "smooth";
%constant const char* FLATNESS = "flatness";
%constant const char* FOV = "fov";
%constant const char* AMBIENTLIGHT = "ambientlight";
%constant const char* POINTLIGHT = "pointlight";
%constant const char* DISTANTLIGHT = "distantlight";
%constant const char* SPOTLIGHT = "spotlight";
%constant const char* INTENSITY = "intensity";
%constant const char* LIGHTCOLOR = "lightcolor";
%constant const char* FROM = "from";
%constant const char* TO = "to";
%constant const char* CONEANGLE = "coneangle";
%constant const char* CONEDELTAANGLE = "conedeltaangle";
%constant const char* BEAMDISTRIBUTION = "beamdistribution";
%constant const char* MATTE = "matte";
%constant const char* METAL = "metal";
%constant const char* SHINYMETAL = "shinymetal";
%constant const char* PLASTIC = "plastic";
%constant const char* PAINTEDPLASTIC = "paintedplastic";
%constant const char* KA = "Ka";
%constant const char* KD = "Kd";
%constant const char* KS = "Ks";
%constant const char* ROUGHNESS = "roughness";
%constant const char* KR = "Kr";
%constant const char* TEXTURENAME = "texturename";
%constant const char* SPECULARCOLOR = "specularcolor";
%constant const char* DEPTHCUE = "depthcue";
%constant const char* FOG = "fog";
%constant const char* BUMPY = "bumpy";
%constant const char* MINDISTANCE = "mindistance";
%constant const char* MAXDISTANCE = "maxdistance";
%constant const char* BACKGROUND = "background";
%constant const char* DISTANCE = "distance";
%constant const char* AMPLITUDE = "amplitude";
%constant const char* RASTER = "raster";
%constant const char* SCREEN = "screen";
%constant const char* CAMERA = "camera";
%constant const char* WORLD = "world";
%constant const char* OBJECT = "object";
%constant const char* INSIDE = "inside";
%constant const char* OUTSIDE = "outside";
%constant const char* LH = "lh";
%constant const char* RH = "rh";
%constant const char* P = "P";
%constant const char* PZ = "Pz";
%constant const char* PW = "Pw";
%constant const char* N = "N";
%constant const char* NP = "Np";
%constant const char* CS = "Cs";
%constant const char* OS = "Os";
%constant const char* S = "s";
%constant const char* T = "t";
%constant const char* ST = "st";
%constant const char* BILINEAR = "bilinear";
%constant const char* BICUBIC = "bicubic";
%constant const char* PRIMITIVE = "primitive";
%constant const char* INTERSECTION = "intersection";
%constant const char* UNION = "union";
%constant const char* DIFFERENCE = "difference";
%constant const char* PERIODIC = "periodic";
%constant const char* NONPERIODIC = "nonperiodic";
%constant const char* CLAMP = "clamp";
%constant const char* BLACK = "black";
%constant const char* IGNORE = "ignore";
%constant const char* PRINT = "print";
%constant const char* ABORT = "abort";
%constant const char* HANDLER = "handler";
%constant const char* BOUNDS = "bounds";
%constant const char* LIMITS = "limits";
%constant const char* SHADOW = "shadow";
%constant const char* BIAS0 = "bias0";
%constant const char* BIAS1 = "bias1";
%constant const char* SAMPLE = "sample";
%constant const char* SEARCHPATH = "searchpath";
%constant const char* SHADER = "shader";
%constant const char* TEXTURE = "texture";
%constant const char* DISPLAY = "display";
%constant const char* WIDTH = "width";
%constant const char* CONSTANTWIDTH = "constantwidth";
%constant const char* COMMENT = "comment";
%constant const char* STRUCTURE = "structure";
%constant const char* VERBATIM = "verbatim";
%constant const char* IDENTIFIER = "identifier";
%constant const char* NAME = "name";
%constant const char* SHADINGGROUP = "shadinggroup";
%constant const char* LINEAR = "linear";
%constant const char* CUBIC = "cubic";
%constant const char* QUANTIZE = "quantize";
%constant const char* DITHER = "dither";
%constant const char* EXPOSURE = "exposure";
%constant const char* FILTER = "filter";
%constant const char* FILTERWIDTH = "filterwidth";
%constant const char* CATMULLCLARK = "catmull-clark";
%constant const char* INTERPOLATEBOUNDARY = "interpolateboundary";

# Procedural Insight additional token
%constant const char* MOTIONFACTOR = "motionfactor";
%constant const char* FILENAME = "filename";
# Visual Information Insight additional token
%constant const char* CS = "Cs";
%constant const char* OS = "Os";
# Error constants
%constant const int E_NOERROR                   =   0;
%constant const int E_NOMEM                     =   1; /* Out of memory */
%constant const int E_SYSTEM                    =   2; /* Miscellaneous system error */
%constant const int E_NOFILE                    =   3; /* File nonexistent */
%constant const int E_BADFILE                   =   4; /* Bad file format */
%constant const int E_VERSION                   =   5; /* File version mismatch */
%constant const int E_DISKFULL                  =   6; /* Target disk is full */
%constant const int E_INCAPABLE                 =  11; /* Optional RI feature */
%constant const int E_UNIMPLEMENT               =  12; /* Unimplemented feature */
%constant const int E_LIMIT                     =  13; /* Arbitrary program limit */
%constant const int E_BUG                       =  14; /* Probably a bug in renderer */
%constant const int E_NOTSTARTED                =  23; /* RiBegin not called */
%constant const int E_NESTING                   =  24; /* Bad begin-end nesting */
%constant const int E_NOTOPTIONS                =  25; /* Invalid state for options */
%constant const int E_NOTATTRIBS                =  26; /* Invalid state for attribs */
%constant const int E_NOTPRIMS                  =  27; /* Invalid state for primitives */
%constant const int E_ILLSTATE                  =  28; /* Other invalid state */
%constant const int E_BADMOTION                 =  29; /* Badly formed motion block */
%constant const int E_BADSOLID                  =  30; /* Badly formed solid block */
%constant const int E_BADTOKEN                  =  41; /* Invalid token for request */
%constant const int E_RANGE                     =  42; /* Parameter out of range */
%constant const int E_CONSISTENCY               =  43; /* Parameters inconsistent */
%constant const int E_BADHANDLE                 =  44; /* Bad object/light handle */
%constant const int E_NOSHADER                  =  45; /* Can't load requested shader */
%constant const int E_MISSINGDATA               =  46; /* Required parameters not provided */
%constant const int E_SYNTAX                    =  47; /* Declare type syntax error */
%constant const int E_TOKENREDECLARED           =  48; /* Redeclaration of token */
%constant const int E_MATH                      =  61; /* Zerodivide, noninvert matrix, etc. */
%constant const int E_BADATTRIB                 = 140; /* Unsupported attribute */
%constant const int E_BADOPTION                 = 141; /* Unsupported option */
%constant const int E_SPACEREDECLARED           = 142; /* Redeclaration of space */
%constant const int E_NODISPLAY                 = 143; /* Can't load requested display server */
%constant const int E_ERRRERTOOBID              = 144; /* Image resolution too big */
%constant const int E_ERRBADSHADERPARAM         = 145; /* Parameter is not in shader param list */
%constant const int E_ERRSHADERPARAMMISMATCH    = 146; /* Value for parameter does not match declaration */
%constant const int E_ERRBADARRAYACCESSINSHADER = 147; /* Invalid array index done in a shader */
%constant const int E_SHADER_PRINTF             = 199; /* output of a shader's printf() */
%constant const int E_INFO                      =   0; /* Rendering stats and other info */
%constant const int E_WARNING                   =   1; /* Something seems wrong, maybe okay */
%constant const int E_ERROR                     =   2; /* Problem. Results may be wrong */
%constant const int E_SEVERE                    =   3; /* So bad you should probably abort */

#if defined (PRMAN_RIBCLIENT)
%constant const char* RIBCLIENT = "PRMan";
#elif defined (PIXIE_RIBCLIENT)
%constant const char* RIBCLIENT = "Pixie";
#elif defined (DELIGHT_RIBCLIENT)
%constant const char* RIBCLIENT = "3Delight";
#endif

#if (defined SWIGJAVA)
%include "RIBClient_java.i"

typedef float RtFloat;
typedef int RtInt;
typedef char* RtToken;
typedef int RtFilterFunc;
typedef int RtArchiveCallback;
typedef int RtBasis;
typedef float RtMatrix[4][4];
typedef float RtColor[];
// typedef int RtLightHandle;
// typedef void* RtObjectHandle;
// typedef int RtArchiveHandle;
typedef bool RtBoolean;

#elif defined(SWIGPYTHON)

typedef long RtFilterFunc;
typedef long RtProcSubdivFunc;
typedef long RtProcFreeFunc;
typedef void* RtArchiveCallback;
typedef float RtFloat;
typedef char* RtToken;
typedef bool RtBoolean;

%include "RIBClient_python.i"

#elif defined(SWIGRUBY)

%include "RIBClient_ruby.i"

typedef char* RtToken;
typedef float RtFloat;
typedef bool RtBoolean;
typedef int RtInt;
typedef void* RtArchiveCallback;

#elif defined(SWIGCSHARP)
%include "RIBClient_csharp.i"
#else
#endif

// Common typemap
%typemap(ret) (void)
{
  // My clean up code for each call returning void
  g_params.CleanUpArgStorage();
}


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
  RiExposure( RtFloat gain, RtFloat gamma )
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
  RiSkew( RtFloat angle,
          RtFloat dx1, RtFloat dy1, RtFloat dz1,
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

%rename(Begin) RiBegin;
EXTERN void RiBegin (RtToken name);

%rename(End) RiEnd;
EXTERN void RiEnd (void);

// We do not implement Context stuff because it can be done via object
// instances

%rename (FrameBegin) RiFrameBegin;
EXTERN void  RiFrameBegin( RtInt frame );

%rename (FrameEnd) RiFrameEnd;
EXTERN void RiFrameEnd( void );

%rename(WorldBegin) RiWorldBegin;
EXTERN void RiWorldBegin (void);

%rename(WorldEnd) RiWorldEnd;
EXTERN void RiWorldEnd (void);

%rename (Format) RiFormat;
EXTERN void RiFormat( RtInt xresolution,
		      RtInt yresolution,
		      RtFloat pixelaspectratio );

%rename (FrameAspectRatio) RiFrameAspectRatio;
EXTERN void RiFrameAspectRatio( RtFloat frameaspectratio );

%rename (ScreenWindow) RiScreenWindow;
EXTERN void  RiScreenWindow( RtFloat left,
			     RtFloat right,
			     RtFloat bottom,
			     RtFloat top );

%rename(CropWindow) RiCropWindow;
EXTERN void RiCropWindow( RtFloat xmin,
			  RtFloat xmax,
			  RtFloat ymin,
			  RtFloat ymax );

%rename(Projection) RiProjectionV;
EXTERN void RiProjectionV (RtToken name,
			   RtInt n, RtToken tokens[], RtPointer params[]);

%rename(Clipping) RiClipping;
EXTERN void RiClipping( RtFloat near,
			RtFloat far );

%rename(ClippingPlane) RiClippingPlane;
EXTERN void RiClippingPlane ( RtFloat nx,
			      RtFloat ny,
			      RtFloat nz,
			      RtFloat x,
			      RtFloat y,
			      RtFloat z);

%rename(DepthOfField) RiDepthOfField;
EXTERN void RiDepthOfField( RtFloat fstop,
			    RtFloat focallength,
			    RtFloat focaldistance );

%rename(Shutter) RiShutter;
EXTERN void RiShutter( RtFloat min,
		       RtFloat max );

%rename (PixelVariance) RiPixelVariance;
EXTERN void RiPixelVariance ( RtFloat variation );

%rename (PixelSamples) RiPixelSamples;
EXTERN void RiPixelSamples( RtFloat xsamples,
			    RtFloat ysamples );
%rename (PixelFilter) RiPixelFilter;
EXTERN void RiPixelFilter( RtFilterFunc filterfunc,
			   RtFloat xwidth,
			   RtFloat ywidth );

%rename (Exposure) RiExposure;
EXTERN void RiExposure( RtFloat gain,
			RtFloat gamma );

%rename (Imager) RiImagerV;
EXTERN void RiImagerV( RtToken name,
		       RtInt n, RtToken tokens[], RtPointer params[]);

%rename (Quantize) RiQuantize;
EXTERN void RiQuantize( RtToken type,
			RtInt one,
			RtInt min,
			RtInt max,
			RtFloat ditheramplitude );

%rename (DisplayChannel) RiDisplayChannelV;
EXTERN void RiDisplayChannelV( RtToken channel,
			       RtInt n, RtToken tokens[], RtPointer params[]);

%rename (Display) RiDisplayV;
EXTERN void RiDisplayV( RtToken name, RtToken type, RtToken mode,
			RtInt n, RtToken tokens[], RtPointer params[]);

%rename (Hider) RiHiderV;
EXTERN void RiHiderV( RtToken type,
		      RtInt n, RtToken tokens[], RtPointer params[]);

#if defined(PIXIE_RIBCLIENT) || defined(PRMAN_RIBCLIENT)
%rename (ColorSamples) RiColorSamples;
EXTERN void RiColorSamples( RtInt n, RtFloat nRGB[], RtFloat RGBn[] );
#endif

%rename (RelativeDetail) RiRelativeDetail;
EXTERN void RiRelativeDetail( RtFloat relativedetail );

%rename (Option) RiOptionV;
EXTERN void RiOptionV( RtToken name,
		       RtInt n, RtToken tokens[], RtPointer params[] );

%rename (AttributeBegin) RiAttributeBegin;
EXTERN void RiAttributeBegin();

%rename (AttributeEnd) RiAttributeEnd;
EXTERN void RiAttributeEnd();

%rename (Color) RiColor;
EXTERN void RiColor( RtColor color );

%rename (Opacity) RiOpacity;
EXTERN void RiOpacity( RtColor color );

%rename (TextureCoordinates) RiTextureCoordinates;
EXTERN void RiTextureCoordinates(RtFloat s1, RtFloat t1,
				 RtFloat s2, RtFloat t2,
				 RtFloat s3, RtFloat t3,
				 RtFloat s4, RtFloat t4);

%rename (LightSource) RiLightSourceV;
EXTERN RtLightHandle
RiLightSourceV(RtToken shadername,
	       RtInt n, RtToken tokens[], RtPointer params[] );

%rename (AreaLightSource) RiAreaLightSourceV;
EXTERN RtLightHandle
RiAreaLightSourceV( RtToken shadername,
		    RtInt n, RtToken tokens[], RtPointer params[] );

%rename (Illuminate) RiIlluminate;
EXTERN void RiIlluminate( RtLightHandle light, RtBoolean onoff );

%rename (Surface) RiSurfaceV;
EXTERN void RiSurfaceV( RtToken shadername,
			RtInt n, RtToken tokens[], RtPointer params[]);

%rename (Displacement) RiDisplacementV;
EXTERN void RiDisplacementV( RtToken shadername,
			     RtInt n, RtToken tokens[], RtPointer params[]);

%rename (Atmosphere) RiAtmosphereV;
EXTERN void RiAtmosphereV( RtToken shadername,
			   RtInt n, RtToken tokens[], RtPointer params[]);

%rename (Interior) RiInteriorV;
EXTERN void RiInteriorV( RtToken shadername,
			 RtInt n, RtToken tokens[], RtPointer params[]);

%rename (Exterior) RiExteriorV;
EXTERN void RiExteriorV( RtToken shadername,
			 RtInt n, RtToken tokens[], RtPointer params[]);

%rename (ShadingRate) RiShadingRate;
EXTERN void RiShadingRate( RtFloat size );

%rename (ShadingInterpolation) RiShadingInterpolation;
EXTERN void RiShadingInterpolation( RtToken type );

%rename (Matte) RiMatte;
EXTERN void RiMatte( RtBoolean onoff );

%rename (Bound) RiBound;
EXTERN void RiBound( RtBound bound );

%rename (Detail) RiDetail;
EXTERN void RiDetail( RtBound bound );

%rename (DetailRange) RiDetailRange;
EXTERN void RiDetailRange( RtFloat minvisible, RtFloat lowertransition,RtFloat uppertransition, RtFloat maxvisible );

%rename (GeometricApproximation) RiGeometricApproximation;
EXTERN void RiGeometricApproximation( RtToken type, RtFloat value );

%rename (Orientation) RiOrientation;
EXTERN void RiOrientation( RtToken orientation );

%rename (ReverseOrientation) RiReverseOrientation;
EXTERN void RiReverseOrientation();

%rename (Sides) RiSides;
EXTERN void RiSides( RtInt sides );

%rename (Identity) RiIdentity;
EXTERN void RiIdentity();

%rename (Transform) RiTransform;
EXTERN void RiTransform( RtMatrix tx);

%rename (ConcatTransform) RiConcatTransform;
EXTERN void RiConcatTransform( RtMatrix transform );

%rename (Perspective) RiPerspective;
EXTERN void RiPerspective( RtFloat fov );

%rename (Translate) RiTranslate;
EXTERN void RiTranslate( RtFloat dx, RtFloat dy, RtFloat dz );

%rename (Rotate) RiRotate;
EXTERN void RiRotate( RtFloat angle, RtFloat dx, RtFloat dy, RtFloat dz );

%rename (Scale) RiScale;
EXTERN void RiScale( RtFloat sx, RtFloat sy, RtFloat sz );

%rename (Skew) RiSkew;
EXTERN void RiSkew( RtFloat angle,
		    RtFloat dx1, RtFloat dy1, RtFloat dz1,
		    RtFloat dx2, RtFloat dy2, RtFloat dz2 );

%rename (CoordinateSystem) RiCoordinateSystem;
EXTERN void RiCoordinateSystem( RtToken space );

#if defined(PRMAN_RIBCLIENT) || defined(DELIGHT_RIBCLIENT)
%rename (ScopedCoordinateSystem) RiScopedCoordinateSystem;
EXTERN void RiScopedCoordinateSystem( RtToken name );
#endif

%rename (CoordSysTransform) RiCoordSysTransform;
EXTERN void RiCoordSysTransform ( RtToken name );

// Not sure if this is needed
//  RtPoint *RiTransformPoints( RtToken fromspace, RtToken tospace,
//                              RtInt n, RtPoint points )

%rename (TransformBegin) RiTransformBegin;
EXTERN void RiTransformBegin();

%rename (TransformEnd) RiTransformEnd;
EXTERN void RiTransformEnd();

%rename (Resource) RiResourceV;
EXTERN void RiResourceV( RtToken handle, RtToken type,
			 RtInt n, RtToken tokens[], RtPointer params[]);

#if defined(DELIGHT_RIBCLIENT)
%rename (ResourceBegin) RiResourceBegin;
EXTERN void RiResourceBegin();

%rename (ResourceEnd) RiResourceEnd;
EXTERN void RiResourceEnd();
#endif //

%rename (Attribute) RiAttributeV;
EXTERN void RiAttributeV( RtToken name,
			  RtInt n, RtToken tokens[], RtPointer params[]);
//=============================================================================


/*===========================================================================
  Geometry Primitives
  RiPolygon( RtInt nvertices, ...parameterlist... )
  RiGeneralPolygon( RtInt nloops, RtInt nvertices[], ...parameterlist... )
  RiPointsPolygons( RtInt npolys, RtInt nvertices[], RtInt vertices[], ...parameterlist...) 
  RiPointsGeneralPolygons( RtInt npolys, RtInt nloops, RtInt nvertices[], RtInt vertices[], ...parameterlist... )
  RiBasis( RtBasis ubasis, RtInt ustep, RtBasis vbasis, RtInt vstep )
  RiPatch( RtToken type, ...parameterlist... )
  RiPatchMesh( RtToken type, RtInt nu, RtToken uwrap, RtInt nv, RtInt vwrap, ...parameterlist...  )
  RiNuPatch( RtInt nu, RtInt uorder, RtFloat uknot[], RtFloat umin, RtFloat umax, RtInt nv, RtInt vorder, RtFloat vknot[], RtFloat vmin, RtFloat vmax, ...parameterlist... )
  RiTrimCurve( RtInt nloops, RtInt ncurves[], RtInt order[], RtFloat knot[], RtFloat min[], RtFloat max[], RtInt n[], RtFloat u[], RtFloat v[], RtFloat w[] )
  RiSubdivisionMesh ( RtToken scheme, RtInt nfaces, RtInt nvertices[], RtInt vertices[], RtInt ntags, RtToken tags[], RtInt nargs[], RtInt intargs[], RtFloat floatargs[], ..parameterlist...)
  RiSphere( RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat thetamax, ...parameterlist... )
  RiCone( RtFloat height, RtFloat radius, RtFloat thetamax, ...parameterlist... )
  RiCylinder( RtFloat radius, RtFloat zmin, RtFloat zmax, RtFloat thetamax, ...parameterlist... )
  RiHyperboloid( RtPoint point1, RtPoint point2, RtFloat thetamax, ...parameterlist... )
  RiParaboloid( RtFloat rmax, RtFloat zmin, RtFloat zmax, RtFloat thetamax, ...parameterlist... )
  RiDisk( RtFloat height, RtFloat radius, RtFloat thetamax, ...parameterlist... )
  RiTorus( RtFloat majorradius, RtFloat minorradius, RtFloat phimin, RtFloat phimax, RtFloat thetamax, ...parameterlist... )
  RiPoints ( RtInt npoints, ...parameterlist...)
  RiCurves ( RtToken type, RtInt ncurves, RtInt nvertices[], RtToken wrap, ...parameterlist...)
  RiBlobby ( RtInt nleaf, RtInt ncode, RtInt code[], RtInt nfloats, RtFloat floats[], RtInt nstrings, RtString strings[], ...parameterlist...)
  RiProcedural( RtPointer data, RtBound bound, RtProcSubdivFunc subdividefunc, RtProcFreeFunc freefunc )
  RiProcDelayedReadArchive ( RtPointer data, RtFloat detail )
  RiProcRunProgram ( RtPointer data, RtFloat detail )
  RiProcDynamicLoad ( RtPointer data, RtFloat detail )
  RiGeometry( RtToken type, ...parameterlist... )
  RiSolidBegin( RtToken operation )
  RiSolidEnd()
  RtObjectHandle RiObjectBegin()
  RiObjectEnd()
  RiObjectInstance( RtObjectHandle handle )
  =========================================================================*/

%rename (Polygon) RiPolygonV;
EXTERN void RiPolygonV( RtInt nvertices,
			RtInt n, RtToken tokens[], RtPointer params[]);

%rename (GeneralPolygon) RiGeneralPolygonV;
EXTERN void RiGeneralPolygonV( RtInt nloops, RtInt nvertices[],
			       RtInt n, RtToken tokens[], RtPointer params[]);

%rename (PointsPolygons) RiPointsPolygonsV;
EXTERN void
RiPointsPolygonsV( RtInt npolys, RtInt nvertices[], RtInt vertices[],
		   RtInt n, RtToken tokens[], RtPointer params[]);

%rename (PointsGeneralPolygons) RiPointsGeneralPolygonsV;
EXTERN void
RiPointsGeneralPolygonsV( RtInt npolys, RtInt nloops[],
			  RtInt nvertices[], RtInt vertices[],
			  RtInt n, RtToken tokens[], RtPointer params[]);
%rename(Basis) RiBasis;
EXTERN void RiBasis( RtBasis ubasis,
		     RtInt ustep,
		     RtBasis vbasis,
		     RtInt vstep );

%rename (Patch) RiPatchV;
EXTERN void RiPatchV( RtToken type,
		      RtInt n, RtToken tokens[], RtPointer params[]);

%rename (PatchMesh) RiPatchMeshV;
EXTERN void RiPatchMeshV( RtToken type,
			  RtInt nu, RtToken uwrap, RtInt nv, RtToken vwrap,
			  RtInt n, RtToken tokens[], RtPointer params[]);

%rename (NuPatch) RiNuPatchV;
EXTERN void RiNuPatchV( RtInt nu, RtInt uorder, RtFloat uknot[],
			RtFloat umin, RtFloat umax,
			RtInt nv, RtInt vorder, RtFloat vknot[],
			RtFloat vmin, RtFloat vmax,
			RtInt n, RtToken tokens[], RtPointer params[]);

%rename (TrimCurve) RiTrimCurve;
EXTERN void RiTrimCurve( RtInt nloops, RtInt ncurves[], RtInt order[],
			 RtFloat knot[], RtFloat min[], RtFloat max[],
			 RtInt n[], RtFloat u[], RtFloat v[], RtFloat w[] );

%rename (SubdivisionMesh) RiSubdivisionMeshV;
EXTERN void RiSubdivisionMeshV( RtToken scheme,
				RtInt nfaces, RtInt nvertices[],
				RtInt vertices[],
				RtInt ntags, RtToken tags[],
				RtInt nargs[],
				RtInt intargs[], RtFloat floatargs[],
				RtInt n, RtToken tokens[], RtPointer params[]);


%rename (Sphere) RiSphereV;
EXTERN void RiSphereV( RtFloat radius, RtFloat zmin, RtFloat zmax,
		       RtFloat thetamax,
		       RtInt n, RtToken tokens[], RtPointer params[] );

%rename (Cone) RiConeV;
EXTERN void RiConeV( RtFloat height, RtFloat radius, RtFloat thetamax,
		     RtInt n, RtToken tokens[], RtPointer params[] );

%rename (Cylinder) RiCylinderV;
EXTERN void RiCylinderV( RtFloat radius, RtFloat zmin, RtFloat zmax,
			 RtFloat thetamax,
			 RtInt n, RtToken tokens[], RtPointer params[] );

%rename (Hyperboloid) RiHyperboloidV;
EXTERN void RiHyperboloidV( RtPoint point1, RtPoint point2, RtFloat thetamax,
			    RtInt n, RtToken tokens[], RtPointer params[] );

%rename (Paraboloid) RiParaboloidV;
EXTERN void RiParaboloidV( RtFloat rmax, RtFloat zmin, RtFloat zmax,
			   RtFloat thetamax,
			   RtInt n, RtToken tokens[], RtPointer params[] );

%rename (Disk) RiDiskV;
EXTERN void RiDiskV( RtFloat height, RtFloat radius, RtFloat thetamax,
		     RtInt n, RtToken tokens[], RtPointer params[] );

%rename (Torus) RiTorusV;
EXTERN void RiTorusV( RtFloat majorradius, RtFloat minorradius,
		      RtFloat phimin, RtFloat phimax, RtFloat thetamax,
		      RtInt n, RtToken tokens[], RtPointer params[] );

%rename (Points) RiPointsV;
EXTERN void RiPointsV ( RtInt npoints,
			RtInt n, RtToken tokens[], RtPointer params[]);

%rename (Curves) RiCurvesV;
EXTERN void RiCurvesV ( RtToken type, RtInt ncurves, RtInt nvertices[],
			RtToken wrap,
			RtInt n, RtToken tokens[], RtPointer params[]);

%rename (Blobby) RiBlobbyV;
EXTERN void RiBlobbyV ( RtInt nleaf, RtInt ncode, RtInt code[],
			RtInt nfloats, RtFloat floats[],
			RtInt nstrings, RtString strings[],
			RtInt n, RtToken tokens[], RtPointer params[]);

%rename (Procedural) RiProcedural;
EXTERN void RiProcedural( RtToken data[],
                          RtBound bound,
                          RtProcSubdivFunc subdividefunc,
                          RtProcFreeFunc freefunc );

%rename (Geometry) RiGeometryV;
EXTERN void RiGeometryV( RtToken type,
			 RtInt n, RtToken tokens[], RtPointer params[] );

%rename (SolidBegin) RiSolidBegin;
EXTERN void RiSolidBegin( RtToken operation );

%rename (SolidEnd) RiSolidEnd;
EXTERN void RiSolidEnd();

%rename (ObjectBegin) RiObjectBegin;
EXTERN RtObjectHandle RiObjectBegin();

%rename (ObjectEnd) RiObjectEnd;
EXTERN void RiObjectEnd();

%rename (ObjectInstance) RiObjectInstance;
EXTERN void RiObjectInstance( RtObjectHandle handle );

/*===========================================================================
  Motion
  RiMotionBegin( RtInt n, RtFloat t0, RtFloat t1,..., RtFloat tnminus1 )
  RiMotionEnd()
  =========================================================================*/

%rename (MotionBegin) RiMotionBeginV;
EXTERN void RiMotionBeginV(RtInt n, RtFloat times[]);

%rename (MotionEnd) RiMotionEnd();
EXTERN void RiMotionEnd();

/*===========================================================================
  External Resources
  RiMakeTexture( char *picturename, char *texturename, RtToken swrap, RtToken twrap, RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, ...parameterlist... )
  RiMakeLatLongEnvironment( char *picturename, char *texturename, RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, ...parameterlist... )
  RiMakeCubeFaceEnvironment( char *px, char *nx, char *py, char *ny, char *pz, char *nz, char *texturename, RtFloat fov,  RtFilterFunc filterfunc, RtFloat swidth, RtFloat twidth, ...parameterlist... )
  RiMakeShadow( char *picturename, char *texturename, char *parameterlist )
  RiMakeBrickMap( int n, char **ptcnames, char *bkmname, char *parameterlist)
  RiSystem(char *cmd)
  RiErrorHandler( RtFunc handler )
  RiArchiveRecord( RtToken type, char *format [, arg ...] )
  RiReadArchive ( RtToken name, RtVoid (*callback)(RtToken, char*,...), ...parameterlist...)
  RtArchiveHandle RiArchiveBegin ( RtToken archivename, ...parameterlist...)
  RiArchiveEnd()
  RiIfBegin (RtToken expression)
  RiElseIf (RtToken expression)
  RiElse ()
  RiIfEnd ()
  =========================================================================*/

%rename (MakeTexture) RiMakeTextureV;
EXTERN void RiMakeTextureV( char *picturename, char *texturename,
			    RtToken swrap, RtToken twrap,
			    RtFilterFunc filterfunc,
			    RtFloat swidth, RtFloat twidth,
			    RtInt n, RtToken tokens[], RtPointer params[] );

%rename (MakeLatLongEnvironment) RiMakeLatLongEnvironmentV;
EXTERN void RiMakeLatLongEnvironmentV( char *picturename, char *texturename,
				       RtFilterFunc filterfunc,
				       RtFloat swidth, RtFloat twidth,
				       RtInt n, RtToken tokens[], RtPointer params[] );

%rename (MakeCubeFaceEnvironment) RiMakeCubeFaceEnvironmentV;
EXTERN void RiMakeCubeFaceEnvironmentV( char *px, char *nx,
					char *py, char *ny,
					char *pz, char *nz,
					char *texturename,
					RtFloat fov,  RtFilterFunc filterfunc,
					RtFloat swidth, RtFloat twidth,
					RtInt n, RtToken tokens[], RtPointer params[] );

%rename (MakeShadow)   RiMakeShadowV;
EXTERN void RiMakeShadowV( char *picturename, char *texturename,
			   RtInt n, RtToken tokens[], RtPointer params[] );
  
%rename (MakeBrickMap) RiMakeBrickMapV;
EXTERN void RiMakeBrickMapV( int n, RtToken ptcnames[], char *bkmname,
			     RtInt n, RtToken tokens[], RtPointer params[]);

%varargs(10,char *arg = NULL) RiArchiveRecord;
%rename (ArchiveRecord) RiArchiveRecord;
EXTERN void RiArchiveRecord( RtToken type, char *format, ...);

%rename (ReadArchive) RiReadArchiveV;
EXTERN void RiReadArchiveV ( RtToken name,
			     RtArchiveCallback func,
			     RtInt n, RtToken tokens[], RtPointer params[]);

%rename (ArchiveBegin) RiArchiveBeginV;
EXTERN RtArchiveHandle RiArchiveBeginV ( RtToken archivename,
					 RtInt n, RtToken tokens[], RtPointer params[]);

%rename (ArchiveEnd) RiArchiveEnd;
EXTERN void RiArchiveEnd();


/*===========================================================================
  Miscellaneous
  RiDeclare(char *name, char *declaration);
  =========================================================================*/

%rename (Declare) RiDeclare;
EXTERN RtToken RiDeclare(char *name, char *declaration);
