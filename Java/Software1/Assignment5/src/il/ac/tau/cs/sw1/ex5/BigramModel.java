package il.ac.tau.cs.sw1.ex5;


import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class BigramModel {
	public static final int MAX_VOCABULARY_SIZE = 14000;
	public static final String VOC_FILE_SUFFIX = ".voc";
	public static final String COUNTS_FILE_SUFFIX = ".counts";
	public static final String SOME_NUM = "some_num";
	public static final int ELEMENT_NOT_FOUND = -1;
	
	String[] mVocabulary;
	int[][] mBigramCounts;
	
	// DO NOT CHANGE THIS !!! 
	public void initModel(String fileName) throws IOException{
		mVocabulary = buildVocabularyIndex(fileName);
		mBigramCounts = buildCountsArray(fileName, mVocabulary);
		
	}
	
	private String isValid(String word){
		//The function check if the given word is legal or not - only digits or has at least one letter
		if (word.length() < 1)
			return "";
		char[] letters = word.toCharArray();
		int countDigits = 0;
		for (char letter : letters){
			if (((letter >= 'a') && (letter <= 'z')) || ((letter >= 'A') && (letter <= 'Z')))
				return word.toLowerCase();
			if (Character.isDigit(letter))
				countDigits++; 
		}
		if (countDigits == word.length())
			return SOME_NUM;
		return "";
	}
	
	private boolean isInVocabulary(String word, String[] vocabulary, int length){
		//Checks if the given word is in the vocabulary already
		for (int i = 0; i < length; i++){
			if (vocabulary[i].equals(word))
				return true;
		}
		return false;
	}
	
	private int placeInVocabulary(String word, String[] vocabulary){
		//Checks if the given word is in the vocabulary, and return it's index, or -1 if not found
		//The function assumes that each word in the vocabulary is unique
		for (int i = 0; i < vocabulary.length; i++){
			if (vocabulary[i].equals(word))
				return i;
		}
		return -1;
	}
	
	
	/*
	 * @post: mVocabulary = prev(mVocabulary)
	 * @post: mBigramCounts = prev(mBigramCounts)
	 */
	public String[] buildVocabularyIndex(String fileName) throws IOException{ // Q 1
		//The function builds a vocabulary from a given file
		//Only words with at least 1 letter or is only digits 
		BufferedReader buffReader = new BufferedReader(new FileReader(fileName));
		String[] vocabulary = new String[MAX_VOCABULARY_SIZE];
		int vocSize = 0;
		String line, word;
		String[] words;
		while ((line = buffReader.readLine()) != null){
			words = line.split(" ");//Split every line to separated words
			for (int i = 0; i < words.length; i++){
				word = isValid(words[i]);
				if (word != ""){//Check if each word is valid
					if (!isInVocabulary(word, vocabulary, vocSize)){//Make sure it's a new word
						vocabulary[vocSize] = word;
						vocSize++;
						}
					}
				}
		}
		buffReader.close();
		if (vocSize < MAX_VOCABULARY_SIZE){//Cut the unused space with a new trimmed vocabulary
			String[] trimVoc = new String[vocSize];
			for (int i=0; i < vocSize; i++){
				trimVoc[i] = vocabulary[i];
			}
			return trimVoc;
		}
		return vocabulary;
	}
	
	
	
	/*
	 * @post: mVocabulary = prev(mVocabulary)
	 * @post: mBigramCounts = prev(mBigramCounts)
	 */
	public int[][] buildCountsArray(String fileName, String[] vocabulary) throws IOException{ // Q - 2
		//The function returns a 2D integers array, that the i,j cell represents the amount of times
		//the word vocabulary[j] appeared right after the word vocabulary[i] in the given file
		int [][] countsArray = new int[vocabulary.length][vocabulary.length];
		BufferedReader buffReader = new BufferedReader(new FileReader(fileName));
		String line;
		String[] words;
		int i, current, next;
		while ((line = buffReader.readLine()) != null){
			words = line.split(" ");
			i = 0;
			while (i < words.length-1){
				current = placeInVocabulary(words[i].toLowerCase(), vocabulary);
				if (current != -1){
					next = placeInVocabulary(words[i+1].toLowerCase(), vocabulary);
					if (next != -1){
						countsArray[current][next]++;
					}
					else
						i++;//If next = -1 the next word isn't in the vocabulary and we can skip it
				}
				i++;
			}
		}
		buffReader.close();
		return countsArray;
	}
	

	/*
	 * @pre: the method initModel was called (the language model is initialized)
	 * @pre: fileName is a legal file path
	 */
	public void saveModel(String fileName) throws IOException{ // Q-3
		BufferedWriter toVoc = new BufferedWriter(new FileWriter(fileName + VOC_FILE_SUFFIX));
		BufferedWriter toCounts = new BufferedWriter(new FileWriter(fileName + COUNTS_FILE_SUFFIX));
		toVoc.write(mVocabulary.length + " words" + System.lineSeparator());
		for (int i = 0; i < mVocabulary.length; i++)
			toVoc.write(i + "," + mVocabulary[i] + System.lineSeparator());
		toVoc.close();
		for (int i = 0; i < mBigramCounts.length; i++){
			for (int j = 0; j< mBigramCounts.length; j++){
				if (mBigramCounts[i][j] != 0){
					toCounts.write(i + "," + j + ":" + mBigramCounts[i][j] + System.lineSeparator());
				}
			}
		}
		toCounts.close();
	}
	
	
	
	/*
	 * @pre: fileName is a legal file path
	 */
	public void loadModel(String fileName) throws IOException{ // Q - 4
		BufferedReader fromVoc = new BufferedReader(new FileReader(fileName + VOC_FILE_SUFFIX));
		BufferedReader fromCounts = new BufferedReader(new FileReader(fileName + COUNTS_FILE_SUFFIX));
		String line;
		line = fromVoc.readLine().split(" ")[0];//Read the first "word" in the file, which is the size of the vocabulary
		String[] vocabulary = new String[Integer.parseInt(line)];
		int[][] counts = new int[vocabulary.length][vocabulary.length];
		int i = 0, j;
		String index;
		while ((line = fromVoc.readLine()) != null){
			vocabulary [i] = line.split(",")[1];
			i++;
		}
		fromVoc.close();
		
		while ((line = fromCounts.readLine()) != null){
			index = line.split(":")[0];
			i = Integer.parseInt(index.split(",")[0]);
			j = Integer.parseInt(index.split(",")[1]);
			counts [i][j] = Integer.parseInt(line.split(":")[1]);
		}
		fromCounts.close();
		
		mVocabulary = vocabulary;
		mBigramCounts = counts;
	}

	
	
	/*
	 * @pre: word is in lowercase
	 * @pre: the method initModel was called (the language model is initialized)
	 * @pre: word is in lowercase
	 * @post: $ret = -1 if word is not in vocabulary, otherwise $ret = the index of word in vocabulary
	 */
	public int getWordIndex(String word){  // Q - 5
		return placeInVocabulary(word, mVocabulary);
	}
	
	
	
	/*
	 * @pre: word1, word2 are in lowercase
	 * @pre: the method initModel was called (the language model is initialized)
	 * @post: $ret = the count for the bigram <word1, word2>. if one of the words does not
	 * exist in the vocabulary, $ret = 0
	 */
	public int getBigramCount(String word1, String word2){ //  Q - 6
		int i = getWordIndex(word1);
		int j = getWordIndex(word2);
		if ((i == -1) || (j == -1))
			return 0;
		return mBigramCounts[i][j];
	}
	
	
	/*
	 * @pre word in lowercase, and is in mVocabulary
	 * @pre: the method initModel was called (the language model is initialized)
	 * @post $ret = the word with the lowest vocabulary index that appears most fequently after word (if a bigram starting with
	 * word was never seen, $ret will be null
	 */
	public String getMostFrequentProceeding(String word){ //  Q - 7
		int max = 0;
		int frequentIndex = 0;
		int wordIndex = getWordIndex(word);
		for (int i = 0; i < mVocabulary.length; i++){
			if (mBigramCounts[wordIndex][i] > max){
				max = mBigramCounts[wordIndex][i];
				frequentIndex = i;
			}
		}
		if (max != 0)
			return mVocabulary[frequentIndex];
		return null;
	}
	
	
	/* @pre: sentence is in lowercase
	 * @pre: the method initModel was called (the language model is initialized)
	 * @pre: each two words in the sentence are are separated with a single space
	 * @post: if sentence is is probable, according to the model, $ret = true, else, $ret = false
	 */
	public boolean isLegalSentence(String sentence){  //  Q - 8
		String [] words = sentence.split(" ");
		for (int i = 0; i < words.length-1; i++){
			if (getBigramCount(words[i], words[i+1]) == 0)
				return false;
		}
		return true;
	}
	
	
	
	/*
	 * @pre: arr1.length = arr2.legnth
	 * post if arr1 or arr2 are only filled with zeros, $ret = 0, otherwise
	 */
	public static double calcCosineSim(int[] arr1, int[] arr2){ //  Q - 9
		int sumASquared = 0;
		int sumBSquared = 0;
		int denominator = 0;
		for (int i = 0; i < arr1.length; i++){
			sumASquared += (arr1[i] * arr1[i]);
			sumBSquared += (arr2[i] * arr2[i]);
			denominator += (arr1[i] * arr2[i]);
		}
		if ((sumASquared == 0) || (sumBSquared == 0))
			return 0.;
		return denominator/(Math.sqrt(sumASquared) * Math.sqrt(sumBSquared));
	}

	
	/*
	 * @pre: word is in vocabulary
	 * @pre: the method initModel was called (the language model is initialized), 
	 * @post: $ret = w implies that w is the word with the largest cosineSimilarity(vector for word, vector for w) among all the
	 * other words in vocabulary
	 */
	public String getClosestWord(String word){ //  Q - 10
		double max = 0;
		double temp;
		String closestWord = "";
		int wordIndex = getWordIndex(word);
		for (int i = 0; i < mVocabulary.length; i++){
			if (i != wordIndex){
				temp = calcCosineSim(mBigramCounts[wordIndex], mBigramCounts[i]);
				if (temp > max){
					max = temp;
					closestWord = mVocabulary[i];
					}
				}
			}
		return closestWord;
		}
	
}
