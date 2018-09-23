package il.ac.tau.cs.sw1.ex9.starfleet;

import java.util.List;
import java.util.Set;

public class Fighter extends AbstractLightBattleship{
	
	private static final int BASE_FIGHTER_COST = 2500;
	private static final int ENGINE_MAINTENANCE_COST = 1000;
	
	public Fighter(String name, int commissionYear, float maximalSpeed, Set<CrewMember> crewMembers, List<Weapon> weapons){
		super(name, commissionYear, maximalSpeed, crewMembers, weapons, BASE_FIGHTER_COST, ENGINE_MAINTENANCE_COST);
	}
}
