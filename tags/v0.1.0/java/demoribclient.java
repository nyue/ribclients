import java.util.*;

public class demoribclient {
  //Load the library
  static {
    System.loadLibrary("ribclient");
  }
  
  public static void main(String arg[]) {

    Hashtable ht = new Hashtable();

    ht.clear();
    String compression[] = {"gzip"};
    ht.put(new String("compression"),compression);
    ribclient.Option("rib",ht);

    ribclient.Begin("demoribclient.rib");

    ht.clear();
    String format[] = {"binary"};
    ht.put(new String("format"),format);
    ribclient.Option("rib",ht);

    ribclient.FrameBegin(1);
    ribclient.Format(480,320,1.01f);

    ht.clear();
    Float fov[] = {27.0f};
    ht.put(ribclient.FOV,fov);
    ribclient.Projection(ribclient.PERSPECTIVE,ht);

    ribclient.Display("demoribclient.tif",ribclient.FRAMEBUFFER,ribclient.RGBA,null);

    ribclient.WorldBegin();

    ht.clear();
    Float intensity[] = {2.0f};
    ht.put(ribclient.INTENSITY,intensity);
    int distantlightID = ribclient.LightSource(ribclient.DISTANTLIGHT,ht);

    ribclient.AttributeBegin();
    ribclient.Translate(0,0,10);
    ribclient.Sphere(1,-1,1,360,null);
    ribclient.AttributeEnd();

    ribclient.WorldEnd();

    ribclient.FrameEnd();
    ribclient.End();
  }
}
