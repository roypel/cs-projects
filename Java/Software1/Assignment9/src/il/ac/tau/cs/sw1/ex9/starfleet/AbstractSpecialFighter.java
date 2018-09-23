package il.ac.tau.cs.sw1.ex9.starfleet;

import java.util.List;
import java.util.Set;

public abstract class AbstractSpecialFighter extends AbstractLightBattleship {

private int crewCost;
	
	public AbstractSpecialFighter(String name, int commissionYear, float maximalSpeed, Set<? extends CrewMember> crewMembers, List<Weapon> weaponList, int baseCost, int engineMaintenanceCost, int crewCost) {
		super(name, commissionYear, maximalSpeed, crewMembers, weaponList, baseCost, engineMaintenanceCost);
		this.crewCost = crewCost;
		setAnnualMaintenance();
	}
		
	private void setAnnualMaintenance(){
		setAnnualMaintenanceCost(this.getAnnualMaintenanceCost() + this.crewCost * this.getCrewMembers().size());
	}
}
