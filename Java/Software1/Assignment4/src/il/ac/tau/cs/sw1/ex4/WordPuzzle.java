package il.ac.tau.cs.sw1.ex4;

import java.io.File;
import java.util.Arrays;
import java.util.Scanner;

public class WordPuzzle {
	public static final char HIDDEN_CHAR = '_';
	public static final int MAX_VOCABULARY_SIZE = 3000;
	
	
	private static boolean hasAppeared(String word, String[] vocabulary, int count){
		//The function checks if the word was already
		//added to the vocabulary, so there won't be any duplicates
		for (int i = 0; i < count; i++){
			if (word.equals(vocabulary[i])){
				return true;				
			}
		}
		return false;
	}
	
	private static boolean isValidWord (String word){
		//The function checks if the given word is a valid a-z only letters word
		char[] letters = word.toCharArray();
		for (char c : letters){
			if ((c < 'a') || (c > 'z'))
				return false;
		}
		return true;
	}
	
	public static String[] scanVocabulary(Scanner scanner){          // Q - 1
		//The function returns a vocabulary from a given file as a string array
		String[] vocabulary = new String[MAX_VOCABULARY_SIZE];
		int count = 0;
		String word;
		
		while ((scanner.hasNext()) && (count < MAX_VOCABULARY_SIZE)){
			word = scanner.next().toLowerCase();
			if ((!hasAppeared(word, vocabulary, count)) && (isValidWord(word))){//Check if the word already appeared
				vocabulary[count] = word;
				count++;				
			}
		}
		
		if (count < MAX_VOCABULARY_SIZE){
			String [] trimVocabulary = new String[count];
			for (int i = 0; i < count; i++){
				trimVocabulary[i] = vocabulary[i];
			}
			Arrays.sort(trimVocabulary);
			return trimVocabulary;
		}
		Arrays.sort(vocabulary);
		return vocabulary;
	}
	
	
	
	public static boolean isInVocabulary(String[] vocabulary, String word){ // Q - 2
		//The function checks if the string given appears in the array of strings
		int leftMarker = 0;
		int rightMarker = vocabulary.length;
		int middle;
		word.toLowerCase();
		while (leftMarker < rightMarker){
			middle = Math.round((leftMarker + rightMarker) / 2);
			if (word.equals(vocabulary[middle]))
				return true;
			if (word.compareTo(vocabulary[middle]) > 0){
				leftMarker = middle + 1;
			}
			else{
				rightMarker = middle - 1;
			}
		}
		return false;
	}

	
	public static boolean isLegalPuzzleStructure(char[] puzzle){  // Q - 3
		//The function checks if the char array given is a valid puzzle
		int count = 0;
		for (int i = 0; i < puzzle.length; i++){
			if (((puzzle[i] >= 'a') && (puzzle[i] <= 'z')) || (puzzle[i] == HIDDEN_CHAR)){
				if (puzzle[i] == HIDDEN_CHAR){
					count++;
				}
			}
			else
				return false;
		}
		if (count == 0)
			return false;
		return true;
	}
	
	
	public static int countHiddenInPuzzle(char[] puzzle){ // Q - 4
		//The function checks how many letters are still hidden in the given puzzle
		int count = 0;
		for (int i = 0; i < puzzle.length; i++){
			if (puzzle[i] == HIDDEN_CHAR){
				count++;
			}
		}
		return count;
	}
	
	
	public static boolean checkSolution(char[] puzzle, String word){ // Q - 5
		//The function checks if the given string is a valid solution to the puzzle
		if (puzzle.length != word.length())
			return false;
		
		int [] wordLetters = new int[26];
		int [] puzzleLetters = new int[26];
		
		for (int i = 0; i < word.length(); i++){
			if (puzzle[i] != HIDDEN_CHAR){
				if (puzzle[i] != word.charAt(i)){
					return false;
				}
				puzzleLetters[Character.getNumericValue(puzzle[i]) - 10]++;
			}
			wordLetters[Character.getNumericValue(word.charAt(i)) - 10]++;
		}
		
		for (int i = 0; i < wordLetters.length; i++){
			if ((wordLetters[i] != puzzleLetters[i]) && (puzzleLetters[i] != 0)){
				return false;
			}
		}
		return true;
	}
	
	
	public static String checkSingleSolution(char[] puzzle, String[] vocabulary){ // Q - 6
		//The function checks if there is only 1 valid solution to the given puzzle int the vocabulary, else returns null
		String solution = "";
		for (int i = 0; i < vocabulary.length; i++){
			if (checkSolution(puzzle, vocabulary[i])){
				if (solution == ""){
					solution = vocabulary[i];
				}
				else
					return null;
			}
		}
		return solution;
		
	}
	
	
	public static int applyGuess(char guess, String solution, char[] puzzle){ // Q - 7
		//The function changes the puzzle according to the solution and the guess given
		int count = 0;
		for (int i = 0; i < solution.length(); i++){
			if (solution.charAt(i) == guess){
				if (puzzle[i] == HIDDEN_CHAR){
					count++;
					puzzle[i] = guess;
				}
			}
		}
		return count;
	}


	public static void main(String[] args) throws Exception{ //Q - 8
		if (args.length == 0){
			System.out.println("No path was given to the vocabulary!");
		}
		else if (args.length > 1){
			System.out.println("Please input only the path to the vocabulary, as a single argument, through the command line!");
		}
		else{
			Scanner vocabularyPath = new Scanner(new File(args[0]));
			String[] vocabulary = scanVocabulary(vocabularyPath);
			printReadVocabulary(args[0], vocabulary.length);
			printSettingsMessage();
			printEnterPuzzleMessage();
			Scanner userInput = new Scanner(System.in); 
			boolean validInput = false;
			String solution = "";
			char[] puzzle = userInput.nextLine().toCharArray();
			
			while (!validInput){
				validInput = true;
				if (!isLegalPuzzleStructure(puzzle)){
					validInput = false;
					printIllegalPuzzleMessage();
					printEnterPuzzleMessage();
					puzzle = userInput.nextLine().toCharArray();
				}
				
				else {
					solution = checkSingleSolution(puzzle, vocabulary);
					if ((solution == null) || (solution == "")){
						validInput = false;
						printIllegalSolutionsNumberMessage();
						printEnterPuzzleMessage();
						puzzle = userInput.nextLine().toCharArray();
					}
				}
			}
			
			printGameStageMessage();
			int numOfTries = countHiddenInPuzzle(puzzle) + 3;
			boolean gameOver = false;
			char guess;
			while (!gameOver){
				printPuzzle(puzzle);
				printEnterYourGuessMessage();
				guess = userInput.nextLine().charAt(0);
				numOfTries--;
				if (applyGuess(guess, solution, puzzle) > 0){
					if (countHiddenInPuzzle(puzzle) == 0){
						printWinMessage();
						gameOver = true;
					}
					else{printCorrectGuess(numOfTries);
						
					}
				}
				else{
					printWrongGuess(numOfTries);
				}
				if ((numOfTries == 0) && (!gameOver)){
					gameOver = true;
					printGameOver();
				}
			}		
			userInput.close();
		}
	}


	/*************************************************************/
	/*********************  Don't change this ********************/
	/*************************************************************/
	
	public static void printReadVocabulary(String vocabularyFileName, int numOfWords){
		System.out.println("Read " + numOfWords + " words from " + vocabularyFileName);
	}

	public static void printSettingsMessage(){
		System.out.println("--- Settings stage ---");
	}
	
	public static void printEnterPuzzleMessage(){
		System.out.println("Enter your puzzle:");
	}
	
	public static void printIllegalPuzzleMessage(){
		System.out.println("Illegal puzzle, try again!");
	}
	
	public static void printIllegalSolutionsNumberMessage(){
		System.out.println("Puzzle doesn't have a single solution, try again!");
	}
	
	
	public static void printGameStageMessage(){
		System.out.println("--- Game stage ---");
	}
	
	public static void printPuzzle(char[] puzzle){
		System.out.println(puzzle);
	}
	
	public static void printEnterYourGuessMessage(){
		System.out.println("Enter your guess:");
	}
	
	public static void printCorrectGuess(int attemptsNum){
		System.out.println("Correct Guess, " + attemptsNum + " guesses left");
	}
	
	public static void printWrongGuess(int attemptsNum){
		System.out.println("Wrong Guess, " + attemptsNum + " guesses left");
	}

	public static void printWinMessage(){
		System.out.println("Congratulations! You solved the puzzle");
	}
	
	public static void printGameOver(){
		System.out.println("Game over!");
	}

}
