
public class Assignment02Q01Sec02 {
	
	public static void main (String[] args){
		int index = 0, max_val = 0, temp_val;
		String tempStr;
		
		for (int i = 0; i < args.length; i++){
			temp_val = 0;
			tempStr = args[i];
			
			for (int j = 0; j < tempStr.length(); j++){
				temp_val += tempStr.charAt(j);
			}
			
			if (temp_val >= max_val){
				index = i;
				max_val = temp_val;
			}
		}
		
		System.out.println(max_val+" " +args[index]);
		
	}

}
