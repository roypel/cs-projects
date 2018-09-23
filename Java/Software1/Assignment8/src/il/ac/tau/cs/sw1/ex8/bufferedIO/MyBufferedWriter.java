package il.ac.tau.cs.sw1.ex8.bufferedIO;

import java.io.FileWriter;
import java.io.IOException;

/**************************************
 * Add your code to this class !!! *
 **************************************/

public class MyBufferedWriter implements IBufferedWriter {

	private char[] buffer;
	private FileWriter writer;
	private int used;

	public MyBufferedWriter(FileWriter fWriter, int bufferSize) {
		this.buffer = new char[bufferSize];
		this.writer = fWriter;
		this.used = 0;
	}

	@Override
	public void write(String str) throws IOException {
		int i = 0;
		while (i < str.length()) {
			if (this.used < this.buffer.length) {
				buffer[this.used] = str.charAt(i);
				i++;
				this.used++;
			}
			if (this.used == this.buffer.length) {
				this.writer.write(this.buffer);
				this.used = 0;
			}
		}
	}

	@Override
	public void close() throws IOException {
		if (used != 0)
			writer.write(buffer, 0, used);;
		this.used = 0;
		this.writer.close();
	}

}
