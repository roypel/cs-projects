package il.ac.tau.cs.sw1.ex9.starfleet;

import java.util.List;
import java.util.Set;

public class Bomber extends AbsstractBattleship{

	private static final int BASE_BOMBER_COST = 5000;
	
	private int numberOfTechnicians;
	
	public Bomber(String name, int commissionYear, float maximalSpeed, Set<CrewMember> crewMembers, List<Weapon> weapons, int numberOfTechnicians){
		super(name, commissionYear, maximalSpeed, crewMembers, weapons);
		this.numberOfTechnicians = numberOfTechnicians;
		setAnnualMaintenance();
	}

	public int getNumberOfTechnicians(){
		return this.numberOfTechnicians;
	}
	
	private void setAnnualMaintenance(){
		int weaponCost = (int) Math.round(getAnnualWeaponCost() * ((10 - this.numberOfTechnicians) / 10.0));// Including Tech discount
		setAnnualMaintenanceCost(BASE_BOMBER_COST + weaponCost);
	}
	
	@Override
	public String toString(){
		return super.toString() + System.lineSeparator() + "\tNumberOfTechnicians=" + getNumberOfTechnicians();
	}
}
