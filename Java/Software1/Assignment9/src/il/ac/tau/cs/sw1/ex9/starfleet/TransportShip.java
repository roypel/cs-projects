package il.ac.tau.cs.sw1.ex9.starfleet;

import java.util.Set;

public class TransportShip extends AbstractSpaceship{
	
	private static final int BASE_TRANSPORT_COST = 3000;
	private static final int CARGO_CAPACITY_COST = 5;
	private static final int PASSANGER_CAPACITY_COST = 3;

	private int cargoCapacity;
	private int passengerCapacity;
	
	public TransportShip(String name, int commissionYear, float maximalSpeed, Set<CrewMember> crewMembers, int cargoCapacity, int passengerCapacity){
		super(name, commissionYear, maximalSpeed, crewMembers);
		this.cargoCapacity = cargoCapacity;
		this.passengerCapacity = passengerCapacity;
		setAnnualMaintenanceCost();
	}

	private void setAnnualMaintenanceCost(){
		super.setAnnualMaintenanceCost(BASE_TRANSPORT_COST + CARGO_CAPACITY_COST * this.cargoCapacity + PASSANGER_CAPACITY_COST * this.passengerCapacity);
	}
	
	@Override
	public String toString(){
		return super.toString() + System.lineSeparator() + "\tCargoCapacity=" + this.cargoCapacity + System.lineSeparator() + "\tPassengerCapacity=" + this.passengerCapacity;
	}
}
