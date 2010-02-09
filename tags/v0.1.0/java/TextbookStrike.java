import java.util.*;

public class TextbookStrike {
  //Load the library
  static {
    System.loadLibrary("ribclient");
  }

  private static void setupLights() {

    Hashtable ht = new Hashtable();

    float[] intensity = {0.1f};
    ht.put(ribclient.INTENSITY,intensity);
    ribclient.LightSource(ribclient.AMBIENTLIGHT,ht);

    float[] from = {0,0,0};
    float[] to = {0,0,1};
    float[] conedeltaangle = {0.1f};

    // increase intensity for spotlight
    intensity[0] = 5;
    ht.clear();
    ht.put(ribclient.INTENSITY,intensity);
    ht.put("uniform float conedeltaangle",conedeltaangle);

    ribclient.TransformBegin();

    ribclient.Translate(0,0,-2);

    ribclient.TransformBegin();
    ribclient.Translate(0,2,0);
    ribclient.LightSource(ribclient.SPOTLIGHT,ht);
    ribclient.TransformEnd();

    ribclient.TransformBegin();
    ribclient.Translate(0,0,0);
    ribclient.LightSource(ribclient.SPOTLIGHT,ht);
    ribclient.TransformEnd();

    ribclient.TransformBegin();
    ribclient.Translate(0,-2,0);
    ribclient.LightSource(ribclient.SPOTLIGHT,ht);
    ribclient.TransformEnd();

    ribclient.TransformEnd();
  }

  private static void setupView() {
    Hashtable ht = new Hashtable();
    float[] fov = {25};
    ht.put(ribclient.FOV,fov);
    ribclient.Projection(ribclient.PERSPECTIVE,ht);
    ribclient.Format(640,480,-1);
    ribclient.Translate(0,0,20);
  }

  private static void setupScene() {
    ribclient.Display("textbookstrike.tif",ribclient.FRAMEBUFFER,
		      ribclient.RGB,null);
    setupView();
  }

  private static void makeFloor(float[] where) {
    Hashtable ht = new Hashtable();
    float P[] = { -1.0f,  4.0f, 0.0f,
		  1.0f,  4.0f, 0.0f,
		  -1.0f, -4.0f, 0.0f,
		  1.0f, -4.0f, 0.0f};
    ribclient.AttributeBegin();
    ht.put(ribclient.P,P);
    ribclient.Surface(ribclient.PLASTIC,null);
    ribclient.Patch(ribclient.BILINEAR,ht);
    ribclient.AttributeEnd();
  }

  private static void makeBall(float[] where) {
  }

  private static void makePin(float[] where) {
  }

  private static void makeTenPins(float[] where) {
  }

  public static void main(String arg[]) {
    float[] location = {0,0,0};
    ribclient.Begin("textbookstrike.rib");
    setupScene();
    ribclient.WorldBegin();
    setupLights();
    makeFloor(location);
    makeBall(location);
    makeTenPins(location);
    ribclient.WorldEnd();
    ribclient.End();
  }
}
