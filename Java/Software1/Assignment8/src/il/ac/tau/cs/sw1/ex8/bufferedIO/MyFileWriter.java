package il.ac.tau.cs.sw1.ex8.bufferedIO;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;


public class MyFileWriter extends FileWriter{

	private int writesCounter = 0;
	
	public MyFileWriter(File arg0) throws IOException {
		super(arg0);
	}

	
	
	@Override
	public void write(char[] cbuf, int off, int len) throws IOException {
		writesCounter++;
		super.write(cbuf, off, len);
	}


	@Override
	public void write(String str, int off, int len) throws IOException {
		writesCounter++;
		super.write(str, off, len);
	}



	@Override
	public void write(int c) throws IOException {
		writesCounter++;
		super.write(c);
	}



	public int getWritesCount(){
		return writesCounter;
	}
	

}
