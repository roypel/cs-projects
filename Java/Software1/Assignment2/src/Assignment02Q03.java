
public class Assignment02Q03 {

	public static void main(String[] args) {
		int num1 = 1, num2 = 1, nextFib;
		double sum = 2.0;

		System.out.println("The first " + args[0] + " Fibonacci numbers are:");
		for (int i = 0; i < Integer.parseInt(args[0]) - 2; i++) {
			nextFib = num1 + num2;
			sum += nextFib;
			num1 = num2;
			num2 = nextFib;
			System.out.print(nextFib + " ");
		}

		System.out.println("");
		System.out.println("The average is: " + sum / Integer.parseInt(args[0]));

	}

}
