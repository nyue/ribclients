import java.util.*;

public class testribclient {
    //Load the library
    static {
        System.loadLibrary("ribclient");
    }

    private static void MapTextureAPIs() {
	ribclient.MakeTexture("nicholas.tif","nicholas.tex",
			 ribclient.PERIODIC,ribclient.PERIODIC,
			 ribclient.TRIANGLEFILTER,
			 3.0f,3.0f,null);
	ribclient.MakeLatLongEnvironment("nicholas.tif","nicholas.tex",
				    ribclient.TRIANGLEFILTER,
				    3.0f,3.0f,null);
	ribclient.MakeCubeFaceEnvironment("left.tif","right.tif",
				      "front.tif","back.tif",
				      "top.tif","bottom.tif",
				      "nicholas.tex",
				      25.0f,
				      ribclient.TRIANGLEFILTER,
				      3.0f,3.0f,null);
	ribclient.MakeShadow("dark.tif","dark.tex",null);
	String ptc[] = {"left.ptc","right.ptc",
			  "front.ptc","back.ptc",
			  "top.ptc","bottom.ptc"};
	ribclient.MakeBrickMap(6,ptc,"dark.bkm",null);
    }

    private static void MotionAPIs() {
	ribclient.AttributeBegin();
	float times[] = {0.0f,1.0f};
	ribclient.Sphere(1,-1,1,360,null);
	ribclient.MotionBegin(2,times);
	ribclient.Translate(0,0,0);
	ribclient.Translate(1,0,0);
	ribclient.MotionEnd();
	ribclient.AttributeEnd();
    }

    private static void ObjectAPIs() {
	SWIGTYPE_p_RtObjectHandle obj = ribclient.ObjectBegin();
	  ribclient.SolidBegin(ribclient.DIFFERENCE);
	    ribclient.Sphere(1,-1,1,360,null);
	    ribclient.Translate(0.5f,0.5f,0);
	    ribclient.Sphere(1,-1,1,360,null);
	  ribclient.SolidEnd();
	ribclient.ObjectEnd();

	ribclient.ObjectInstance(obj);
    }

    private static void SolidAPIs() {
	ribclient.AttributeBegin();

	ribclient.SolidBegin(ribclient.UNION);
	ribclient.Sphere(1,-1,1,360,null);
	ribclient.Sphere(1,-1,1,360,null);
	ribclient.SolidEnd();

	ribclient.AttributeEnd();
    }

    private static void ProceduralAPIs() {
	String commands[] = {"myprog.exe"};
	float bounds[] = { 0,1,0,1,0,1 };
	//  ribclient.Procedural(commands,bounds,ribclient.PROCRUNPROGRAM,ribclient.PROCFREE);
    }

    private static void BlobbyAPIs() {
	int nleafs = 2;
	int ncode = 8;
	int code[] = {
	    // Definitions
	    1001, 0,
	    1001, 16,
	    // Operations
	    0, 2, 0, 1
        };
	int nflt = 32;
	float flt[] = {
	    // Blob 0
	    1, 0, 0, 0,
	    0, 1, 0, 0,
	    0, 0, 1, 0,
	    0, 0, 0, 1,
	    // Blob 1
	    1, 0, 0, 0,
	    0, 1, 0, 0,
	    0, 0, 1, 0,
	    0, 1, 0, 1
        };
	int nstr = 0;
	String strings[] = null;
	ribclient.AttributeBegin();
	ribclient.Blobby(nleafs, ncode, code, nflt, flt, nstr, strings,null);
	ribclient.AttributeEnd();
    }

    private static void CurvesAPIs() {
	float width[] = {0.1f};
	float P[] = {0,0,0,
		     1,1,1,
		     1,1,0,
		     2,1,1,
		     1,2,1};
	int nvertices[] = {4};
	Hashtable ht = new Hashtable();
	ht.put(ribclient.P,P);
	ht.put(ribclient.CONSTANTWIDTH,width);
	ribclient.AttributeBegin();
	ribclient.Curves(ribclient.CUBIC,1,nvertices,ribclient.NONPERIODIC,ht);
	ribclient.AttributeEnd();
    }

    private static void PointsAPIs() {
	int sideSize = 3;
	int totalPointCount = sideSize * sideSize * sideSize;
	float P[] = new float [3 * totalPointCount];
	int index = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	while ( i < sideSize ) {
	    while ( j < sideSize ) {
		while ( k < sideSize ) {
		    P[index++] = i;
		    P[index++] = j;
		    P[index++] = k;
		    k++;
		}
		j++;
	    }
	    i++;
	}
	float width[] = {0.1f};
	Hashtable ht = new Hashtable();
	ht.put(ribclient.P,P);
	ht.put(ribclient.CONSTANTWIDTH,width);
	ribclient.AttributeBegin();
	ribclient.Points(totalPointCount,ht);
	ribclient.AttributeEnd();
    }

    private static void ConicAPIs() {
	ribclient.AttributeBegin();
	ribclient.Sphere(1.0f,-1.0f,1.0f,360.0f,null);
	ribclient.Cone(1.0f,1.0f,360.0f,null);
	ribclient.Cylinder(1.0f,-1.0f,1.0f,360.0f,null);
	float point1[] = {0.0f,-0.5f,+0.5f};
	float point2[] = {1.0f,+1.0f,-0.5f};
	ribclient.Hyperboloid(point1,point2,360.0f,null);
	ribclient.Paraboloid(1.0f,-1.0f,1.0f,360.0f,null);
	ribclient.Disk(0.1f,0.5f,360.0f,null);
	ribclient.Torus(2.0f,0.1f,270.0f,360.0f,360.0f,null);
	ribclient.AttributeEnd();
    }

    private static void SubdivMeshAPIs() {
	String scheme = ribclient.CATMULLCLARK;
	int nfaces = 1;
	int nvertices[] = {4};
	int vertices[] = {0, 1, 2, 3};
	int ntags = 1;
	String tags[] = {ribclient.INTERPOLATEBOUNDARY};
	int nargs[] = {0, 0};
	int intargs[] = {};
	float floatargs[] = {};
	float P[] = { -1.0f, 1.0f,0.0f,
		      +1.0f, 1.0f,0.0f,
		      +1.0f,-1.0f,0.0f,
		      -1.0f,-1.0f,0.0f};
	Hashtable ht = new Hashtable();
	ht.put(ribclient.P,P);
	ribclient.AttributeBegin();
	ribclient.SubdivisionMesh(scheme,
			     nfaces,
			     nvertices,
			     vertices,
			     ntags,
			     tags,
			     nargs,
			     intargs,
			     floatargs,
			     ht);
	ribclient.AttributeEnd();
    }
    
    private static void TrimCurveAPIs() {
	int nloops = 1;
	int ncurves[] = {1};
	int order[] = {3};
	float knot[] = {
	    0.000000f,0.000000f,0.000000f,
	    0.142857f,0.285714f,0.428571f,0.571429f,0.714286f,0.857143f,
	    1.000000f,1.000000f,1.000000f
        };
	float min[] = {0};
	float max[] = {4};
	int n[] = {9};
	float u[] = {0.9f,0.9f,0.9f,0.1f,0.1f,0.1f,0.9f,0.9f,0.9f};
	float v[] = {0.5f,0.7f,0.9f,0.9f,0.5f,0.1f,0.1f,0.1f,0.5f};
	float w[] = {1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f};
	ribclient.TrimCurve(nloops,ncurves,order,knot,min,max,n,u,v,w);
    }

    private static void NURBSAPIs() {
	int nu = 7;
	int uorder = 4;
	float uknot[] = {0f, 0f, 0f, 0f, 0.25f, 0.5f, 0.75f, 1f, 1f, 1f, 1};
	float umin = 0;
	float umax = 1;
	int nv = 9;
	int vorder = 4;
	float vknot[] = {0f, 0f, 0f, 0f, 0.166667f, 0.333333f, 0.5f, 0.666667f, 0.833333f, 1f, 1f, 1f, 1};
	float vmin = 0;
	float vmax = 1;
	float P[] = {
	    -0.5f,      -0.5f,      0f,        1f,
	    -0.5f,      -0.416667f, 0f,        1f,
	    -0.5f,      -0.25f,     0f,        1f,
	    -0.5f,       0f,        0f,        1f,
	    -0.5f,       0.25f,     0f,        1f,
	    -0.5f,       0.416667f, 0f,        1f,
	    -0.5f,       0.5f,      0f,        1f,
	    
	    -0.444444f, -0.5f,      0f,        1f,
	    -0.444444f, -0.416667f, 0f,        1f,
	    -0.444444f, -0.25f,     0f,        1f,
	    -0.444444f,  0f,        0f,        1f,
	    -0.444444f,  0.25f,     0f,        1f,
	    -0.444444f,  0.416667f, 0f,        1f,
	    -0.444444f,  0.5f,      0f,        1f,
	    
	    -0.333333f, -0.5f,      0f,        1f,
	    -0.333333f, -0.416667f, 0f,        1f,
	    -0.333333f, -0.25f,     0f,        1f,
	    -0.333333f,  0f,        0f,        1f,
	    -0.333333f,  0.25f,     0f,        1f,
	    -0.333333f,  0.416667f, 0f,        1f,
	    -0.333333f,  0.5f,      0f,        1f,
	    
	    -0.166667f, -0.5f,      0f,        1f,
	    -0.166667f, -0.416667f, 0f,        1f,
	    -0.166667f, -0.25f,     0.124372f, 1f,
	    -0.166667f,  0f,        0.124372f, 1f,
	    -0.166667f,  0.25f,     0.124372f, 1f,
	    -0.166667f,  0.416667f, 0f,        1f,
	    -0.166667f,  0.5f,      0f,        1f,
	    
	    0f,        -0.5f,      0f,        1f,
	    0f,        -0.416667f, 0f,        1f,
	    0f,        -0.25f,     0.124372f, 1f,
	    0f,         0f,        1.07474f,  1f,
	    0f,         0.25f,     0.124372f, 1f,
	    0f,         0.416667f, 0f,        1f,
	    0f,         0.5f,      0f,        1f,
	    
	    0.166667f, -0.5f,      0f,        1f,
	    0.166667f, -0.416667f, 0f,        1f,
	    0.166667f, -0.25f,     0.124372f, 1f,
	    0.166667f,  0f,        0.124372f, 1f,
	    0.166667f,  0.25f,     0.124372f, 1f,
	    0.166667f,  0.416667f, 0f,        1f,
	    0.166667f,  0.5f,      0f,        1f,
	    
	    0.333333f, -0.5f,      0f,        1f,
	    0.333333f, -0.416667f, 0f,        1f,
	    0.333333f, -0.25f,     0f,        1f,
	    0.333333f,  0f,        0f,        1f,
	    0.333333f,  0.25f,     0f,        1f,
	    0.333333f,  0.416667f, 0f,        1f,
	    0.333333f,  0.5f,      0f,        1f,
	    
	    0.444444f, -0.5f,      0f,        1f,
	    0.444444f, -0.416667f, 0f,        1f,
	    0.444444f, -0.25f,     0f,        1f,
	    0.444444f,  0f,        0f,        1f,
	    0.444444f,  0.25f,     0f,        1f,
	    0.444444f,  0.416667f, 0f,        1f,
	    0.444444f,  0.5f,      0f,        1f,
	    
	    0.5f,      -0.5f,      0f,        1f,
	    0.5f,      -0.416667f, 0f,        1f,
	    0.5f,      -0.25f,     0f,        1f,
	    0.5f,       0f,        0f,        1f,
	    0.5f,       0.25f,     0f,        1f,
	    0.5f,       0.416667f, 0f,        1f,
	    0.5f,       0.5f,      0f,        1f
        };
	Hashtable ht = new Hashtable();
	ht.put(ribclient.P,P);
	ribclient.AttributeBegin();
	ribclient.NuPatch(nu,uorder,uknot,umin,umax,
		     nv,vorder,vknot,vmin,vmax,ht);
	ribclient.AttributeEnd();
    }

    private static void Nurbs() {
	NURBSAPIs();
	TrimCurveAPIs();
    }

    private static void PatchAPIs() {
	float P[] = { -1.0f,  1.0f, 0.0f,
		       1.0f,  1.0f, 0.0f,
		      -1.0f, -1.0f, 0.0f,
		       1.0f, -1.0f, 0.0f};
	Hashtable ht = new Hashtable();
	ht.put(ribclient.P,P);
	ribclient.AttributeBegin();
	ribclient.Patch(ribclient.BILINEAR,ht);
	ribclient.PatchMesh(ribclient.BILINEAR,
		       4, ribclient.NONPERIODIC,
		       4, ribclient.NONPERIODIC,ht);
	ribclient.AttributeEnd();
    }

    private static void PolygonalAPIs() {
	ribclient.AttributeBegin();
	float P[] = {-1.0f,  1.0f, 0.0f,
		      1.0f,  1.0f, 0.0f,
		      1.0f, -1.0f, 0.0f,
		     -1.0f, -1.0f, 0.0f};
	Hashtable ht = new Hashtable();
	ht.put(ribclient.P,P);
	int npolys = 1;
	int nvertices = 4;
	int nvertices_a[] = {4};
	int vertices_a[] = {0,1,2,3};
	int nloops = 1;
	int nloops_a[] = {1};
	ribclient.Polygon(nvertices,ht);
	ribclient.GeneralPolygon(nloops,nvertices_a,ht);
	ribclient.PointsPolygons(nloops,nvertices_a,vertices_a,ht);
	ribclient.PointsGeneralPolygons(npolys,nloops_a,nvertices_a,vertices_a,ht);


	ribclient.AttributeEnd();
    }

    public static void main(String arg[]) {
	System.out.println("ribclienttest START\n");
	Hashtable ht = new Hashtable();
	boolean useOriginalTestCode = true;
	if (useOriginalTestCode) {
	    Float Ka[] = new Float[1];
	    Ka[0] = 0.5f;
	    Float Kd[] = new Float[1];
	    Kd[0] = 0.1f;
	    Float from[] = new Float[3];
	    from[0] = -4.17f;
	    from[1] = 2.25f;
	    from[2] = 1.79f;
	    Double to[] = new Double[3];
	    to[0] = 3.1479183719832;
	    to[1] = -87.13871298731;
	    to[2] = 0.0006177389717;
	    Integer indices[] = new Integer[4];
	    indices[0] = 217;
	    indices[1] = 17;
	    indices[2] = 769;
	    indices[3] = 23;
	    String textures[] = new String[2];
	    textures[0] = "/tmp/wood.tex";
	    textures[1] = "/tmp/procedural/skin.tex";
	    float weights[] = new float[2];
	    weights[0] = 0.50f;
	    weights[1] = 0.75f;
	    double densities[] = new double[3];
	    densities[0] = 0.177381236;
	    densities[1] = 0.798496287;
	    densities[2] = 0.638937846;
	    int IDs[] = new int[2];
	    IDs[0] = 17;
	    IDs[1] = 7;
	    
	    
	    
	    ht.put(new String("Ka"),Ka);
	    ht.put(new String("Kd"),Kd);
	    ht.put(new String("from"),from);
	    ht.put(new String("to"),to);
	    ht.put(new String("indices"),indices);
	    ht.put(new String("textures"),textures);
	    ht.put(new String("weights"),weights);
	    ht.put(new String("densities"),densities);
	    ht.put(new String("IDs"),IDs);
	    
	    // Use the following to trigger an exception in ribclient
	    // Float singleFloat = new Float(1);
	    // ht.put(new String("singleFloat"),singleFloat);
	} else {
	    Float fv[] = new Float[3];
	    fv[0] = 27.5f;
	    fv[1] = 0.75f;
	    fv[2] = -1.75f;
	    ht.put(new String("fov"),fv);
	}
	ribclient.Begin("testribclient.rib");
	ribclient.FrameBegin(5);
	ribclient.Projection(ribclient.PERSPECTIVE,ht);
	ribclient.Format(480,320,1.01f);
	ribclient.FrameAspectRatio(1.02f);
	ribclient.ScreenWindow(0.0f,1.0f,0.0f,1.0f);
	ribclient.CropWindow(0.0f,1.0f,0.0f,1.0f);
	ribclient.Clipping(0.1f,10000.0f);
	ribclient.ClippingPlane(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	ribclient.DepthOfField(8.0f, 200.0f, 50.0f);
	ribclient.Shutter(0.1f, 0.9f);

	ribclient.PixelVariance(0.2f);
	ribclient.PixelSamples(4.0f,6.0f);
	ribclient.PixelFilter(ribclient.TRIANGLEFILTER,3.0f,3.0f);
	ribclient.Exposure(1.0f,1.8f);
	ribclient.Imager(ribclient.BACKGROUND,ht);
	ribclient.Quantize("box",1,1,256,1.0f);
	{
	    Hashtable dcht = new Hashtable();
	    Float filterwidth[] = new Float [2];
	    filterwidth[0] = 47.1f;
	    filterwidth[1] = 93.27f;
	    Double fill[] = new Double [3];
	    fill[0] = 2.0;
	    fill[1] = 7.0;
	    fill[2] = 3.0;
	    int indices[] = new int [2];
	    indices[0] = 217;
	    indices[1] = 797;
	    String filter[] = new String [1];
	    filter[0] = "triangle";
	    dcht.put(new String("string filter"),filter);
	    dcht.put(new String("float[2] filterwidth"),filterwidth);
	    dcht.put(new String("point fill"),fill);
	    dcht.put(new String("int[2] indices"),indices);
	    ribclient.DisplayChannel("varying point P",dcht);
	}
	ribclient.Display("myimage.tif",ribclient.FRAMEBUFFER,ribclient.RGBA,ht);
	ribclient.Hider(ribclient.HIDDEN,null);
	float inRGB[] = {.3f,.3f,.4f};
	float outRGB[] = {1,1,1};
	// ribclient.ColorSamples(1,inRGB,outRGB);
	ribclient.RelativeDetail(3.141592654f);
	ht.clear();
	int endofframe[] = {1};
	ht.put(new String("int endofframe"),endofframe);
	ribclient.Option("statistics",ht);
	ribclient.WorldBegin();
	ribclient.AttributeBegin();

	// Color samples > 3 needs to be tested and verified
	float mycolor[] = {0.5f,0.7f,0.1f,0.2f};
	ribclient.Color(mycolor);
	float myopacity[] = {0.1f,0.9f,0.3f,0.6f};
	ribclient.Opacity(myopacity);

	ribclient.TextureCoordinates(0.1f,0.3f,0.5f,0.7f,0.9f,0.2f,0.4f,0.6f);

	SWIGTYPE_p_RtLightHandle pointlightID = ribclient.LightSource("pointlight",null);
	SWIGTYPE_p_RtLightHandle arealightID = ribclient.AreaLightSource("fluoro",null);

	ribclient.Illuminate(pointlightID,false);
	ribclient.Illuminate(arealightID,true);

	ribclient.Surface("mysurface",null);
	ribclient.Displacement("mydisplacement",null);
	ribclient.Atmosphere("myatmosphere",null);
	ribclient.Interior("myinterior",null);
	ribclient.Exterior("myexterior",null);

	ribclient.ShadingRate(0.1f);
	ribclient.ShadingInterpolation(ribclient.SMOOTH);
	ribclient.Matte(false);
	
	ribclient.AttributeEnd();
	float bounds[] = new float[6];
	bounds[0] = 0;
	bounds[1] = 5;
	bounds[2] = 0;
	bounds[3] = 2;
	bounds[4] = 0;
	bounds[5] = 7;
	ribclient.Bound(bounds);

	ribclient.Detail(bounds);
	ribclient.DetailRange(0,0,10,20);
	ribclient.GeometricApproximation(ribclient.FLATNESS,2.4f);
	ribclient.Orientation(ribclient.RH);
	ribclient.ReverseOrientation();
	ribclient.Sides(2);
	ribclient.Identity();

	ribclient.Basis(ribclient.CATMULLROMBASIS,1,ribclient.POWERBASIS,4);
	float tx[][] = {{1,1,1,1},{2,2,2,2},{3,3,3,3},{4,4,4,4}};
	ribclient.Transform(tx);

	ribclient.ConcatTransform(tx);
	ribclient.Perspective(4);
	ribclient.Translate(1,2,3);
	ribclient.Rotate(90,0,1,0);
	ribclient.Scale(2,4,6);
	ribclient.Skew(45, 0, 1, 0, 1, 0, 0);

	ribclient.TransformBegin();
	ribclient.CoordinateSystem(ribclient.WORLD);
	/*
	int ribClientCompareResult = ribclient.RIBCLIENT.compareTo("PRMan");
	System.out.println("ribClientCompareResult : " + ribClientCompareResult + "\n");
	if (ribClientCompareResult == 0) {
	    // ribclient.ScopedCoordinateSystem(ribclient.CAMERA);
	}
	*/
	ribclient.CoordSysTransform(ribclient.OBJECT);
	ribclient.TransformEnd();

	// ribclient.ResourceBegin();
	ribclient.Resource("ecwserver","texture",null);
	ht.clear();
	float sphericalDB[] = {0.2f};
	ht.put(new String("uniform float sphere"),sphericalDB);
	ribclient.Attribute("displacementbound",ht);
	// ribclient.ResourceEnd();

	PolygonalAPIs();
	PatchAPIs();
	Nurbs();
	SubdivMeshAPIs();
	ConicAPIs();

	BlobbyAPIs();
	CurvesAPIs();
	PointsAPIs();
	
	ProceduralAPIs();

	ribclient.Geometry("teapot",null);

	SolidAPIs();

	ObjectAPIs();

	MotionAPIs();

	MapTextureAPIs();

	ribclient.ArchiveRecord(ribclient.COMMENT,"dir");

	ribclient.ReadArchive("nicholas.rib",0,null);

	ribclient.ArchiveBegin("mysphere",null);
	ribclient.Sphere(1,-1,1,360,null);
	ribclient.ArchiveEnd();

	ribclient.ReadArchive("mysphere",0,null);

	ribclient.Declare("nicholas","uniform float");

	ribclient.WorldEnd();
	ribclient.FrameEnd();
	ribclient.End();

	// System.out.println("ribclienttest RIBClient is from " + ribclient.RIBCLIENT + "\n");
	System.out.println("ribclienttest FINISH\n");
    }
    
}
