import java.util.*;
import java.lang.reflect.Array;

class LangTut {


    public void TestHashtable() {
	Hashtable ht = new Hashtable();
	try {
	    // Put something into the has table
	    Float Ka[] = new Float[1];
	    Ka[0] = 0.5f;
	    Float from[] = new Float[3];
	    from[0] = 0.2f;
	    from[1] = 0.4f;
	    from[2] = 0.6f;
	    Float to[] = new Float[3];
	    to[0] = 0.3f;
	    to[1] = 0.6f;
	    to[2] = 0.9f;
	    ht.put(new String("Ka"),Ka);
	    ht.put(new String("from"),from);
	    ht.put(new String("to"),to);
	    int i = ht.size();
	    System.out.println("Number of items " + i);
	    
	    // Iterate
	    String key;
	    Float   fa[];
	    Integer ia[];
	    String  sa[];
	    for (Enumeration e = ht.keys(); e.hasMoreElements();) {
		key = (String)e.nextElement();
		fa = (Float[])ht.get( key );
		System.out.println (key);
		int numElements = Array.getLength(fa);
		System.out.println ("value array has length " + numElements);
	    }
	}
	catch (Exception e) {
	    System.err.println(e.toString());
	}
    }

    public static void main(String args[]) {

	System.out.print("Java Language tutorial\n");
	LangTut lt = new LangTut();
	lt.TestHashtable();
    }
}
