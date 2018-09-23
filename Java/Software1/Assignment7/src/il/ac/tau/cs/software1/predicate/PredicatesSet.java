package il.ac.tau.cs.software1.predicate;

import java.util.List;

public interface PredicatesSet<T> {
	
	/*
	 *  Remove every object, obj, for which pred.test(obj) is true.
	 */
	public void remove(Predictor pred);
	
	/*
	 * Remove every object, obj, 
	 * for which pred.test(obj) is false.  
	 * (That is, retain the objects for which the predicate is true.)
	 */
	public void retain(Predictor pred);
	
	/*
	 * Return a List that contains all the objects, obj,
	 *  such that pred.test(obj) is true.
	 */
	public List<T> collect(Predictor pred);
	
	/*
	 * Return the index of the first item in the list 
	 * for which the predicate is true, if any. 
	 * If there is no such item, return -1.
	 */
	public int find(Predictor pred);

}
