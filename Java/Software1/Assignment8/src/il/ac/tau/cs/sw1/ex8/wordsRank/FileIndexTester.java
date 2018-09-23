package il.ac.tau.cs.sw1.ex8.wordsRank;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import il.ac.tau.cs.sw1.ex8.wordsRank.RankedWord.rankType;

public class FileIndexTester {
	
	public static final String INPUT_FOLDER = "resources/hw8/input";

	public static void main(String[] args){
		testRankedWordComparator();
		testFileIndex();
		System.out.println("done!");
	}

	public static void testRankedWordComparator(){
		Map<String, Integer> ranks1 = new HashMap<>();
		ranks1.put("file1", 1);
		ranks1.put("file2", 120);
		ranks1.put("file3", 8);
		RankedWord rWord1 = new RankedWord("Julia", ranks1);
		
		Map<String, Integer> ranks2 = new HashMap<>();
		ranks2.put("file1", 70);
		ranks2.put("file2", 50);
		ranks2.put("file3", 3);
		RankedWord rWord2 = new RankedWord("Eleanor", ranks2);
		RankedWordComparator minComp = new RankedWordComparator(rankType.min);
		RankedWordComparator maxComp = new RankedWordComparator(rankType.max);
		RankedWordComparator averageComp = new RankedWordComparator(rankType.average);

		if (minComp.compare(rWord1, rWord2) >= 0){
			printErrorNum(1);
		}
		if (maxComp.compare(rWord1, rWord2) <= 0){
			printErrorNum(2);
		}
		if (averageComp.compare(rWord1, rWord2) <= 0){
			printErrorNum(3);
		}
		System.out.println("finished RankedWord Test!");
	}
	
	public static void testFileIndex(){
		FileIndex fIndex = new FileIndex();
		fIndex.indexDirectory(INPUT_FOLDER);

		try {
			if (fIndex.getCountInFile("rocky1.txt", "Rocky") != 5) {
				printErrorNum(4);
			}
			if (fIndex.getRankForWordInFile("rocky3.txt", "and") != 1){
				printErrorNum(5);
			}

		} catch (FileIndexException e) {
			printErrorNum(6);
		}
		try{
			fIndex.getRankForWordInFile("help.txt", "rocky"); //non existing file
			printErrorNum(7);
		}
		catch (FileIndexException e) {
		}
		
		//in rocky1.txt: rank = 1, in rocky2.txt: rank = 4, in rocky3.txt: rank = 2
		if (fIndex.getAverageRankForWord("rocky") != Math.round((1+4+2)/3.)){
			printErrorNum(8);
		}

		List<String> topByMin = fIndex.getWordsBelowMinRank(1);
		//"rocky" is ranked 
		if (!topByMin.contains("rocky") || !topByMin.contains("and") || !topByMin.contains("his")){
			printErrorNum(9);
		}
		
		//highest rank for rocky is 4
		List<String> topByMax = fIndex.getWordsAboveMaxRank(5);
		if (!topByMax.get(0).equals("rocky")){
			printErrorNum(10);
		}


		
		// *** Custom Tests ***
		List<String> topByAvg = fIndex.getWordsWithAverageRankLowerThenK(5);// Check small to large values ordering
		if (((!topByAvg.get(0).equals("rocky"))|| (!topByAvg.get(1).equals("and")) || (topByAvg.size() > 2)))
			printErrorNum(11);
		

		FileIndex newFIndex = new FileIndex();
		newFIndex.indexDirectory("resources/hw8/new");
		
		try {
			if (newFIndex.getRankForWordInFile("only_a.txt", "b") != 21){
				System.out.println("Problem with Rank for Word not in File");
			}

		} catch (FileIndexException e) {
			printErrorNum(6);
		}
		
		if (newFIndex.getAverageRankForWord("a") != Math.round((1+22+22)/3.)){
			System.out.println("Problem with Rank for Word not in File OR Average Rank for Word1");
		}
		
		if (newFIndex.getAverageRankForWord("d") != Math.round((21+22+22)/3.)){
			System.out.println("Problem with Rank for Word not in File OR Average Rank for Word2");
		}	
		
		
		// *** Times Tests ***

		FileIndex timeIndex = new FileIndex();
		System.out.println("Building Index please wait!");
		long t1 = System.currentTimeMillis();
		timeIndex.indexDirectory("resources/hw8/times");
		long t2 = System.currentTimeMillis();
		System.out.println(t2-t1 + " Miliseconds for Building Index");
		t1 = System.currentTimeMillis();
		List<String> topByAvgTime = timeIndex.getWordsWithAverageRankLowerThenK(5);
		t2 = System.currentTimeMillis();
		System.out.println(t2-t1 + " Miliseconds for Above K");
		
		t1 = System.currentTimeMillis();
		try{
			timeIndex.getRankForWordInFile("Ulysses.txt", "his");
		}
		catch (FileIndexException e) {
		}
		t2 = System.currentTimeMillis();
		System.out.println(t2-t1 + " Miliseconds for Rank for word in file");
		
		t1 = System.currentTimeMillis();
		try{
			timeIndex.getRankForWordInFile("Ulysses.txt", "noWordLikeThis");
		}
		catch (FileIndexException e) {
		}
		t2 = System.currentTimeMillis();
		System.out.println(t2-t1 + " Miliseconds for Rank for word in file, word not in file");
		
		t1 = System.currentTimeMillis();
		timeIndex.getAverageRankForWord("alice");
		t2 = System.currentTimeMillis();
		System.out.println(t2-t1 + " Miliseconds for Average rank for word");
		
		t1 = System.currentTimeMillis();
		try {
			timeIndex.getCountInFile("Ulysses.txt", "Ulysses");
		} catch (FileIndexException e) {
			e.printStackTrace();
		}
		t2 = System.currentTimeMillis();
		System.out.println(t2-t1 + " Miliseconds for Count in File");
		
		
		System.out.println("finished fileIndex Test!");

	}
	
	private static void printErrorNum(int num){
		System.out.println("ERROR " + num);
	}
}
