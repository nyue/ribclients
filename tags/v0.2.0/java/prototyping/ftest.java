import java.util.*;

public class ftest {
    //Load the library
    static {
        System.loadLibrary("functions");
    }
    
    public static void main(String arg[]) {
	System.out.println("ftest START\n");

	float f = 3.14159f;
	functions.SingleFloat(f);

	float fv[] = new float [3];
	fv[0] = 1.1f;
	fv[1] = 2.2f;
	fv[2] = 3.3f;
	functions.FloatVector(fv);

	Float Fm[][] = new Float [4][4];
	System.out.println("Fm is of type " + Fm.getClass().getName() + "\n");

	float fm[][] = new float [4][4];
	System.out.println("fm is of type " + fm.getClass().getName() + "\n");

	functions.FloatMatrix(fm);

	System.out.println("ftest FINISH\n");
    }
    
}
