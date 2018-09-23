package il.ac.tau.cs.sw1.ex9.starfleet;

import java.util.List;
import java.util.Set;

public class CylonRaider extends AbstractSpecialFighter{
	
	private static final int BASE_RAIDER_COST = 3500;
	private static final int ENGINE_MAINTENANCE_COST = 1200;
	private static final int CREW_MAINTENANCE_COST = 500;

	public CylonRaider(String name, int commissionYear, float maximalSpeed, Set<Cylon> crewMembers,
			List<Weapon> weapons) {
		super(name, commissionYear, maximalSpeed, crewMembers, weapons, BASE_RAIDER_COST, ENGINE_MAINTENANCE_COST, CREW_MAINTENANCE_COST);
	}

}
