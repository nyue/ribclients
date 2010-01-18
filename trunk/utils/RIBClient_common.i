// -*- C++ -*-
// Procedural Insight 2007 

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
%constant const char* SEARCHPATH = "searchpath";
%constant const char* SHADER = "shader";
%constant const char* TEXTURE = "texture";
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
extern void RiBegin (RtToken name);

%rename(End) RiEnd;
extern void RiEnd (void);

// We do not implement Context stuff because it can be done via object
// instances

%rename (FrameBegin) RiFrameBegin;
extern void  RiFrameBegin( RtInt frame );

%rename (FrameEnd) RiFrameEnd;
extern void RiFrameEnd( void );

%rename(WorldBegin) RiWorldBegin;
extern void RiWorldBegin (void);

%rename(WorldEnd) RiWorldEnd;
extern void RiWorldEnd (void);

%rename (Format) RiFormat;
extern void RiFormat( RtInt xresolution,
		      RtInt yresolution,
		      RtFloat pixelaspectratio );

%rename (FrameAspectRatio) RiFrameAspectRatio;
extern void RiFrameAspectRatio( RtFloat frameaspectratio );

%rename (ScreenWindow) RiScreenWindow;
extern void  RiScreenWindow( RtFloat left,
			     RtFloat right,
			     RtFloat bottom,
			     RtFloat top );

%rename(CropWindow) RiCropWindow;
extern void RiCropWindow( RtFloat xmin,
			  RtFloat xmax,
			  RtFloat ymin,
			  RtFloat ymax );

%rename(Projection) RiProjectionV;
extern void RiProjectionV (RtToken name,
			   RtInt n, RtToken tokens[], RtPointer params[]);

%rename(Clipping) RiClipping;
extern void RiClipping( RtFloat near,
			RtFloat far );

%rename(ClippingPlane) RiClippingPlane;
extern void RiClippingPlane ( RtFloat nx,
			      RtFloat ny,
			      RtFloat nz,
			      RtFloat x,
			      RtFloat y,
			      RtFloat z);

%rename(DepthOfField) RiDepthOfField;
extern void RiDepthOfField( RtFloat fstop,
			    RtFloat focallength,
			    RtFloat focaldistance );

%rename(Shutter) RiShutter;
extern void RiShutter( RtFloat min,
		       RtFloat max );

%rename (PixelVariance) RiPixelVariance;
extern void RiPixelVariance ( RtFloat variation );

%rename (PixelSamples) RiPixelSamples;
extern void RiPixelSamples( RtFloat xsamples,
			    RtFloat ysamples );
%rename (PixelFilter) RiPixelFilter;
extern void RiPixelFilter( RtFilterFunc filterfunc,
			   RtFloat xwidth,
			   RtFloat ywidth );

%rename (Exposure) RiExposure;
extern void RiExposure( RtFloat gain,
			RtFloat gamma );

%rename (Imager) RiImagerV;
extern void RiImagerV( RtToken name,
		       RtInt n, RtToken tokens[], RtPointer params[]);

%rename (Quantize) RiQuantize;
extern void RiQuantize( RtToken type,
			RtInt one,
			RtInt min,
			RtInt max,
			RtFloat ditheramplitude );

%rename (DisplayChannel) RiDisplayChannelV;
extern void RiDisplayChannelV( RtToken channel,
			       RtInt n, RtToken tokens[], RtPointer params[]);

%rename (Display) RiDisplayV;
extern void RiDisplayV( RtToken name, RtToken type, RtToken mode,
			RtInt n, RtToken tokens[], RtPointer params[]);

%rename (Hider) RiHiderV;
extern void RiHiderV( RtToken type,
		      RtInt n, RtToken tokens[], RtPointer params[]);

#if defined(PIXIE_RIBCLIENT) || defined(PRMAN_RIBCLIENT)
%rename (ColorSamples) RiColorSamples;
extern void RiColorSamples( RtInt n, RtFloat nRGB[], RtFloat RGBn[] );
#endif

%rename (RelativeDetail) RiRelativeDetail;
extern void RiRelativeDetail( RtFloat relativedetail );

%rename (Option) RiOptionV;
extern void RiOptionV( RtToken name,
		       RtInt n, RtToken tokens[], RtPointer params[] );

%rename (AttributeBegin) RiAttributeBegin;
extern void RiAttributeBegin();

%rename (AttributeEnd) RiAttributeEnd;
extern void RiAttributeEnd();

%rename (Color) RiColor;
extern void RiColor( RtColor color );

%rename (Opacity) RiOpacity;
extern void RiOpacity( RtColor color );

%rename (TextureCoordinates) RiTextureCoordinates;
extern void RiTextureCoordinates(RtFloat s1, RtFloat t1,
				 RtFloat s2, RtFloat t2,
				 RtFloat s3, RtFloat t3,
				 RtFloat s4, RtFloat t4);

%rename (LightSource) RiLightSourceV;
extern RtLightHandle
RiLightSourceV(RtToken shadername,
	       RtInt n, RtToken tokens[], RtPointer params[] );

%rename (AreaLightSource) RiAreaLightSourceV;
extern RtLightHandle
RiAreaLightSourceV( RtToken shadername,
		    RtInt n, RtToken tokens[], RtPointer params[] );

%rename (Illuminate) RiIlluminate;
extern void RiIlluminate( RtLightHandle light, RtBoolean onoff );

%rename (Surface) RiSurfaceV;
extern void RiSurfaceV( RtToken shadername,
			RtInt n, RtToken tokens[], RtPointer params[]);

%rename (Displacement) RiDisplacementV;
extern void RiDisplacementV( RtToken shadername,
			     RtInt n, RtToken tokens[], RtPointer params[]);

%rename (Atmosphere) RiAtmosphereV;
extern void RiAtmosphereV( RtToken shadername,
			   RtInt n, RtToken tokens[], RtPointer params[]);

%rename (Interior) RiInteriorV;
extern void RiInteriorV( RtToken shadername,
			 RtInt n, RtToken tokens[], RtPointer params[]);

%rename (Exterior) RiExteriorV;
extern void RiExteriorV( RtToken shadername,
			 RtInt n, RtToken tokens[], RtPointer params[]);

%rename (ShadingRate) RiShadingRate;
extern void RiShadingRate( RtFloat size );

%rename (ShadingInterpolation) RiShadingInterpolation;
extern void RiShadingInterpolation( RtToken type );

%rename (Matte) RiMatte;
extern void RiMatte( RtBoolean onoff );

%rename (Bound) RiBound;
extern void RiBound( RtBound bound );

%rename (Detail) RiDetail;
extern void RiDetail( RtBound bound );

%rename (DetailRange) RiDetailRange;
extern void RiDetailRange( RtFloat minvisible, RtFloat lowertransition,RtFloat uppertransition, RtFloat maxvisible );

%rename (GeometricApproximation) RiGeometricApproximation;
extern void RiGeometricApproximation( RtToken type, RtFloat value );

%rename (Orientation) RiOrientation;
extern void RiOrientation( RtToken orientation );

%rename (ReverseOrientation) RiReverseOrientation;
extern void RiReverseOrientation();

%rename (Sides) RiSides;
extern void RiSides( RtInt sides );

%rename (Identity) RiIdentity;
extern void RiIdentity();

%rename (Transform) RiTransform;
extern void RiTransform( RtMatrix tx);

%rename (ConcatTransform) RiConcatTransform;
extern void RiConcatTransform( RtMatrix transform );

%rename (Perspective) RiPerspective;
extern void RiPerspective( RtFloat fov );

%rename (Translate) RiTranslate;
extern void RiTranslate( RtFloat dx, RtFloat dy, RtFloat dz );

%rename (Rotate) RiRotate;
extern void RiRotate( RtFloat angle, RtFloat dx, RtFloat dy, RtFloat dz );

%rename (Scale) RiScale;
extern void RiScale( RtFloat sx, RtFloat sy, RtFloat sz );

%rename (Skew) RiSkew;
extern void RiSkew( RtFloat angle,
		    RtFloat dx1, RtFloat dy1, RtFloat dz1,
		    RtFloat dx2, RtFloat dy2, RtFloat dz2 );

%rename (CoordinateSystem) RiCoordinateSystem;
extern void RiCoordinateSystem( RtToken space );

#if defined(PRMAN_RIBCLIENT) || defined(DELIGHT_RIBCLIENT)
%rename (ScopedCoordinateSystem) RiScopedCoordinateSystem;
extern void RiScopedCoordinateSystem( RtToken name );
#endif

%rename (CoordSysTransform) RiCoordSysTransform;
extern void RiCoordSysTransform ( RtToken name );

// Not sure if this is needed
//  RtPoint *RiTransformPoints( RtToken fromspace, RtToken tospace,
//                              RtInt n, RtPoint points )

%rename (TransformBegin) RiTransformBegin;
extern void RiTransformBegin();

%rename (TransformEnd) RiTransformEnd;
extern void RiTransformEnd();

%rename (Resource) RiResourceV;
extern void RiResourceV( RtToken handle, RtToken type,
			 RtInt n, RtToken tokens[], RtPointer params[]);

#if defined(DELIGHT_RIBCLIENT)
%rename (ResourceBegin) RiResourceBegin;
extern void RiResourceBegin();

%rename (ResourceEnd) RiResourceEnd;
extern void RiResourceEnd();
#endif //

%rename (Attribute) RiAttributeV;
extern void RiAttributeV( RtToken name,
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
extern void RiPolygonV( RtInt nvertices,
			RtInt n, RtToken tokens[], RtPointer params[]);

%rename (GeneralPolygon) RiGeneralPolygonV;
extern void RiGeneralPolygonV( RtInt nloops, RtInt nvertices[],
			       RtInt n, RtToken tokens[], RtPointer params[]);

%rename (PointsPolygons) RiPointsPolygonsV;
extern void
RiPointsPolygonsV( RtInt npolys, RtInt nvertices[], RtInt vertices[],
		   RtInt n, RtToken tokens[], RtPointer params[]);

%rename (PointsGeneralPolygons) RiPointsGeneralPolygonsV;
extern void
RiPointsGeneralPolygonsV( RtInt npolys, RtInt nloops[],
			  RtInt nvertices[], RtInt vertices[],
			  RtInt n, RtToken tokens[], RtPointer params[]);
%rename(Basis) RiBasis;
extern void RiBasis( RtBasis ubasis,
		     RtInt ustep,
		     RtBasis vbasis,
		     RtInt vstep );

%rename (Patch) RiPatchV;
extern void RiPatchV( RtToken type,
		      RtInt n, RtToken tokens[], RtPointer params[]);

%rename (PatchMesh) RiPatchMeshV;
extern void RiPatchMeshV( RtToken type,
			  RtInt nu, RtToken uwrap, RtInt nv, RtToken vwrap,
			  RtInt n, RtToken tokens[], RtPointer params[]);

%rename (NuPatch) RiNuPatchV;
extern void RiNuPatchV( RtInt nu, RtInt uorder, RtFloat uknot[],
			RtFloat umin, RtFloat umax,
			RtInt nv, RtInt vorder, RtFloat vknot[],
			RtFloat vmin, RtFloat vmax,
			RtInt n, RtToken tokens[], RtPointer params[]);

%rename (TrimCurve) RiTrimCurve;
extern void RiTrimCurve( RtInt nloops, RtInt ncurves[], RtInt order[],
			 RtFloat knot[], RtFloat min[], RtFloat max[],
			 RtInt n[], RtFloat u[], RtFloat v[], RtFloat w[] );

%rename (SubdivisionMesh) RiSubdivisionMeshV;
extern void RiSubdivisionMeshV( RtToken scheme,
				RtInt nfaces, RtInt nvertices[],
				RtInt vertices[],
				RtInt ntags, RtToken tags[],
				RtInt nargs[],
				RtInt intargs[], RtFloat floatargs[],
				RtInt n, RtToken tokens[], RtPointer params[]);


%rename (Sphere) RiSphereV;
extern void RiSphereV( RtFloat radius, RtFloat zmin, RtFloat zmax,
		       RtFloat thetamax,
		       RtInt n, RtToken tokens[], RtPointer params[] );

%rename (Cone) RiConeV;
extern void RiConeV( RtFloat height, RtFloat radius, RtFloat thetamax,
		     RtInt n, RtToken tokens[], RtPointer params[] );

%rename (Cylinder) RiCylinderV;
extern void RiCylinderV( RtFloat radius, RtFloat zmin, RtFloat zmax,
			 RtFloat thetamax,
			 RtInt n, RtToken tokens[], RtPointer params[] );

%rename (Hyperboloid) RiHyperboloidV;
extern void RiHyperboloidV( RtPoint point1, RtPoint point2, RtFloat thetamax,
			    RtInt n, RtToken tokens[], RtPointer params[] );

%rename (Paraboloid) RiParaboloidV;
extern void RiParaboloidV( RtFloat rmax, RtFloat zmin, RtFloat zmax,
			   RtFloat thetamax,
			   RtInt n, RtToken tokens[], RtPointer params[] );

%rename (Disk) RiDiskV;
extern void RiDiskV( RtFloat height, RtFloat radius, RtFloat thetamax,
		     RtInt n, RtToken tokens[], RtPointer params[] );

%rename (Torus) RiTorusV;
extern void RiTorusV( RtFloat majorradius, RtFloat minorradius,
		      RtFloat phimin, RtFloat phimax, RtFloat thetamax,
		      RtInt n, RtToken tokens[], RtPointer params[] );

%rename (Points) RiPointsV;
extern void RiPointsV ( RtInt npoints,
			RtInt n, RtToken tokens[], RtPointer params[]);

%rename (Curves) RiCurvesV;
extern void RiCurvesV ( RtToken type, RtInt ncurves, RtInt nvertices[],
			RtToken wrap,
			RtInt n, RtToken tokens[], RtPointer params[]);

%rename (Blobby) RiBlobbyV;
extern void RiBlobbyV ( RtInt nleaf, RtInt ncode, RtInt code[],
			RtInt nfloats, RtFloat floats[],
			RtInt nstrings, RtString strings[],
			RtInt n, RtToken tokens[], RtPointer params[]);

/*
%rename (Procedural) RiProcedural;
extern void RiProcedural( RtToken data[],
			  RtBound bound,
			  RtProcSubdivFunc subdividefunc,
			  RtProcFreeFunc freefunc );
*/

%rename (Geometry) RiGeometryV;
extern void RiGeometryV( RtToken type,
			 RtInt n, RtToken tokens[], RtPointer params[] );

%rename (SolidBegin) RiSolidBegin;
extern void RiSolidBegin( RtToken operation );

%rename (SolidEnd) RiSolidEnd;
extern void RiSolidEnd();

%rename (ObjectBegin) RiObjectBegin;
extern RtObjectHandle RiObjectBegin();

%rename (ObjectEnd) RiObjectEnd;
extern void RiObjectEnd();

%rename (ObjectInstance) RiObjectInstance;
extern void RiObjectInstance( RtObjectHandle handle );

/*===========================================================================
  Motion
  RiMotionBegin( RtInt n, RtFloat t0, RtFloat t1,..., RtFloat tnminus1 )
  RiMotionEnd()
  =========================================================================*/

%rename (MotionBegin) RiMotionBeginV;
extern void RiMotionBeginV(RtInt n, RtFloat times[]);

%rename (MotionEnd) RiMotionEnd();
extern void RiMotionEnd();

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
extern void RiMakeTextureV( char *picturename, char *texturename,
			    RtToken swrap, RtToken twrap,
			    RtFilterFunc filterfunc,
			    RtFloat swidth, RtFloat twidth,
			    RtInt n, RtToken tokens[], RtPointer params[] );

%rename (MakeLatLongEnvironment) RiMakeLatLongEnvironmentV;
extern void RiMakeLatLongEnvironmentV( char *picturename, char *texturename,
				       RtFilterFunc filterfunc,
				       RtFloat swidth, RtFloat twidth,
				       RtInt n, RtToken tokens[], RtPointer params[] );

%rename (MakeCubeFaceEnvironment) RiMakeCubeFaceEnvironmentV;
extern void RiMakeCubeFaceEnvironmentV( char *px, char *nx,
					char *py, char *ny,
					char *pz, char *nz,
					char *texturename,
					RtFloat fov,  RtFilterFunc filterfunc,
					RtFloat swidth, RtFloat twidth,
					RtInt n, RtToken tokens[], RtPointer params[] );

%rename (MakeShadow)   RiMakeShadowV;
extern void RiMakeShadowV( char *picturename, char *texturename,
			   RtInt n, RtToken tokens[], RtPointer params[] );
  
%rename (MakeBrickMap) RiMakeBrickMapV;
extern void RiMakeBrickMapV( int n, RtToken ptcnames[], char *bkmname,
			     RtInt n, RtToken tokens[], RtPointer params[]);

%varargs(10,char *arg = NULL) RiArchiveRecord;
%rename (ArchiveRecord) RiArchiveRecord;
extern void RiArchiveRecord( RtToken type, char *format, ...);

%rename (ReadArchive) RiReadArchiveV;
extern void RiReadArchiveV ( RtToken name,
			     RtArchiveCallback func,
			     RtInt n, RtToken tokens[], RtPointer params[]);

%rename (ArchiveBegin) RiArchiveBeginV;
extern RtArchiveHandle RiArchiveBeginV ( RtToken archivename,
					 RtInt n, RtToken tokens[], RtPointer params[]);

%rename (ArchiveEnd) RiArchiveEnd;
extern void RiArchiveEnd();


/*===========================================================================
  Miscellaneous
  RiDeclare(char *name, char *declaration);
  =========================================================================*/

%rename (Declare) RiDeclare;
extern RtToken RiDeclare(char *name, char *declaration);
