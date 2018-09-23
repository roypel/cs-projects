package il.ac.tau.cs.software1.ip;

public class IPAddressShort implements IPAddress {

	private short[] address;

	IPAddressShort(short[] address) {
		this.address = new short[4];
		for (int i = 0; i < address.length; i++)
			this.address[i] = address[i];
	}

	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < this.address.length; i++){
			sb.append(this.address[i]);
			if (i != this.address.length-1)
				sb.append('.');
		}
		return sb.toString();
	}

	@Override
	public boolean equals(IPAddress other) {
		for (int i = 0; i < this.address.length; i++){
			if (this.address[i] != other.getOctet(i))
				return false;
		}
		return true;
	}

	@Override
	public int getOctet(int index) {
		return this.address[index];
	}

	@Override
	public boolean isPrivateNetwork(){
		if (this.address[0] == 10)
			return true;
		if (this.address[0] == 172)
			if ((this.address[1] >= 16) && (this.address[1] <= 31))
				return true;
		if ((this.address[0] == 192) && (this.address[1] == 168))
			return true;
		if ((this.address[0] == 169) && (this.address[1] == 254))
			return true;
		return false;
	}
	
}
