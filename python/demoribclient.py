# Copyright Procedural Insight http://www.proceduralinsight.com
# Author : Nicholas Yue

import ribclient

ri = ribclient

ri.Option('rib',{'compression':['gzip']})

ri.Begin('demoribclient.rib')

ri.Option('rib',{'format':['binary']})

ri.FrameBegin(1)
ri.Format(640,480,1.0)

ri.Projection(ri.PERSPECTIVE,{ri.FOV:[27.0]})

ri.Display('demoribclient.tif',ri.FRAMEBUFFER,ri.RGBA,None)

ri.WorldBegin()
    
plh = ri.LightSource(ri.DISTANTLIGHT,{ri.INTENSITY:[2],ri.LIGHTCOLOR:[1,1,1]})

ri.AttributeBegin()
ri.Translate(0,0,10)
ri.Sphere(1,-1,1,360,None)
ri.AttributeEnd()

ri.WorldEnd()

ri.FrameEnd()
ri.End()
