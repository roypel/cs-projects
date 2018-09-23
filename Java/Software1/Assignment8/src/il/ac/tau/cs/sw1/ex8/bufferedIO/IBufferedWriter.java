package il.ac.tau.cs.sw1.ex8.bufferedIO;

import java.io.Closeable;
import java.io.IOException;

public interface IBufferedWriter extends Closeable{

	public void write(String str) throws IOException;

}
