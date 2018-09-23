package il.ac.tau.cs.sw1.ex10.riddles;

import java.util.HashSet;
import java.util.Set;
import java.util.TreeSet;


public class Main {
	
	
     final static int DIFFERENTIATED  = 2;
     final static int UNDIFFERENTIATED = 1;
     final static int ALL_DIFFERENTIATED = 3;
	
	public static void main(String[] args){
		Set<A> set1 = new HashSet<A>();
		set1.add(new A(1,2));
		set1.add(new A(1,"2"));
		set1.add(new A(1,50));
		int num1 = set1.size();
		System.out.println(num1);
		
		
		Set<B> set2 = new HashSet<B>();
		set2.add(new B(1,2));
		set2.add(new B(1,"2"));
		set2.add(new B(1,50));
		int num2 = set2.size();
		System.out.println(num2);
		
		
		Set<C> set3 = new TreeSet<C>();
		set3.add(new C(1,2));
		set3.add(new C(1,"2"));
		set3.add(new C(1,50));
		int num3 = set3.size();
		System.out.println(num3);
		
		
		Set<D> set4 = new TreeSet<D>();
		set4.add(new D(1,2));
		set4.add(new D(1,"2"));
		set4.add(new D(1,50));
		int num4 = set4.size();
		System.out.println(num4);
		
		
		Set<E> set5 = new HashSet<E>();
		set5.add(new E(1,2));
		set5.add(new E(1,"2"));
		set5.add(new E(1,50));
		int num5 = set5.size();
		System.out.println(num5);
		
		
		Set<F> set6 = new TreeSet<F>();
		set6.add(new F(1,2));
		set6.add(new F(1,"2"));
		set6.add(new F(1,50));
		int num6 = set6.size();
		System.out.println(num6);
	
	
		
		if(num1 == DIFFERENTIATED  && num2 == UNDIFFERENTIATED  && num3 == DIFFERENTIATED  && num4 == UNDIFFERENTIATED && num5 == ALL_DIFFERENTIATED && num6 == ALL_DIFFERENTIATED )
			System.out.println("success!");
	}
}
