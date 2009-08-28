import java.util.*;

class TestProto {

    //Load the library
    static {
	System.loadLibrary("RIBClient");
    }

    public static void main(String args[]) {

	System.out.print("Testing Java prototyping code\n");

	RIBClient rc = new RIBClient();
	// Integer
	rc.ProtoIntParam(1000);
	rc.ProtoIntParam(1);
	rc.ProtoIntParam(0);
	rc.ProtoIntParam(-1);
	rc.ProtoIntParam(-1000);
	// Float
	rc.ProtoFloatParam(1000.123f);
	rc.ProtoFloatParam(1.415f);
	rc.ProtoFloatParam(0.987f);
	rc.ProtoFloatParam(-1.7618f);
	rc.ProtoFloatParam(-1000.761f);
	// Double
	rc.ProtoDoubleParam(2000.123);
	rc.ProtoDoubleParam(2.415);
	rc.ProtoDoubleParam(0.2987);
	rc.ProtoDoubleParam(-2.7618);
	rc.ProtoDoubleParam(-2000.761);
	// String
	rc.ProtoStringParam("");
	rc.ProtoStringParam("abc");
	rc.ProtoStringParam("abcdefghijklmnopqrstuvwxyz");
	// array
	int ia[] = new int[5];
	float fa[] = new float[5];
	double da[] = new double[5];
	rc.ProtoIntArrayParam(ia);
	rc.ProtoFloatArrayParam(fa);
	rc.ProtoDoubleArrayParam(da);
	Hashtable params = new Hashtable();
	Float points[] = new Float[3];
	points[0] = 0.0f;
	points[1] = 0.0f;
	points[2] = 0.0f;
	params.put("P", points);
	/*
	  params.put("Kd",  new int[5]);
	  params.put("Ks",  new int[5]);
	  params.put("Ka",  new int[5]);
	*/
	rc.ProtoObjectParam(params);
    }
}
