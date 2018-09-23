package il.ac.tau.cs.software1.ip;

import java.nio.ByteBuffer;

public class IPAddressInt implements IPAddress {

	private int address;

	IPAddressInt(int address) {
		this.address = address;
	}

	@Override
	public String toString() {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.asIntBuffer().put(this.address);
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < 4; i++) {
			sb.append((int)(bb.get(i) & 0xff));
			if (i < 3)
				sb.append('.');
		}
		return sb.toString();
	}

	@Override
	public boolean equals(IPAddress other) {
		ByteBuffer bb = ByteBuffer.allocate(4);
		bb.asIntBuffer().put(this.address);
		for (int i = 0; i < 4; i++) {
			if ((int)(bb.get(i) & 0xff) != other.getOctet(i))
				return false;
		}
		return true;
	}

	@Override
	public int getOctet(int index) {
		int mask = 0xff;// Mask all but 8 right-most bits
		return (this.address >> (8 * (3 - index))) & mask;
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
