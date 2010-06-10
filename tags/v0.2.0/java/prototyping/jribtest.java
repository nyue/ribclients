import java.util.*;

public class jribtest {
    //Load the library
    static {
        System.loadLibrary("ribclient");
    }

    private static void MapTextureAPIs() {
	jrib.MakeTexture("nicholas.tif","nicholas.tex",
			 jrib.PERIODIC,jrib.PERIODIC,
			 jrib.TRIANGLEFILTER,
			 3.0f,3.0f,null);
	jrib.MakeLatLongEnvironment("nicholas.tif","nicholas.tex",
				    jrib.TRIANGLEFILTER,
				    3.0f,3.0f,null);
	jrib.MakeCubeFaceEnvironment("left.tif","right.tif",
				      "front.tif","back.tif",
				      "top.tif","bottom.tif",
				      "nicholas.tex",
				      25.0f,
				      jrib.TRIANGLEFILTER,
				      3.0f,3.0f,null);
	jrib.MakeShadow("dark.tif","dark.tex",null);
	String ptc[] = {"left.ptc","right.ptc",
			  "front.ptc","back.ptc",
			  "top.ptc","bottom.ptc"};
	jrib.MakeBrickMap(6,ptc,"dark.bkm",null);
    }

    private static void MotionAPIs() {
	jrib.AttributeBegin();
	float times[] = {0.0f,1.0f};
	jrib.Sphere(1,-1,1,360,null);
	jrib.MotionBegin(2,times);
	jrib.Translate(0,0,0);
	jrib.Translate(1,0,0);
	jrib.MotionEnd();
	jrib.AttributeEnd();
    }

    private static void ObjectAPIs() {
	int obj = jrib.ObjectBegin();
	  jrib.SolidBegin(jrib.DIFFERENCE);
	    jrib.Sphere(1,-1,1,360,null);
	    jrib.Translate(0.5f,0.5f,0);
	    jrib.Sphere(1,-1,1,360,null);
	  jrib.SolidEnd();
	jrib.ObjectEnd();

	jrib.ObjectInstance(obj);
    }

    private static void SolidAPIs() {
	jrib.AttributeBegin();

	jrib.SolidBegin(jrib.UNION);
	jrib.Sphere(1,-1,1,360,null);
	jrib.Sphere(1,-1,1,360,null);
	jrib.SolidEnd();

	jrib.AttributeEnd();
    }

    private static void ProceduralAPIs() {
	String commands[] = {"myprog.exe"};
	float bounds[] = { 0,1,0,1,0,1 };
	//  jrib.Procedural(commands,bounds,jrib.PROCRUNPROGRAM,jrib.PROCFREE);
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
	jrib.AttributeBegin();
	jrib.Blobby(nleafs, ncode, code, nflt, flt, nstr, strings,null);
	jrib.AttributeEnd();
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
	ht.put(jrib.P,P);
	ht.put(jrib.CONSTANTWIDTH,width);
	jrib.AttributeBegin();
	jrib.Curves(jrib.CUBIC,1,nvertices,jrib.NONPERIODIC,ht);
	jrib.AttributeEnd();
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
	ht.put(jrib.P,P);
	ht.put(jrib.CONSTANTWIDTH,width);
	jrib.AttributeBegin();
	jrib.Points(totalPointCount,ht);
	jrib.AttributeEnd();
    }

    private static void ConicAPIs() {
	jrib.AttributeBegin();
	jrib.Sphere(1.0f,-1.0f,1.0f,360.0f,null);
	jrib.Cone(1.0f,1.0f,360.0f,null);
	jrib.Cylinder(1.0f,-1.0f,1.0f,360.0f,null);
	float point1[] = {0.0f,-0.5f,+0.5f};
	float point2[] = {1.0f,+1.0f,-0.5f};
	jrib.Hyperboloid(point1,point2,360.0f,null);
	jrib.Paraboloid(1.0f,-1.0f,1.0f,360.0f,null);
	jrib.Disk(0.1f,0.5f,360.0f,null);
	jrib.Torus(2.0f,0.1f,270.0f,360.0f,360.0f,null);
	jrib.AttributeEnd();
    }

    private static void SubdivMeshAPIs() {
	String scheme = jrib.CATMULLCLARK;
	int nfaces = 1;
	int nvertices[] = {4};
	int vertices[] = {0, 1, 2, 3};
	int ntags = 1;
	String tags[] = {jrib.INTERPOLATEBOUNDARY};
	int nargs[] = {0, 0};
	int intargs[] = {};
	float floatargs[] = {};
	float P[] = { -1.0f, 1.0f,0.0f,
		      +1.0f, 1.0f,0.0f,
		      +1.0f,-1.0f,0.0f,
		      -1.0f,-1.0f,0.0f};
	Hashtable ht = new Hashtable();
	ht.put(jrib.P,P);
	jrib.AttributeBegin();
	jrib.SubdivisionMesh(scheme,
			     nfaces,
			     nvertices,
			     vertices,
			     ntags,
			     tags,
			     nargs,
			     intargs,
			     floatargs,
			     ht);
	jrib.AttributeEnd();
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
	jrib.TrimCurve(nloops,ncurves,order,knot,min,max,n,u,v,w);
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
	ht.put(jrib.P,P);
	jrib.AttributeBegin();
	jrib.NuPatch(nu,uorder,uknot,umin,umax,
		     nv,vorder,vknot,vmin,vmax,ht);
	jrib.AttributeEnd();
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
	ht.put(jrib.P,P);
	jrib.AttributeBegin();
	jrib.Patch(jrib.BILINEAR,ht);
	jrib.PatchMesh(jrib.BILINEAR,
		       4, jrib.NONPERIODIC,
		       4, jrib.NONPERIODIC,ht);
	jrib.AttributeEnd();
    }

    private static void PolygonalAPIs() {
	jrib.AttributeBegin();
	float P[] = {-1.0f,  1.0f, 0.0f,
		      1.0f,  1.0f, 0.0f,
		      1.0f, -1.0f, 0.0f,
		     -1.0f, -1.0f, 0.0f};
	Hashtable ht = new Hashtable();
	ht.put(jrib.P,P);
	int npolys = 1;
	int nvertices = 4;
	int nvertices_a[] = {4};
	int vertices_a[] = {0,1,2,3};
	int nloops = 1;
	int nloops_a[] = {1};
	jrib.Polygon(nvertices,ht);
	jrib.GeneralPolygon(nloops,nvertices_a,ht);
	jrib.PointsPolygons(nloops,nvertices_a,vertices_a,ht);
	jrib.PointsGeneralPolygons(npolys,nloops_a,nvertices_a,vertices_a,ht);


	jrib.AttributeEnd();
    }

    public static void main(String arg[]) {
	System.out.println("jribtest START\n");
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
	    
	    // Use the following to trigger an exception in jrib
	    // Float singleFloat = new Float(1);
	    // ht.put(new String("singleFloat"),singleFloat);
	} else {
	    Float fv[] = new Float[3];
	    fv[0] = 27.5f;
	    fv[1] = 0.75f;
	    fv[2] = -1.75f;
	    ht.put(new String("fov"),fv);
	}
	ribclient.Begin("jrib.rib");
	jrib.FrameBegin(5);
	jrib.Projection(jrib.PERSPECTIVE,ht);
	jrib.Format(480,320,1.01f);
	jrib.FrameAspectRatio(1.02f);
	jrib.ScreenWindow(0.0f,1.0f,0.0f,1.0f);
	jrib.CropWindow(0.0f,1.0f,0.0f,1.0f);
	jrib.Clipping(0.1f,10000.0f);
	jrib.ClippingPlane(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	jrib.DepthOfField(8.0f, 200.0f, 50.0f);
	jrib.Shutter(0.1f, 0.9f);

	jrib.PixelVariance(0.2f);
	jrib.PixelSamples(4.0f,6.0f);
	jrib.PixelFilter(jrib.TRIANGLEFILTER,3.0f,3.0f);
	jrib.Exposure(1.0f,1.8f);
	jrib.Imager(jrib.BACKGROUND,ht);
	jrib.Quantize("box",1,1,256,1.0f);
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
	    jrib.DisplayChannel("varying point P",dcht);
	}
	jrib.Display("myimage.tif",jrib.FRAMEBUFFER,jrib.RGBA,ht);
	jrib.Hider(jrib.HIDDEN,null);
	float inRGB[] = {.3f,.3f,.4f};
	float outRGB[] = {1,1,1};
	// jrib.ColorSamples(1,inRGB,outRGB);
	jrib.RelativeDetail(3.141592654f);
	ht.clear();
	int endofframe[] = {1};
	ht.put(new String("int endofframe"),endofframe);
	jrib.Option("statistics",ht);
	jrib.WorldBegin();
	jrib.AttributeBegin();

	// Color samples > 3 needs to be tested and verified
	float mycolor[] = {0.5f,0.7f,0.1f,0.2f};
	jrib.Color(mycolor);
	float myopacity[] = {0.1f,0.9f,0.3f,0.6f};
	jrib.Opacity(myopacity);

	jrib.TextureCoordinates(0.1f,0.3f,0.5f,0.7f,0.9f,0.2f,0.4f,0.6f);

	int pointlightID = jrib.LightSource("pointlight",null);
	int arealightID = jrib.AreaLightSource("fluoro",null);

	jrib.Illuminate(pointlightID,false);
	jrib.Illuminate(arealightID,true);

	jrib.Surface("mysurface",null);
	jrib.Displacement("mydisplacement",null);
	jrib.Atmosphere("myatmosphere",null);
	jrib.Interior("myinterior",null);
	jrib.Exterior("myexterior",null);

	jrib.ShadingRate(0.1f);
	jrib.ShadingInterpolation(jrib.SMOOTH);
	jrib.Matte(false);
	
	jrib.AttributeEnd();
	float bounds[] = new float[6];
	bounds[0] = 0;
	bounds[1] = 5;
	bounds[2] = 0;
	bounds[3] = 2;
	bounds[4] = 0;
	bounds[5] = 7;
	jrib.Bound(bounds);

	jrib.Detail(bounds);
	jrib.DetailRange(0,0,10,20);
	jrib.GeometricApproximation(jrib.FLATNESS,2.4f);
	jrib.Orientation(jrib.RH);
	jrib.ReverseOrientation();
	jrib.Sides(2);
	jrib.Identity();

	jrib.Basis(jrib.CATMULLROMBASIS,1,jrib.POWERBASIS,4);
	float tx[][] = {{1,1,1,1},{2,2,2,2},{3,3,3,3},{4,4,4,4}};
	jrib.Transform(tx);

	jrib.ConcatTransform(tx);
	jrib.Perspective(4);
	jrib.Translate(1,2,3);
	jrib.Rotate(90,0,1,0);
	jrib.Scale(2,4,6);
	jrib.Skew(45, 0, 1, 0, 1, 0, 0);

	jrib.TransformBegin();
	jrib.CoordinateSystem(jrib.WORLD);
	/*
	int ribClientCompareResult = jrib.RIBCLIENT.compareTo("PRMan");
	System.out.println("ribClientCompareResult : " + ribClientCompareResult + "\n");
	if (ribClientCompareResult == 0) {
	    // jrib.ScopedCoordinateSystem(jrib.CAMERA);
	}
	*/
	jrib.CoordSysTransform(jrib.OBJECT);
	jrib.TransformEnd();

	// jrib.ResourceBegin();
	jrib.Resource("ecwserver","texture",null);
	ht.clear();
	float sphericalDB[] = {0.2f};
	ht.put(new String("uniform float sphere"),sphericalDB);
	jrib.Attribute("displacementbound",ht);
	// jrib.ResourceEnd();

	PolygonalAPIs();
	PatchAPIs();
	Nurbs();
	SubdivMeshAPIs();
	ConicAPIs();

	BlobbyAPIs();
	CurvesAPIs();
	PointsAPIs();
	
	ProceduralAPIs();

	jrib.Geometry("teapot",null);

	SolidAPIs();

	ObjectAPIs();

	MotionAPIs();

	MapTextureAPIs();

	jrib.ArchiveRecord(jrib.COMMENT,"dir");

	jrib.ReadArchive("nicholas.rib",0,null);

	jrib.ArchiveBegin("mysphere",null);
	jrib.Sphere(1,-1,1,360,null);
	jrib.ArchiveEnd();

	jrib.ReadArchive("mysphere",0,null);

	jrib.Declare("nicholas","uniform float");

	jrib.WorldEnd();
	jrib.FrameEnd();
	jrib.End();

	// System.out.println("jribtest RIBClient is from " + jrib.RIBCLIENT + "\n");
	System.out.println("jribtest FINISH\n");
    }
    
}
