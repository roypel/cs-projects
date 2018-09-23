package il.ac.tau.cs.sw1.ex8.wordsRank;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import il.ac.tau.cs.sw1.ex8.histogram.HashMapHistogram;
import il.ac.tau.cs.sw1.ex8.wordsRank.RankedWord.rankType;

/**************************************
 * Add your code to this class !!! *
 **************************************/

public class FileIndex {

	public static final int UNRANKED_CONST = 20;

	private HashMap<String, HashMapHistogram<String>> index;
	private HashMap<String, HashMap<String, Integer>> wordToFilesToRank;
	private HashMap<String, RankedWord> rankOfWords;
	private  int unranked;

	public FileIndex() {
		this.index = new HashMap<>();
		this.wordToFilesToRank = new HashMap<>();
		this.rankOfWords = new HashMap<>();
		this.unranked = 0;
	}

	private void rankWordsInFile(String fileName){
		Iterator<String> iter = this.index.get(fileName).iterator();
		int rank = 0;
		String word;
		while (iter.hasNext()){// Build a map between each word to it's rank in the file
			word = iter.next();
			rank++;
			if (!this.wordToFilesToRank.containsKey(word))// Add new word to mapping
				this.wordToFilesToRank.put(word, new HashMap<String, Integer>());
			this.wordToFilesToRank.get(word).put(fileName, rank);// If word already seen, update it's map
		}
	}
	
	private void addRanksToWords (){
		int diffrentWordCount;
		for (String word : this.wordToFilesToRank.keySet()) {
			for (String fileName : this.index.keySet()){
				try {
					if (getCountInFile(fileName, word) == 0){// Fill the files the word didn't appeared in them
						diffrentWordCount = this.index.get(fileName).getItemsSet().size();
						this.wordToFilesToRank.get(word).put(fileName, diffrentWordCount + UNRANKED_CONST);
					}
				}catch (FileIndexException e) {
					e.toString();
				}
			}
			this.rankOfWords.put(word, new RankedWord(word, this.wordToFilesToRank.get(word)));// Add the word to RankedWords mapping
		}
	}
	
	
	/*
	 * @pre: the directory is no empty, and contains only readable text files
	 */
	public void indexDirectory(String folderPath) {
		// This code iterates over all the files in the folder. add your code
		// wherever is needed

		File folder = new File(folderPath);
		File[] listFiles = folder.listFiles();
		for (File file : listFiles) {
			// for every file in the folder
			if (file.isFile()) {
				try {
					if (!this.index.containsKey(file.getName())){// Make sure file wasn't checked before
						List<String> wordsInFile = FileUtils.readAllTokens(file);
						HashMapHistogram<String> histogram = new HashMapHistogram<>();
						histogram.addAll(wordsInFile);
						this.index.put(file.getName(), histogram);
						this.unranked += histogram.getItemsSet().size() + UNRANKED_CONST;
						rankWordsInFile(file.getName());
						}
					} catch (IOException e) {
						System.err.println("Folder is empty or contains unreadable files");
						}
				}
			}
		addRanksToWords();
	}

	/*
	 * @pre: the index is initialized
	 * 
	 * @pre filename is a name of a valid file
	 * 
	 * @pre word is not null
	 */
	public int getCountInFile(String filename, String word) throws FileIndexException {
		if (!index.containsKey(filename))// filename doesn't exist in directory
			throw new FileIndexException("The file doesn't exist in the directory!");
		return index.get(filename).getCountForItem(word.toLowerCase());
	}

	/*
	 * @pre: the index is initialized
	 * 
	 * @pre filename is a name of a valid file
	 * 
	 * @pre word is not null
	 */
	public int getRankForWordInFile(String filename, String word) throws FileIndexException {
		if (!this.index.containsKey(filename))
			throw new FileIndexException("The file doesn't exist in the directory!");
		String lowerCase = word.toLowerCase();
		if (this.wordToFilesToRank.containsKey(lowerCase))
			return this.wordToFilesToRank.get(lowerCase).get(filename);
		return this.index.get(filename).getItemsSet().size() + UNRANKED_CONST;
	}

	/*
	 * @pre: the index is initialized
	 * 
	 * @pre word is not null
	 */
	public int getAverageRankForWord(String word) {
		String lowerCase = word.toLowerCase();
		if (this.rankOfWords.containsKey(lowerCase))
			return this.rankOfWords.get(lowerCase).getRankByType(rankType.average);
		return (int)Math.round(((double)this.unranked) / this.index.size());
	}

	public List<String> aboveK (int k, rankType cType){
		List<RankedWord> rankedWordList = new ArrayList<>(this.rankOfWords.values());
		Collections.sort(rankedWordList, new RankedWordComparator(cType));
		List<String> list = new ArrayList<>();
		int i = 0;
		while (rankedWordList.get(i).getRankByType(cType) <= k)
			list.add(rankedWordList.get(i++).getWord());
		return list;
	}
	
	public List<String> getWordsWithAverageRankLowerThenK(int k) {
		return aboveK(k, rankType.average);
	}

	public List<String> getWordsBelowMinRank(int k) {
		return aboveK(k, rankType.min);
	}

	public List<String> getWordsAboveMaxRank(int k) {
		return aboveK(k, rankType.max);
	}
}
