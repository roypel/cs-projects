package il.ac.tau.cs.sw1.ex8.histogram;

import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;

/**************************************
 *  Add your code to this class !!!   *
 **************************************/
public class HashMapHistogram<T extends Comparable<T>> implements IHistogram<T>{

	private HashMap<T, Integer> histogram;

	public HashMapHistogram(){
		this.histogram = new HashMap<T,Integer>();
	}

	
	@Override
	public void addItem(T item) {
		if (this.histogram.containsKey(item))
			this.histogram.put(item, this.histogram.get(item) + 1);
		else
			this.histogram.put(item, 1);
	}

	@Override
	public void addItemKTimes(T item, int k) throws IllegalKValue {
		if (k < 0)
			throw new IllegalKValue(k);
		if (this.histogram.containsKey(item))
			this.histogram.put(item, this.histogram.get(item) + k);
		else
			this.histogram.put(item, k);
	}

	@Override
	public int getCountForItem(T item) {
		if (this.histogram.containsKey(item))
			return this.histogram.get(item);
		return 0; //Item wasn't seen
	}

	@Override
	public void addAll(Collection<T> items) {
		for (T item : items){
			if (this.histogram.containsKey(item))
				this.histogram.put(item, this.histogram.get(item) + 1);
			else
				this.histogram.put(item, 1);
		}
	}

	@Override
	public void clear() {
		this.histogram.clear();
	}

	@Override
	public Set<T> getItemsSet() {
		Set<T> itemsSet = new HashSet<T>(this.histogram.keySet());
		return itemsSet; //Make new object so collisions won't happen
	}

	@Override
	public Iterator<T> iterator() {
		return new HashMapHistogramIterator<T>(this.histogram);
	}
	
}
