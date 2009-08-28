import java.util.*;

public class smalltest {
  //Load the library
  static {
    System.loadLibrary("ribclient");
  }
  
  public static void main(String arg[]) {
    ribclient.Begin("smalltest.rib");
    ribclient.End();
    
  }
  
}
