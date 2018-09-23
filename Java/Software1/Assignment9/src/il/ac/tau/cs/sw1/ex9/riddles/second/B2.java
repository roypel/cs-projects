package il.ac.tau.cs.sw1.ex9.riddles.second;

public class B2 extends A2{
	
	private boolean randBool;
	
	public B2(){
		this.randBool = true;
	}
	
	public B2(boolean randBool){
		this.randBool = randBool;
	}
	
	public B2 getA(boolean bool){
		return new B2(bool);
	}
	
	public String foo(String str){
		if (this.randBool)
			return str.toUpperCase();
		return str.toLowerCase();
	}
}
