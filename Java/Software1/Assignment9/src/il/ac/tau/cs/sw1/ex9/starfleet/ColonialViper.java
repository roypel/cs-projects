package il.ac.tau.cs.sw1.ex9.starfleet;

import java.util.List;
import java.util.Set;

public class ColonialViper extends AbstractSpecialFighter{
	
	private static final int BASE_VIPER_COST = 4000;
	private static final int ENGINE_MAINTENANCE_COST = 500;
	private static final int CREW_MAINTENANCE_COST = 500;

	public ColonialViper(String name, int commissionYear, float maximalSpeed, Set<CrewWoman> crewMembers,
			List<Weapon> weapons) {
		super(name, commissionYear, maximalSpeed, crewMembers, weapons, BASE_VIPER_COST, ENGINE_MAINTENANCE_COST, CREW_MAINTENANCE_COST);
	}
	
}
