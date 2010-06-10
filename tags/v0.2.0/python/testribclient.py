import ribclient

def BlobbyGeometries(r):
    nleafs = 2
    ncode = 8
    code = [
        # Definitions
        1001, 0,
        1001, 16,
        # Operations
        0, 2, 0, 1
        ]
    nflt = 32
    flt = [
        # Blob 0
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
        # Blob 1
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 1, 0, 1
        ]
    nstr = 0
    strings = None
    r.Blobby(nleafs, ncode, code, nflt, flt, nstr, strings,None)

def PointsGeometries(r,radius):
    import random
    sideSize = 3
    numPointsComp = 3
    points = []
    index = 0
    i = 0
    j = 0
    k = 0
    t = 0
    for i in range(sideSize):
        for j in range(sideSize):
            for k in range(sideSize):
                points.append( random.random() )
                points.append( random.random() )
                points.append( random.random() )
    totalPointCount = len(points) / 3;
    width = [radius]
    r.Points(totalPointCount,{r.P:points,r.CONSTANTWIDTH:width})

def SubdivisionMeshGeometries(r):
    scheme = r.CATMULLCLARK
    nfaces = 1
    nvertices = [4]
    vertices = [0, 1, 2, 3]
    ntags = 1
    tags = [r.INTERPOLATEBOUNDARY]
    nargs = [0, 0]
    intargs = []
    floatargs = []
    r.SubdivisionMesh(scheme,
                      nfaces,
                      nvertices,
                      vertices,
                      ntags,
                      tags,
                      nargs,
                      intargs,
                      floatargs,
                      {r.P:[ -1, 1,0,
                             1, 1,0,
                             1,-1,0,
                             -1,-1,0
                            ]})
    
def TrimCurves(r):
    nloops = 1
    ncurves = [1]
    order = [3]
    knot = [
        0.000000,0.000000,0.000000,
        0.142857,0.285714,0.428571,0.571429,0.714286,0.857143,
        1.000000,1.000000,1.000000
        ]
    min = [0]
    max = [4]
    n = [9]
    u = [0.9,0.9,0.9,0.1,0.1,0.1,0.9,0.9,0.9]
    v = [0.5,0.7,0.9,0.9,0.5,0.1,0.1,0.1,0.5]
    w = [1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0]
    r.TrimCurve(nloops,ncurves,order,knot,min,max,n,u,v,w)
        
def NURBSGeometries(r):
    nu = 7
    uorder = 4
    uknot = [0, 0, 0, 0, 0.25, 0.5, 0.75, 1, 1, 1, 1]
    umin = 0
    umax = 1
    nv = 9
    vorder = 4
    vknot = [0, 0, 0, 0, 0.166667, 0.333333, 0.5, 0.666667, 0.833333, 1, 1, 1, 1]
    vmin = 0
    vmax = 1
    points = [
        -0.5,      -0.5,      0,        1,
        -0.5,      -0.416667, 0,        1,
        -0.5,      -0.25,     0,        1,
        -0.5,       0,        0,        1,
        -0.5,       0.25,     0,        1,
        -0.5,       0.416667, 0,        1,
        -0.5,       0.5,      0,        1,
        
        -0.444444, -0.5,      0,        1,
        -0.444444, -0.416667, 0,        1,
        -0.444444, -0.25,     0,        1,
        -0.444444,  0,        0,        1,
        -0.444444,  0.25,     0,        1,
        -0.444444,  0.416667, 0,        1,
        -0.444444,  0.5,      0,        1,
        
        -0.333333, -0.5,      0,        1,
        -0.333333, -0.416667, 0,        1,
        -0.333333, -0.25,     0,        1,
        -0.333333,  0,        0,        1,
        -0.333333,  0.25,     0,        1,
        -0.333333,  0.416667, 0,        1,
        -0.333333,  0.5,      0,        1,
        
        -0.166667, -0.5,      0,        1,
        -0.166667, -0.416667, 0,        1,
        -0.166667, -0.25,     0.124372, 1,
        -0.166667,  0,        0.124372, 1,
        -0.166667,  0.25,     0.124372, 1,
        -0.166667,  0.416667, 0,        1,
        -0.166667,  0.5,      0,        1,
        
        0,        -0.5,      0,        1,
        0,        -0.416667, 0,        1,
        0,        -0.25,     0.124372, 1,
        0,         0,        1.07474,  1,
        0,         0.25,     0.124372, 1,
        0,         0.416667, 0,        1,
        0,         0.5,      0,        1,
        
        0.166667, -0.5,      0,        1,
        0.166667, -0.416667, 0,        1,
        0.166667, -0.25,     0.124372, 1,
        0.166667,  0,        0.124372, 1,
        0.166667,  0.25,     0.124372, 1,
        0.166667,  0.416667, 0,        1,
        0.166667,  0.5,      0,        1,
        
        0.333333, -0.5,      0,        1,
        0.333333, -0.416667, 0,        1,
        0.333333, -0.25,     0,        1,
        0.333333,  0,        0,        1,
        0.333333,  0.25,     0,        1,
        0.333333,  0.416667, 0,        1,
        0.333333,  0.5,      0,        1,
        
        0.444444, -0.5,      0,        1,
        0.444444, -0.416667, 0,        1,
        0.444444, -0.25,     0,        1,
        0.444444,  0,        0,        1,
        0.444444,  0.25,     0,        1,
        0.444444,  0.416667, 0,        1,
        0.444444,  0.5,      0,        1,
        
        0.5,      -0.5,      0,        1,
        0.5,      -0.416667, 0,        1,
        0.5,      -0.25,     0,        1,
        0.5,       0,        0,        1,
        0.5,       0.25,     0,        1,
        0.5,       0.416667, 0,        1,
        0.5,       0.5,      0,        1
        ]
    r.NuPatch(nu,uorder,uknot,umin,umax,
              nv,vorder,vknot,vmin,vmax,
              {r.PW:points})
    
ri = ribclient

ri.Begin('testribclient.rib')
ri.FrameBegin(1)
ri.Format(640,480,1.0)
ri.FrameAspectRatio(1.0)
ri.ScreenWindow(-1,-1,1,1)
ri.CropWindow(0,1,0,1)
ri.Projection(ri.PERSPECTIVE,{ri.FOV:[27.0]})
ri.Perspective(29)
ri.Clipping(0.2,1000.0)
ri.ClippingPlane(0,0,1,0,0,10)
ri.DepthOfField(8,50,80)
ri.Shutter(0,1)
ri.PixelVariance(0.1)
ri.PixelSamples(2.7,3.9)
ri.PixelFilter(ri.BOXFILTER,2,2)
ri.Exposure(1.0,1.0)
ri.Quantize(ri.RGBA,4095,0,65535,0.5)
ri.DisplayChannel(ri.Z,None)
ri.Display('myimage.tif',ri.FRAMEBUFFER,ri.RGBA,None)
ri.Imager(ri.BACKGROUND,{"uniform color bgcolor":[0.631373,0.631373,0.631373]})
ri.Hider(ri.HIDDEN,{"uniform int jitter":[1]})
# ri.ColorSamples(1,[1,1,1],[2,2,2])
ri.RelativeDetail(0.1)
ri.Option('limits',{'uniform int gridsize':[256]})
ri.WorldBegin()
ri.ArchiveRecord(ri.COMMENT,'my comments')
plh = ri.LightSource(ri.POINTLIGHT,{ri.INTENSITY:[2]})
alh = ri.AreaLightSource(ri.POINTLIGHT,{ri.INTENSITY:[2]})
ri.Illuminate(plh,True)
ri.Illuminate(alh,False)
ri.AttributeBegin()
ri.Attribute(ri.IDENTIFIER,{ri.NAME:['Nicholas']})
ri.Color([1,0,1])
ri.Opacity([1,0,1])
ri.TextureCoordinates(0,0,0,1,1,1,1,0)
ri.Surface(ri.PLASTIC,{ri.KD:[0.5]})
ri.Displacement(ri.PLASTIC,{ri.KD:[0.5]})
ri.Atmosphere(ri.PLASTIC,{ri.KD:[0.5]})
ri.Interior(ri.PLASTIC,{ri.KD:[0.5]})
ri.Exterior(ri.PLASTIC,{ri.KD:[0.5]})
ri.ShadingRate(1.5)
ri.ShadingInterpolation(ri.SMOOTH)
ri.Matte(False)
ri.Bound([0,0,0,1,1,1])
ri.Detail([0,0,0,1,1,1])
ri.DetailRange(0.1,10.0,1000.0,100000.0)
ri.GeometricApproximation(ri.MOTIONFACTOR,1.0)
ri.Orientation(ri.LH)
ri.ReverseOrientation()
ri.Sides(1)
ri.Identity()
ri.Transform([1,0,0,0,
              0,1,0,0,
              0,0,1,0,
              0,0,0,1])
ri.ConcatTransform([1,0,0,0,
                    0,1,0,0,
                    0,0,1,0,
                    0,0,0,1])
ri.Translate(1,2,3)
ri.Rotate(72,1,1,0)
ri.Scale(2,3,2)
ri.Skew(1,0,0,0,1,1,1)
ri.CoordinateSystem(ri.WORLD)
# ri.ScopedCoordinateSystem(ri.WORLD)
ri.CoordSysTransform(ri.OBJECT)
ri.TransformBegin()
#ri.ResourceBegin()
ri.Resource('resource.rib',ri.FILENAME,{'uniform string filename':['resource.rib']})
#ri.ResourceEnd()
ri.TransformEnd()
ri.Attribute('displacementbound',{'uniform float sphere':[0.5]})
ri.Polygon(4,{ri.P:[-1.0,  1.0, 0.0, # v0
                    1.0,  1.0, 0.0,  # v1
                    1.0, -1.0, 0.0,  # v3
                    -1.0, -1.0, 0.0  # v2
                    ]})
ri.GeneralPolygon(1,[4],{ri.P:[ -1.0,  1.0, 0.0, # v0
                                1.0,  1.0, 0.0,  # v1
                                1.0, -1.0, 0.0,  # v3
                                -1.0, -1.0, 0.0  # v2
                                ]})
ri.PointsPolygons(1,[4],[0,1,2,3],
                  {ri.P:[ -1.0,  1.0, 0.0, # v0
                          1.0,  1.0, 0.0,  # v1
                          1.0, -1.0, 0.0,  # v3
                          -1.0, -1.0, 0.0  # v2
                          ]})
ri.PointsGeneralPolygons(1,[1],[4],[0,1,2,3],
                         {ri.P:[ -1.0,  1.0, 0.0, # v0
                                 1.0,  1.0, 0.0,  # v1
                                 1.0, -1.0, 0.0,  # v2
                                 -1.0, -1.0, 0.0  # v3
                                 ]})
ri.Basis(ri.BSPLINEBASIS,3,ri.BEZIERBASIS,3)
points = [ -1.0,  1.0, 0.0, # v0
           1.0,  1.0, 0.0, # v1
           -1.0, -1.0, 0.0, # v2
           1.0, -1.0, 0.0  # v3
           ]
ri.Patch(ri.BILINEAR,{ri.P:points})
patchmeshpoints = [
    -3.0,  3.0, 0.0, # v00
    -2.0,  3.0, 1.0, # v00
    -1.0,  3.0, 0.0, # v00
    -0.0,  3.0, 1.0, # v00
    +1.0,  3.0, 0.0, # v00
    +2.0,  3.0, 1.0, # v00
    +3.0,  3.0, 0.0, # v00
    
    -3.0,  2.0, 1.0, # v00
    -2.0,  2.0, 0.0, # v00
    -1.0,  2.0, 1.0, # v00
    -0.0,  2.0, 0.0, # v00
    +1.0,  2.0, 1.0, # v00
    +2.0,  2.0, 0.0, # v00
    +3.0,  2.0, 1.0, # v00
    
    -3.0,  1.0, 0.0, # v00
    -2.0,  1.0, 1.0, # v00
    -1.0,  1.0, 0.0, # v00
    -0.0,  1.0, 1.0, # v00
    +1.0,  1.0, 0.0, # v00
    +2.0,  1.0, 1.0, # v00
    +3.0,  1.0, 0.0, # v00
    
    -3.0,  0.0, 1.0, # v00
    -2.0,  0.0, 0.0, # v00
    -1.0,  0.0, 1.0, # v00
    -0.0,  0.0, 0.0, # v00
    +1.0,  0.0, 1.0, # v00
    +2.0,  0.0, 0.0, # v00
    +3.0,  0.0, 1.0, # v00
    ]
ri.PatchMesh(ri.BICUBIC, 7, ri.NONPERIODIC, 4, ri.NONPERIODIC,
             {ri.P:patchmeshpoints})
ri.AttributeEnd()
ri.AttributeBegin()
TrimCurves(ri)
NURBSGeometries(ri)
SubdivisionMeshGeometries(ri)
ri.Sphere(1,-1,1,360,None)
ri.Cone(1,1,360,None)
ri.Cylinder(1,-1,1,360,None)
point1 = [0,-0.5,0.5]
point2 = [1,1,-0.5]
ri.Hyperboloid(point1,point2,360,None)
ri.Paraboloid(1,-1,1,360,None)
ri.Disk(0.1,0.5,360,None)
ri.Torus(2,0.1,270,360,360,None)
ri.AttributeEnd()
ri.AttributeBegin()
PointsGeometries(ri,0.1)
ri.Curves(ri.CUBIC,1,[4],ri.NONPERIODIC,{ri.P:[0,0,0,
                                               1,1,1,
                                               1,1,0,
                                               2,1,1,
                                               1,2,1],
                                         ri.CONSTANTWIDTH:[0.1]})

ri.AttributeEnd()
ri.AttributeBegin()
BlobbyGeometries(ri)
ri.Geometry('teapot',None)
ri.AttributeEnd()
ri.AttributeBegin()
oh = ri.ObjectBegin()
ri.SolidBegin(ri.DIFFERENCE)
ri.Sphere(1,-1,1,360,None)
ri.Sphere(2,-2,2,360,None)
ri.SolidEnd()
ri.ObjectEnd()
ri.ObjectInstance(oh)
ri.AttributeEnd()
ri.MotionBegin(2,[0,0.5])
ri.MotionEnd()
ri.WorldEnd()
ri.FrameEnd()
ri.End()
