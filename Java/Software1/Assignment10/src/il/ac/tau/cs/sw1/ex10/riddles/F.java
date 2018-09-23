package il.ac.tau.cs.sw1.ex10.riddles;

import java.util.ArrayList;
import java.util.List;

public class F implements Comparable<F>{

	private List<Object> lst;
	
	public F(int obj1, Object obj2) {
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
		F other = (F) obj;
		if (lst == null) {
			if (other.lst != null)
				return false;
		} else if (!lst.equals(other.lst))
			return false;
		return true;
	}

	public int compareTo(F other){
		if (this.lst.get(1) instanceof String)
			return 1;
		if (other.lst.get(1) instanceof Integer)
			return Integer.compare((Integer)this.lst.get(1), (Integer)other.lst.get(1));
		return -1;
	}
}
