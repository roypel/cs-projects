package il.ac.tau.cs.software1.ip;

public class TestIPAddress {

	public static void main(String[] args) {
		int address1 = -1062731775; // 192.168.0.1
		short[] address2 = { 10, 1, 255, 1 }; // 10.1.255.1

		IPAddress ip1 = IPAddressFactory.createAddress(address1);
		IPAddress ip2 = IPAddressFactory.createAddress(address2);
		IPAddress ip3 = IPAddressFactory.createAddress("127.0.0.1");

		for (int i = 0; i < 4; i++) {
			System.out.println(ip1.getOctet(i));
		}

		System.out.println("equals: " + ip1.equals(ip2));// False
		System.out.println("Is private Network: " + ip1.isPrivateNetwork());// True

		// ***Custom Tests***

		int address3 = -1407924209; // 172.20.200.15
		short[] address4 = { 172, 20, 200, 15 };
		int address5 = -1442931958; // 169.254.155.10
		short[] address6 = { 169, 254, 155, 9 };
		int address7 = 252909859; // 15.19.25.35
		short[] address8 = { 16, 19, 25, 35 };

		IPAddress ip4 = IPAddressFactory.createAddress(address3);
		IPAddress ip5 = IPAddressFactory.createAddress(address4);
		IPAddress ip6 = IPAddressFactory.createAddress("172.20.200.15");

		System.out.println("equals: " + ip4.equals(ip5));// True
		System.out.println("equals: " + ip5.equals(ip6));// True
		System.out.println("equals: " + ip6.equals(ip4));// True

		System.out.println("equals: " + ip3.equals(ip4));// False

		System.out.println("Is private Network: " + ip4.isPrivateNetwork());// True
		System.out.println("Is private Network: " + ip5.isPrivateNetwork());// True
		System.out.println("Is private Network: " + ip6.isPrivateNetwork());// True

		ip4 = IPAddressFactory.createAddress(address5);
		ip5 = IPAddressFactory.createAddress(address6);
		ip6 = IPAddressFactory.createAddress("10.15.0.255");

		System.out.println("equals: " + ip4.equals(ip5));// False
		System.out.println("equals: " + ip5.equals(ip6));// False
		System.out.println("equals: " + ip6.equals(ip4));// False

		System.out.println("Is private Network: " + ip4.isPrivateNetwork());// True
		System.out.println("Is private Network: " + ip5.isPrivateNetwork());// True
		System.out.println("Is private Network: " + ip6.isPrivateNetwork());// True

		ip4 = IPAddressFactory.createAddress(address7);
		ip5 = IPAddressFactory.createAddress(address8);
		ip6 = IPAddressFactory.createAddress("22.255.0.255");

		for (int i = 0; i < 4; i++) {
			System.out.println(ip4.getOctet(i));
		}
		System.out.println(ip4);

		for (int i = 0; i < 4; i++) {
			System.out.println(ip5.getOctet(i));
		}
		System.out.println(ip5);

		for (int i = 0; i < 4; i++) {
			System.out.println(ip6.getOctet(i));
		}
		System.out.println(ip6);
	}
}
