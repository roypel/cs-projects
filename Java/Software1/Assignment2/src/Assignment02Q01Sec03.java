
public class Assignment02Q01Sec03 {
	
	public static void main(String[] args){
		int count = 0, temp;
		
		for (int i = 0; i < args.length; i++){
			temp = Integer.parseInt(args[i]) % 6; //temp is the remainder of args[i] in 6
			
			if (temp % 2 ==0)
				count++;
		}
		
		System.out.println(count);
	}

}
