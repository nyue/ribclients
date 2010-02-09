require 'ribclient'

def CurvesGeometries(r)
  def VectorAdd(u,v)
    vec = []
    for i in 0..2
      vec[i] = u[i] + v[i]
    end
    return vec
  end
  def VectorScale(v,s)
    vec = []
    for i in 0..2
      vec[i] = s * v[i]
    end
    return vec
  end
  def SingleStrand(r,base,direction,numSegments,overallLength,width)
    vertices = []
    segmentLength = overallLength / numSegments
    vertices[0] = base
    for i in 1..numSegments
      vertices[i] = VectorAdd(vertices[i-1], VectorScale(VectorScale(direction,rand),segmentLength))
    end
    pointIndex = 0
    points = []
    for i in 0..numSegments
      points[pointIndex] = vertices[i][0]
      pointIndex += 1
      points[pointIndex] = vertices[i][1]
      pointIndex += 1
      points[pointIndex] = vertices[i][2]
      pointIndex += 1
    end
    r.Curves(Ribclient::CUBIC,1,[numSegments+1],Ribclient::NONPERIODIC,[Ribclient::P,points,Ribclient::CONSTANTWIDTH,[width]])
  end
  sideSize = 4
  hairRoot = []
  hairNormal = []
  hairWidth = 0.01
  hairLength = 1.05
  numSegments = 7
  index = 0
  srand(12345)
  for i in 1..sideSize
    for j in 1..sideSize
      for k in 1..sideSize
        hairRoot[0] = rand
        hairRoot[1] = rand
        hairRoot[2] = rand
        hairNormal[0] = rand
        hairNormal[1] = rand
        hairNormal[2] = rand
        SingleStrand(r,hairRoot,hairNormal,numSegments,hairLength,hairWidth)
      end
    end
  end
  totalHairCount = sideSize * sideSize * sideSize;
end

def PointsGeometries(r,radius)
  sideSize = 10
  points = []
  index = 0
  srand(12345)
  for i in 1..sideSize
    for j in 1..sideSize
      for k in 1..sideSize
        points[index] = rand
        index = index + 1
        points[index] = rand
        index = index + 1
        points[index] = rand
        index = index + 1
      end
    end
  end
  totalPointCount = sideSize * sideSize * sideSize;
  width = [radius]
  r.Points(totalPointCount,[Ribclient::P,points,Ribclient::CONSTANTWIDTH,width])
end

def QuadricGeometries(r)
  radius = 1
  zmin = -1
  zmax = 1
  thetamax = 360
  height = 1
  point1 = [0,-0.5,0.5]
  point2 = [1,1,-0.5]
  rmax = 0.5
  majorradius = 1
  minorradius = 0.3
  phimin = 10
  phimax = 300
  # =================================
  # sphere
  # =================================
  r.AttributeBegin
  r.Translate(-2,2,2)
  r.Sphere(radius,zmin,zmax,thetamax,nil)
  r.AttributeEnd
  # =================================
  # cone
  # =================================
  r.AttributeBegin
  r.Translate(-2,0,2)
  r.Rotate(-90,1,0,0) # Needed because cone pointy end is z-facing
  r.Cone(height,radius,thetamax,nil)
  r.AttributeEnd
  # =================================
  # hyperboloid
  # =================================
  r.AttributeBegin
  r.Translate(-2,-2,2)
  r.Rotate(-90,1,0,0) # Need to investigate more
  r.Hyperboloid(point1,point2,thetamax,nil)
  r.AttributeEnd
  # =================================
  # cylinder
  # =================================
  r.AttributeBegin
  r.Translate(0,0,2)
  r.Rotate(-90,1,0,0) # Needed because cylinder is z-facing
  r.Cylinder(radius*0.4,zmin*2,zmax*2,thetamax,nil)
  r.AttributeEnd
  # =================================
  # paraboloid
  # =================================
  r.AttributeBegin
  r.Translate(1,1,1)
  r.Rotate(-90,1,0,0) # Need to investigate more
  r.Paraboloid(rmax,-zmin*0.2,zmax*0.7,thetamax*0.75,nil)
  r.AttributeEnd
  # =================================
  # disk
  # =================================
  r.AttributeBegin
  r.Translate(1,0,1)
  r.Rotate(-140,1,0,0) # Disk is z-facing
  r.Disk(height*0.1,radius*0.5,thetamax,nil)
  r.AttributeEnd
  # =================================
  # torus
  # =================================
  r.AttributeBegin
  r.Translate(1,-1,1)
  r.Rotate(-140,1,0,0) # Disk is z-facing
  r.Torus(majorradius,minorradius,phimin,phimax,thetamax,nil)
  r.AttributeEnd
end

def BlobbyGeometries(r)
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
  str = []
  r.Blobby(nleafs, ncode, code, nflt, flt, nstr, str,nil)

end

def TrimCurves(r)
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

end

def SubdivisionMeshGeometries(r)
  scheme = Ribclient::CATMULLCLARK
  nfaces = 1
  nvertices = [4]
  vertices = [0, 1, 2, 3]
  ntags = 1
  tags = [Ribclient::INTERPOLATEBOUNDARY]
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
                    [Ribclient::P,[
                             -1, 1,0,
                              1, 1,0,
                              1,-1,0,
                             -1,-1,0
                            ]])
end

def NURBSGeometries(r)
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
            [Ribclient::PW,points])
end

def PolygonalGeometries(r, isType)

  r.TextureCoordinates(0,0,2,0,2,2,0,2) # Suitable for polygons
  st = [0,0,0,1,1,1,1,0]
  case isType
  when 0 then
    r.Polygon(4,{Ribclient::P=>[
                                -1.0,  1.0, 0.0, # v0
                                1.0,  1.0, 0.0,  # v1
                                1.0, -1.0, 0.0,  # v3
                                -1.0, -1.0, 0.0  # v2
                               ],
                Ribclient::ST=>st})
  when 1 then
    r.GeneralPolygon(1,[4],[Ribclient::P,[
                                    -1.0,  1.0, 0.0, # v0
                                    1.0,  1.0, 0.0,  # v1
                                    1.0, -1.0, 0.0,  # v3
                                    -1.0, -1.0, 0.0  # v2
                                   ]])
  when 2 then
    r.PointsPolygons(1,[4],[0,1,2,3],
                     [Ribclient::P,[
                              -1.0,  1.0, 0.0, # v0
                              1.0,  1.0, 0.0,  # v1
                              1.0, -1.0, 0.0,  # v3
                              -1.0, -1.0, 0.0  # v2
                             ]])
  when 3 then
    r.PointsGeneralPolygons(1,[1],[4],[0,1,2,3],
                            [Ribclient::P,[
                                     -1.0,  1.0, 0.0, # v0
                                     1.0,  1.0, 0.0,  # v1
                                     1.0, -1.0, 0.0,  # v2
                                     -1.0, -1.0, 0.0  # v3
                                    ]])
  end
end

def PatchGeometries(r, isBiCubic, isMesh)

  r.Basis(Ribclient::BSPLINEBASIS,3,Ribclient::BEZIERBASIS,3)

  
  if (isBiCubic)
    #r.TextureCoordinates(0,0,2,0,0,2,2,2) # Suitable for patch
    points = [
              1.0,1.0,0.0,
              0.333333333,1.0,0.0,
              -0.33333333,1.0,0.0,
              -1.0,1.0,0.0,
              1.0,0.333333333,0.0,
              0.333333333,0.333333333,0.0,
              -0.33333333,0.333333333,0.0,
              -1.0,0.333333333,0.0,
              1.0,-0.33333333,0.0,
              0.333333333,-0.33333333,0.0,
              -0.33333333,-0.33333333,0.0,
              -1.0,-0.33333333,0.0,
              1.0,-1.0,0.0,
              0.333333333,-1.0,0.0,
              -0.33333333,-1.0,0.0,
              -1.0,-1.0,0.0
             ]
  else
    r.TextureCoordinates(0,0,2,0,0,2,2,2) # Suitable for bilinear patch
    points = [
              -1.0,  1.0, 0.0, # v0
              1.0,  1.0, 0.0, # v1
              -1.0, -1.0, 0.0, # v2
              1.0, -1.0, 0.0  # v3
             ]
  end

  if (isMesh)
    if (isBiCubic)
      r.PatchMesh(Ribclient::BICUBIC, 4, Ribclient::NONPERIODIC, 4, Ribclient::NONPERIODIC,
                  [Ribclient::P,points])
    else
      r.PatchMesh(Ribclient::BILINEAR, 2, Ribclient::NONPERIODIC, 2, Ribclient::NONPERIODIC,
                  [Ribclient::P,points])
    end
  else
    r.Patch(patch_type,[Ribclient::P,points])
  end

end

r = Ribclient

filename = "nicholas.rib"
display = "nicholas.tif"
eocdisplay = "+eoc.tif"
r.Begin(filename)
# Display options
# r.DisplayChannel("varying normal N",nil)
r.Display(display,Ribclient::FRAMEBUFFER,Ribclient::RGBA,nil)
# r.Display(eocdisplay,Ribclient::FRAMEBUFFER,Ribclient::N,[Ribclient::QUANTIZE,[0,255,0,255]])
r.Format(600,600,1)
# Camera options
r.ArchiveRecord(Ribclient::COMMENT,"Camera options")
#r.Orientation(Ribclient::LH)
#r.ReverseOrientation()
# r.Sides(1)
#r.Identity()
#r.Transform([1,0,0,0,
#             0,1,0,0,
#             0,0,1,0,
#             0,0,0,1])
#r.ConcatTransform([1,0,0,0,
#                   0,1,0,0,
#                   0,0,1,0,
#                   0,0,0,1])
r.Projection(Ribclient::PERSPECTIVE,{Ribclient::FOV=>[25]})
# r.Perspective(27)
# r.PixelSamples(4,4)
r.PixelFilter(Ribclient::BOXFILTER,2,2)
r.ShadingInterpolation(Ribclient::SMOOTH)
r.ScreenWindow(-1,1,-1,1)
r.CropWindow(0,1,0,1)
r.FrameAspectRatio(1.0)
r.Clipping(0.1,100)
r.ClippingPlane(0.2,0,0,0,0,-1)
r.Shutter(0,1)
# r.PixelVariance(1.0/255.0) # Working but 3Delight does not support the test
# r.DepthOfField(8,35,60) # Working but commented out for faster render test
r.Exposure(1,1)
r.Hider(Ribclient::HIDDEN,nil)
#r.Imager(Ribclient::BACKGROUND,["uniform color bgcolor",[1,1,0]])
# r.ColorSamples(1,[0.3,0.3,0.4],[1,1,1]) # not supported in 3Delight 
#r.Quantize(Ribclient::RGBA,255,0,255,0.5)
#r.RelativeDetail(1)
r.Option("user",{"float particleId"=>[1]})
r.ShadingRate(2.0)
r.ShadingInterpolation(Ribclient::SMOOTH)
# r.Matte(1)
# r.Bound([1,2,3,4,5,6])
r.GeometricApproximation(Ribclient::FLATNESS,2.5)

# Camera placement translation
r.FrameBegin(100)

r.WorldBegin
lha = r.LightSource(Ribclient::AMBIENTLIGHT,{Ribclient::INTENSITY=>[0.1]})
lhd = r.LightSource(Ribclient::DISTANTLIGHT,{Ribclient::INTENSITY=>[1.0]})
# lha = r.AreaLightSource(Ribclient::SPOTLIGHT,[Ribclient::INTENSITY,[1.0]])
# lhs = r.LightSource(Ribclient::SPOTLIGHT,[Ribclient::INTENSITY,[100],Ribclient::FROM,[1,1,-5],"uniform float blur",[0.001]])
r.AttributeBegin
r.Illuminate(lha,0)
# r.Color([1,0,1])
# r.Opacity([0.5,0,0.7])
# r.MakeTexture('grid.tif','grid.tx',
#              Ribclient::PERIODIC,Ribclient::PERIODIC,
#              'triangle',1.0,1.0,nil)
r.Surface(Ribclient::PLASTIC,nil)
# r.Surface(Ribclient::PAINTEDPLASTIC,[Ribclient::TEXTURENAME,["grid.tx"]])
# r.Surface('LGParquetPlank',nil)
# r.Displacement("IDbubbly",nil)
r.TransformBegin
# r.DetailRange(0,1,7,2)
#r.Detail([1,2,3,4,5,6])
r.Translate(0,0,1)
# r.Rotate(45,0,0,1)
# r.TextureCoordinates(0,0,2,0,0,2,2,2)
# r.Patch(Ribclient::BILINEAR,[Ribclient::P,[-1,1,0.0,1,1.0,0,-1.0,-1,0,1,-1,0],Ribclient::N,[-1,1,0.0,1,1.0,0,-1.0,-1,0,1,-1,0]])

r.AttributeBegin
r.Translate(0,+2,20)
# PatchGeometries(r, true, true)
r.AttributeEnd

r.AttributeBegin
r.Translate(0,0,2)
# SubdivisionMeshGeometries(r)
r.AttributeEnd

r.AttributeBegin
r.Translate(0,0,2)
r.Rotate(-150,1,0,0)
# TrimCurves(r)
# NURBSGeometries(r)
r.AttributeEnd

r.AttributeBegin
r.Translate(0,0,10)
# BlobbyGeometries(r)
r.AttributeEnd

r.AttributeBegin
r.Translate(0,0,10)
# QuadricGeometries(r)
r.AttributeEnd

r.AttributeBegin
r.Translate(-0.5,-0.5,2)
# PointsGeometries(r,0.02)
r.AttributeEnd

r.AttributeBegin
r.Translate(-1.5,-1.5,5)
# CurvesGeometries(r)
r.AttributeEnd

r.AttributeBegin
r.Translate(0,0,5)
PolygonalGeometries(r,0)
r.AttributeEnd

r.TransformEnd
r.AttributeEnd
r.WorldEnd

r.FrameEnd

r.End
