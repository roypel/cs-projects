
public class Assignment02Q01Sec01 {

	public static void main(String[] args) {
		char c;

		for (int i = 0; i < args.length; i++) {
			c = args[i].charAt(0);

			if (c % 2 == 0) {
				System.out.println(c);
			}
		}
	}

}
