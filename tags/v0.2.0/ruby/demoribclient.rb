require 'ribclient'

r = Ribclient


filename = "demoribclient.rib"
display = "demoribclient.tif"
eocdisplay = "+eoc.tif"

r.Option("rib",{"compression"=>["gzip"]})

r.Begin(filename)

r.Option("rib",{"format"=>["binary"]})

r.FrameBegin(1)
r.Format(640,480,1.0)

r.Projection(Ribclient::PERSPECTIVE,{Ribclient::FOV=>[27]})

r.Display(display,Ribclient::FRAMEBUFFER,Ribclient::RGBA,nil)

r.WorldBegin

lhd = r.LightSource(Ribclient::DISTANTLIGHT,{Ribclient::INTENSITY=>[2.0]})

r.AttributeBegin
r.Translate(0,0,10)
r.Sphere(1,-1,1,360,nil)
r.AttributeEnd

r.WorldEnd

r.FrameEnd

r.End
