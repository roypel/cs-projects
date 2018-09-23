
public class Assignment02Q02 {

	public static void main(String[] args) {
		double piEstimate = 0.0, denominator = 1.0;// .0 isn't necessary, just easier to read it's a double
		
		for(int i = 0; i < Integer.parseInt(args[0]); i++){
			piEstimate += (1/denominator) * (Math.pow(-1, i)); //calculating (1 - 1/3 + 1/5...)
			
			denominator += 2.0; // .0 isn't necessary, just a reminder that denominator is a double
		}
		piEstimate *= 4;
		
		System.out.println(piEstimate + " " + Math.PI);
	}

}
