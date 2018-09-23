
public class Assignment02Q05 {
	public static void main(String[] args) {
		int size = 6; // size of the board
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if ((i + j) % 2 == 0) {
					System.out.print("w ");
				} else {
					System.out.print("b ");
				}
			}
			System.out.println();
		}
	}

}
