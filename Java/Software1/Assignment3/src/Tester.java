import java.util.Arrays;

public class Tester {


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

	
	public static String sortStringWords(String str) {
		String[] strArray = str.split(" ");
		Arrays.sort(strArray);
		String temp;
		StringBuilder strBuild = new StringBuilder();
		for (int i = 0; i < strArray.length / 2; i++) {
			temp = strArray[i];
			strArray[i] = strArray[strArray.length - i - 1];
			strArray[strArray.length - i - 1] = temp;
		}
		for (int i = 0; i < strArray.length; i++) {
			if (i != strArray.length - 1)
				strBuild.append(strArray[i] + " ");
			else
				strBuild.append(strArray[i]);
		}
		str = strBuild.toString();
		return str;
	}

	public static String mergeStrings(String a, String b) {
		StringBuilder strBuild = new StringBuilder();
		for (int i = 0; i < a.length(); i++){
			for (int j = 0; j < b.length(); j++){
				if (a.charAt(i) == b.charAt(j)){
					strBuild.append(a.charAt(i));
				}
			}
			
		}
		return strBuild.toString();
	}
	
	public static int[] countLetters(String str) {
		int[] charCount = new int[26];
		for (int i = 0; i < str.length(); i++) {
			charCount[Character.getNumericValue(str.charAt(i)) - 10]++;// Count each time the letter appeared

		}
		return charCount;
	}

	public static boolean isAnagram(String a, String b) {
		if ((a.replaceAll("\\s", "").equals(b.replaceAll("\\s", "")) && (a.replaceAll("\\s", "").equals(""))))// Make sure if strings are only spaces, they are anagram if they are same length
			if (a.length() == b.length())
				return true;
			else
				return false;
		a = a.replaceAll("\\s", "");// Cut all whitespaces
		b = b.replaceAll("\\s", "");// Because it doesn't affect anagrams
		if (a.length() != b.length())// Not same size = Can't be anagram!
			return false;

		int[] charCountA = countLetters(a);// Array with character
		int[] charCountB = countLetters(b);// count for each string
		for (int i = 0; i < charCountA.length; i++) {
			if (charCountA[i] != charCountB[i])// Check they have same amount of letters
				return false;
		}
		return true;

	}

	public static void testReverseArray(int[] array, int[] result) {

		int[] answer = reverseArray(array);

		if (!Arrays.equals(answer, result))
			System.out.println(Arrays.toString(array) + "expected: " + Arrays.toString(result) + ", result: "
					+ Arrays.toString(answer));
		else
			System.out.println(Arrays.toString(array) + "correct!");
	}

	public static void testShiftArray(int[] array, int move, int[] result) {

		int[] answer = shiftArrayToTheRightCyclic(array, move);

		if (!Arrays.equals(answer, result))
			System.out.println(Arrays.toString(array) + "expected: " + Arrays.toString(result) + ", result: "
					+ Arrays.toString(answer));
		else
			System.out.println(Arrays.toString(array) + "correct!");
	}

	public static void testAlternateSum(int[] array, int result) {

		int answer = alternateSum(array);

		if (answer != result)
			System.out.println(Arrays.toString(array) + "expected: " + result + ", result: " + answer);
		else
			System.out.println(Arrays.toString(array) + "correct!");
	}

	public static void testFindPath(int[][] m, int i, int j, int result) {

		int answer = findPath(m, i, j);

		if (answer != result)
			System.out.println(Arrays.deepToString(m) + "expected: " + result + ", result: " + answer);
		else
			System.out.println(Arrays.deepToString(m) + "correct!");
	}
	
	public static void testSortStrings(String str, String result) {

		String answer = sortStringWords(str);

		if (!answer.equals(result)) {
			System.out.println(str + " expected: " + result + ", result: " + answer);
		} else {
			System.out.println(str + " correct!");
		}
	}

	public static void testMergeStrings(String a, String b, String result) {

		String answer = mergeStrings(a, b);

		if (!answer.equals(result)) {
			System.out.println(a + " " + b + " expected: " + result + ", result: " + answer);
		} else {
			System.out.println(a + " " + b + " correct!");
		}
	}
	
	public static void testIsAnagram(String a, String b, boolean result) {

		boolean answer = isAnagram(a, b);

		if (answer != result) {
			System.out.println(a + " " + b + " expected: " + result + ", result: " + answer);
		} else {
			System.out.println(a + " " + b + " correct!");
		}
	}


	public static void main(String[] args) {
		testReverseArray(new int[] { 1, 2, 3, 4, 5 }, new int[] { 5, 4, 3, 2, 1 });
		testReverseArray(new int[] { 1 }, new int[] { 1 });
		testReverseArray(new int[] { 2, 5, 3 }, new int[] { 3, 5, 2 });
		testReverseArray(new int[] { 4, 3, 2, 1 }, new int[] { 1, 2, 3, 4 });

		testShiftArray(new int[] { 1, 2, 3, 4, 5 }, -1, new int[] { 1, 2, 3, 4, 5 });
		testShiftArray(new int[] { 1, 2, 3, 4, 5 }, 3, new int[] { 3, 4, 5, 1, 2 });
		testShiftArray(new int[] { 1, 2, 3, 4, 5 }, 8, new int[] { 3, 4, 5, 1, 2 });
		testShiftArray(new int[] { 1, 2, 3, 4, 5, 6 }, 9, new int[] { 4, 5, 6, 1, 2 ,3});

		testAlternateSum(new int[] { 1, -2, 3, 4, 5 }, 7);
		testAlternateSum(new int[] { 1, 2, -3, 4, 5 }, 9);
		testAlternateSum(new int[] {}, 0);
		testAlternateSum(new int[] { 1, -2, 3, 4, 5 }, 7);
		testAlternateSum(new int[] { 1, 0, 0, 0, 10, 10 }, 11);
		testAlternateSum(new int[] { 1, -1, -1, 1, 0, 0, 0, 1 }, 2);

		int[][] array = { { 1, 0, 0, 1, 0, 0, 0, 0, 0 }, { 0, 1, 0, 1, 1, 0, 0, 0, 0 }, { 0, 0, 1, 0, 1, 0, 1, 0, 0 },
				{ 1, 1, 0, 1, 0, 0, 0, 0, 0 }, { 0, 1, 1, 0, 1, 0, 0, 1, 0 }, { 0, 0, 0, 0, 0, 1, 1, 1, 0 },
				{ 0, 0, 1, 0, 0, 1, 1, 0, 0 }, { 0, 0, 0, 0, 1, 1, 0, 1, 0 }, { 0, 0, 0, 0, 0, 0, 0, 1 } };
		testFindPath(array, 0, 7, 1);
		testFindPath(array, 0, 8, 0);
		testFindPath(new int[][] { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } }, 1, 1, 1);
		array = new int[][] { { 1, 0, 0, 1 }, { 0, 1, 0, 1 }, { 0, 0, 1, 0 }, { 1, 1, 0, 1 } };
		testFindPath(array, 0, 1, 1);
		testFindPath(array, 0, 2, 0);
		
		testSortStrings("to be or not to be", "to to or not be be");
		testSortStrings("a b c d e f g", "g f e d c b a");
		
		testMergeStrings("boy", "girl", "");
		testMergeStrings("catdog", "boygirl", "og");
		testMergeStrings("abcdefg", "bcgfhi", "bcfg");
		testMergeStrings("abcdefgk", "kbcgfhi", "bcfgk");
		testMergeStrings("abcdefgk", "bcgfhik", "bcfgk");
		
		testIsAnagram("  mother in law", "hitler woman  ", true);
		testIsAnagram("software", "jeans", false);
		testIsAnagram("tom marvolo riddle", "i am lord voldemort", true);
		testIsAnagram("ababababbbb", "ababababbb", false);
		testIsAnagram("ababababbbb", "bababababbb", true);
		testIsAnagram("ababababbbb", "bbbababababbb", false);
		testIsAnagram(" ", "   ", false);
		testIsAnagram("   ", "   ", true);
		testIsAnagram("a", " a  ", true);
	}

}
