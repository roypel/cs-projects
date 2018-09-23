package il.ac.tau.cs.sw1.hw3;

import java.util.Arrays;

public class StringUtils {
	

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
}
