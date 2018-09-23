package il.ac.tau.cs.sw1.ex9.starfleet;

import java.util.Comparator;

public class SpaceshipComparator implements Comparator<Spaceship> {

	public int compare(Spaceship ship1, Spaceship ship2) {
		int i = Integer.compare(ship2.getFirePower(), ship1.getFirePower());
		if (i != 0)
			return i;
		i = Integer.compare(ship2.getCommissionYear(), ship1.getCommissionYear());
		if (i != 0)
			return i;
		return ship1.getName().compareTo(ship2.getName());
	}
}
