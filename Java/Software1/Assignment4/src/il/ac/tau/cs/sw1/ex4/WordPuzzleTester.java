package il.ac.tau.cs.sw1.ex4;

import java.util.Scanner;

public class WordPuzzleTester {
	public static void main(String[] args){
		String vocabularyText = "I look at the floor and I see it needs sweeping while my guitar gently wheeps";
		Scanner vocabularyScanner = new Scanner(vocabularyText);
		String[] vocabulary = WordPuzzle.scanVocabulary(vocabularyScanner);
		
		//puzzle1 = {_,_,_,e,_,_}
		char[] puzzle1 = {WordPuzzle.HIDDEN_CHAR, WordPuzzle.HIDDEN_CHAR, WordPuzzle.HIDDEN_CHAR, 'e', WordPuzzle.HIDDEN_CHAR, WordPuzzle.HIDDEN_CHAR};
		//puzzle2 = {_,_,e,e,_}
		char[] puzzle2 = {WordPuzzle.HIDDEN_CHAR, WordPuzzle.HIDDEN_CHAR, 'e', 'e', WordPuzzle.HIDDEN_CHAR};
		//puzzle3 = {w,_,i,_,e}
		char[] puzzle3 = new char[] {'w',WordPuzzle.HIDDEN_CHAR, 'i', WordPuzzle.HIDDEN_CHAR, 'e'};

		if (!WordPuzzle.isInVocabulary(vocabulary, "while")){
			System.out.println("Error 2.1");
		}
		
		if (!WordPuzzle.isLegalPuzzleStructure(new char[]{'a', WordPuzzle.HIDDEN_CHAR, 'b'})){
			System.out.println("Error 3.1");
		}
		if (WordPuzzle.isLegalPuzzleStructure(new char[]{'a', 'b'})){
			System.out.println("Error 3.2");
		}
		
		if (WordPuzzle.countHiddenInPuzzle(puzzle1) != 5){
			System.out.println("Error 4.1");
		}
		
		if (WordPuzzle.checkSolution(puzzle1, "wheeps")){
			System.out.println("Error 5.1");
		}
		if (!WordPuzzle.checkSolution(puzzle1, "thread")){
			System.out.println("Error 5.2");
		}
		if (!WordPuzzle.checkSolution(puzzle2, "tweet")){
			System.out.println("Error 5.3");
		}	
		
		if (!"tweet".equals(WordPuzzle.checkSingleSolution(puzzle2, new String[] {"tweet"}))){
			System.out.println("Error 6.1");
		}			
		if (WordPuzzle.checkSingleSolution(puzzle2, new String[] {"tweet", "sleep"}) != null){
			System.out.println("Error 6.2");
		}
		if (!"while".equals(WordPuzzle.checkSingleSolution(puzzle3, vocabulary))){
			System.out.println("Error 6.3");
		}
		
		int numOfChangedLetters = WordPuzzle.applyGuess('h', "while", puzzle3);
		if (numOfChangedLetters != 1){
			System.out.println("Error 7.1");
		}
		numOfChangedLetters =  WordPuzzle.applyGuess('i', "while", puzzle3);
		if (numOfChangedLetters != 0){
			System.out.println("Error 7.2");
		}
		
		System.out.println("done!");
	}
}
