package il.ac.tau.cs.software1.ip;

public class IPAddressFactory {

	public static IPAddress createAddress(String ip) {
		return new IPAddressString(ip);
	}

	public static IPAddress createAddress(short[] ip) {
		return new IPAddressShort(ip);
	}

	public static IPAddress createAddress(int ip) {
		return new IPAddressInt(ip);
	}
}