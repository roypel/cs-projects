package il.ac.tau.cs.sw1.ex10.riddles;

import java.util.ArrayList;
import java.util.List;

public class C implements Comparable<C>{

	private List<Object> lst;
	
	public C(int obj1, Object obj2) {
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
		C other = (C) obj;
		if (lst == null) {
			if (other.lst != null)
				return false;
		} else if (!lst.get(1).getClass().equals(other.lst.get(1).getClass()))
			return false;
		return true;
	}
	
	public int compareTo(C other){
		return this.lst.get(1).getClass().toString().compareTo(other.lst.get(1).getClass().toString());
	}
}
