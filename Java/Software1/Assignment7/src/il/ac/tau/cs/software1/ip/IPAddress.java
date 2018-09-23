package il.ac.tau.cs.software1.ip;

public interface IPAddress {

	/**
	 * Returns a string representation of the IP address, e.g. 
       * "192.168.0.1"
	 */
	public String toString();

	/**
	 * Compares this IPAddress to the specified object
	 * @param other
	 *            the IPAddress to compare the current against
	 * @return true if both IPAddress objects represent the same 
       * IP address, false otherwise.
	 */
	public boolean equals(IPAddress other);

	/**
	 * Returns one of the four parts of the IP address. The parts 
       * are indexed from left to right. For example, in the IP 
       * address 192.168.0.1 part 0 is 192, part 1 is 168,
       * part 2 is 0 and part 3 is 1.
       * (Each part is called an octet as its representation 
       * requires 8 bits.)
	 * @param index
	 *            The index of the IP address part (0, 1, 2 or 3)
	 * @return The value of the specified part.
	 */
	public int getOctet(int index);

	/**
	* There are four classes of private networks
	* (http://en.wikipedia.org/wiki/IPv4#Private_networks)
	* 10.0.0.0 – 10.255.255.255
	* 172.16.0.0 – 172.31.255.255
	* 192.168.0.0 – 192.168.255.255
	* 169.254.0.0 – 169.254.255.255
	*
	* This query returns true if this object is a private network address
	*/
	public boolean isPrivateNetwork();


}
