package il.ac.tau.cs.sw1.ex9.starfleet;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Set;

public class StealthCruiser extends Fighter{
	
	private static int numOfCloakingDevices = 0;
	private static final int CLOAKING_MAINTENANCE_COST = 50;
	private static int annualCloackingMaintenance = 0;
		
	public StealthCruiser(String name, int commissionYear, float maximalSpeed, Set<CrewMember> crewMembers, List<Weapon> weapons) {
		super(name, commissionYear, maximalSpeed, crewMembers, weapons);
		numOfCloakingDevices++;
		updateCloackingMaintenance();
	}

	public StealthCruiser(String name, int commissionYear, float maximalSpeed, Set<CrewMember> crewMembers){
		this(name, commissionYear, maximalSpeed, crewMembers, new ArrayList<Weapon>(Arrays.asList(new Weapon ("Laser Cannons", 10, 100))));
	}

	@Override
	public int getAnnualMaintenanceCost(){
		return super.getAnnualMaintenanceCost() + annualCloackingMaintenance;
	}
	
	private void updateCloackingMaintenance(){
		annualCloackingMaintenance = CLOAKING_MAINTENANCE_COST * numOfCloakingDevices;
	}
	
}
