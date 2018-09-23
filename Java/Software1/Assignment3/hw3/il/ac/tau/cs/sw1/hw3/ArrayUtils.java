package il.ac.tau.cs.sw1.hw3;

public class ArrayUtils {

	public static int[] reverseArray(int[] array) {
		int temp;
		for (int i = 0; i < array.length / 2; i++) {
			temp = array[i];
			array[i] = array[array.length - i - 1];
			array[array.length - i - 1] = temp;
		}
		return array;
	}

	public static int[] shiftArrayToTheRightCyclic(int[] array, int move) {
		if ((move < 0) || (array.length == 0))
			return array;
		int temp1 = array[0], temp2; // temporary variables so we won't lose data
		int count = 0; // check if we covered all the array
		int point = move; // pointing to the next place to change
		while (count < array.length) {
			while (point >= array.length)
				point -= array.length;
			temp2 = array[point];
			array[point] = temp1;
			temp1 = temp2;
			point += move;
			count++;
		}
		return array;
	}

	public static int alternateSum(int[] array) {		if (array.length == 0)
		return 0;
	int temp = array[0] - array[1];// Initialize with first iteration
	int max = temp;
	int firstIndex = 0;// Marker of our current "tail of the snake"
	int flag = 1;// In case we started from an odd index, we need to calculate differently
	int i = 2;
	for (; i < array.length; i++) {
		if (i % 2 == 0) {// The first part is just adding or subtracting the next index
			temp += array[i] * flag;
		} else {
			temp -= array[i] * flag;
		}
		if ((temp - array[firstIndex]) * (-1) > temp) {// If it's better to "cut the tail", do it!
			temp = (temp - array[firstIndex]) * (-1);
			firstIndex++;
			flag *= (-1);
		}
		if ((array[firstIndex] == 0) && (array.length - firstIndex > 2)) {// If we begin with a zero, we might prefer to cut a bigger portion of the tail!
			if (temp + array[firstIndex + 1] > temp)
				temp += array[firstIndex + 1];
			firstIndex += 2;
		}
		if (max < temp)
			max = temp;
	}
	return max;
	}

	public static int findNeighbours(int[][] m, int[] row, int[] neighbours, int destination) {
		if (neighbours[destination] == 1)// Stop condition: we are linked to the destination
			return 1;
		for (int i = 0; i < row.length; i++) {// Check linked nodes to current node
			if ((row[i] == 1) && (neighbours[i] == 0)) {
				neighbours[i] = 1;
				return findNeighbours(m, m[i], neighbours, destination);// Find all neighbours of current node
			}
		}
		return 0;
	}

	public static int findPath(int[][] m, int i, int j) {
		int[] neighbours = new int[m[0].length]; // Array of linked nodes
		neighbours[i] = 1; // Initialize starting node
		return findNeighbours(m, m[i], neighbours, j);
	}

}
