package il.ac.tau.cs.sw1.ex9.riddles.third;

public class B3 extends A3{	
	
	public B3(String str){
		super(str);
	}
	
	public String getMessage(){
		return s;
	}
	
	public void foo(String str) throws Exception{
		throw new B3 (str);
	}
}