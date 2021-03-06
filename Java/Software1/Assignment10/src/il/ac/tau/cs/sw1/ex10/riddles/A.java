package il.ac.tau.cs.sw1.ex10.riddles;

import java.util.ArrayList;
import java.util.List;

public class A {

	private List<Object> lst;
	
	public A(int obj1, Object obj2) {
		this.lst = new ArrayList<>();
		this.lst.add(obj1);
		this.lst.add(obj2);
	}

	/*@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((lst == null) ? 0 : lst.get(1).getClass().hashCode());
		return result;
	}*/

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		A other = (A) obj;
		if (lst == null) {
			if (other.lst != null)
				return false;
		} else if (!lst.get(1).getClass().equals(other.lst.get(1).getClass()))
			return false;
		return true;
	}
}
