package il.ac.tau.cs.sw1.ex9.starfleet;

import java.util.List;
import java.util.Set;

public abstract class AbstractLightBattleship extends AbsstractBattleship {

	private int baseCost;
	private int engineMaintenanceCost;
	
	public AbstractLightBattleship(String name, int commissionYear, float maximalSpeed, Set<? extends CrewMember> crewMembers, List<Weapon> weaponList, int baseCost, int engineMaintenanceCost) {
		super(name, commissionYear, maximalSpeed, crewMembers, weaponList);
		this.baseCost = baseCost;
		this.engineMaintenanceCost = engineMaintenanceCost;
		setAnnualMaintenance();
	}
		
	private void setAnnualMaintenance(){
		setAnnualMaintenanceCost(baseCost + getAnnualWeaponCost() + Math.round(engineMaintenanceCost * this.getMaximalSpeed()));
	}
}
