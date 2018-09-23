package il.ac.tau.cs.sw1.ex10.riddles;

import java.util.ArrayList;
import java.util.List;

public class D implements Comparable<D>{

	private List<Object> lst;
	
	public D(int obj1, Object obj2) {
		this.lst = new ArrayList<>();
		this.lst.add(obj1);
		this.lst.add(obj2);
	}



	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		D other = (D) obj;
		if (lst == null) {
			if (other.lst != null)
				return false;
		} else if (!lst.get(0).equals(other.lst.get(0)))
			return false;
		return true;
	}
	
	public int compareTo(D other){
		return this.lst.get(0).getClass().toString().compareTo(other.lst.get(0).getClass().toString());
	}
}
