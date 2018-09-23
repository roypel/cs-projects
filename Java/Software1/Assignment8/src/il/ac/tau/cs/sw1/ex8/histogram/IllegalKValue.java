package il.ac.tau.cs.sw1.ex8.histogram;

public class IllegalKValue extends Exception {

	private static final long serialVersionUID = 1L;

	public IllegalKValue(int k){
		super("Illegal k value: " + k);
	}
}
