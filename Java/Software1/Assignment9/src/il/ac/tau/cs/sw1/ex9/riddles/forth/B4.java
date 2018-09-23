package il.ac.tau.cs.sw1.ex9.riddles.forth;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Iterator;

public class B4 implements Iterator<String>{
	
	private List<String> lst;
	private int place;
	
	public B4(String[] strings, int k){
		this.lst = new ArrayList<>();
		this.place = 0;
		for (int i = 0; i < k; i++){
			this.lst.addAll(Arrays.asList(strings));
		}
	}

	@Override
	public boolean hasNext() {
		if (this.place < this.lst.size())
			return true;
		return false;
	}

	@Override
	public String next() {
		return this.lst.get(place++);
	}
	
	
}
