package il.ac.tau.cs.sw1.ex8.histogram;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;

/**************************************
 * Add your code to this class !!! *
 **************************************/
public class HashMapHistogramIterator<T extends Comparable<T>> implements Iterator<T> {

	private ArrayList<T> orderedHistogram;
	private int pointer;

	public class HMHistogramComparator<T1 extends Comparable<T1>> implements Comparator<T1> {

		private HashMap<T1, Integer> histogram;

		public HMHistogramComparator(HashMap<T1, Integer> hM) {
			this.histogram = hM;
		}

		public int compare(T1 object1, T1 object2) {
			if (this.histogram.get(object1) != this.histogram.get(object2))
				return this.histogram.get(object2).compareTo(this.histogram.get(object1));// Return in descending order
			return object1.compareTo(object2);// object1 and object2 has same count in histogram, return by natural order
		}
	}

	public HashMapHistogramIterator(HashMap<T, Integer> hM) {
		this.orderedHistogram = new ArrayList<T>(hM.keySet());
		Collections.sort(this.orderedHistogram, new HMHistogramComparator<>(hM));// Use comparator for ordering 
		this.pointer = 0;
	}

	@Override
	public boolean hasNext() {
		if (this.pointer < this.orderedHistogram.size())
			return true;
		return false;
	}

	@Override
	public T next() {
		return this.orderedHistogram.get(pointer++);// Increment pointer
	}

	@Override
	public void remove() {
		throw new UnsupportedOperationException();
	}
}
