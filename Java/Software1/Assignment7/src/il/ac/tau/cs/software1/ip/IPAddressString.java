package il.ac.tau.cs.software1.ip;

public class IPAddressString implements IPAddress {

	private String address;

	IPAddressString(String address) {
		this.address = address;
	}

	@Override
	public String toString() {
		return this.address;
	}

	@Override
	public boolean equals(IPAddress other) {
		for (int i = 0; i < 4; i++) {
			if (this.getOctet(i) != other.getOctet(i))
				return false;
		}
		return true;
	}

	@Override
	public int getOctet(int index) {
		String[] addressArray = this.address.split("\\.");
		return Integer.parseInt(addressArray[index]);
	}

	@Override
	public boolean isPrivateNetwork() {
		int firstByte = this.getOctet(0);
		if (firstByte == 10)
			return true;
		int secondByte = this.getOctet(1);
		if (firstByte == 172)
			if ((secondByte >= 16) && (secondByte <= 31))
				return true;
		if (firstByte == 192)
			if (secondByte == 168)
				return true;
		if (firstByte == 169)
			if (secondByte == 254)
				return true;
		return false;
	}

}
