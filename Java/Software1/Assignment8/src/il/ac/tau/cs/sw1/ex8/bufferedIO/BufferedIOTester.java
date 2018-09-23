package il.ac.tau.cs.sw1.ex8.bufferedIO;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class BufferedIOTester {
	public static final String RESOURCES_FOLDER = "resources/hw8/out/";

	public static void main(String[] args) throws IOException{
		String outputFileName = RESOURCES_FOLDER + "rocky1_out.txt";
		String outString1 = "Now somewhere in the Black mining Hills of Dakota\nThere lived a young boy named Rocky Raccoon,\n"; 
		String outString2 = "And one day his woman";
		String outString3 = " ran off with another guy,\nHit young Rocky in the eye.";
		FileWriter fWriter = new FileWriter(new File(outputFileName));
		IBufferedWriter bW = new MyBufferedWriter(fWriter, 10);
		bW.write(outString1);
		bW.write(outString2);
		bW.write(outString3);
		bW.close();
		
		/***
		 * The output file this tester creates should be identical to rocky1_correct.txt
		 * 
		 */
		
		
		// ***Custom Tests***
		
		// First File
		outputFileName = RESOURCES_FOLDER + "rocky2_out.txt";
		String inputFileName = RESOURCES_FOLDER + "../input/rocky2.txt";
		MyFileWriter mFWriter = new MyFileWriter(new File(outputFileName));
		bW = new MyBufferedWriter(mFWriter, 5);// Determine size of buffer
		BufferedReader bReader = new BufferedReader(new FileReader(new File(inputFileName)));
		String line = bReader.readLine();
		while (line != null){
			bW.write(line);
			line = bReader.readLine();
			if (line != null)
				bW.write(System.lineSeparator());
		}
		bW.close();
		if (mFWriter.getWritesCount() != 113)// Divide number of chars to size of buffer, check if +1 is needed
			// Counter assumes Windows operating system (Line seperator = 4 chars, so total file is 564 chars long)
			// On different OS, probaly should be 110 writes
			System.err.println("Should have written to file 113 times, uses " + mFWriter.getWritesCount() + " writes instead");
		System.out.println("Make sure output file " + outputFileName + " matches " + inputFileName);
		
		// Second File
		outputFileName = RESOURCES_FOLDER + "rocky3_out.txt";
		inputFileName = RESOURCES_FOLDER + "../input/rocky3.txt";
		mFWriter = new MyFileWriter(new File(outputFileName));
		bW = new MyBufferedWriter(mFWriter, 100);
		bReader = new BufferedReader(new FileReader(new File(inputFileName)));
		line = bReader.readLine();
		while (line != null){
			bW.write(line);
			line = bReader.readLine();
			if (line != null)
				bW.write(System.lineSeparator());
		}


		bW.close();
		bReader.close();
		if (mFWriter.getWritesCount() != 4)
			System.err.println("Should have written to file 4 times, uses " + mFWriter.getWritesCount() + " writes instead");
		System.out.println("Make sure output file " + outputFileName + " matches " + inputFileName);
	}
}
