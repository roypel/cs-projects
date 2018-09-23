package il.ac.tau.cs.sw1.ex9.starfleet;

import java.util.HashSet;
import java.util.Set;

public abstract class AbstractSpaceship implements Spaceship{
	
	private String name;
	private int commissionYear;
	private float maximalSpeed;
	private int firePower;
	private Set<CrewMember> crewMembers;
	private int annualMaintenanceCost;
	
	public AbstractSpaceship(String name, int commissionYear, float maximalSpeed, Set<? extends CrewMember> crewMembers){
		this.name = name;
		this.commissionYear = commissionYear;
		this.maximalSpeed = maximalSpeed;
		this.firePower = 10;
		this.crewMembers = new HashSet<>();
		for (CrewMember member : crewMembers)
			if (!this.crewMembers.contains(member))
				this.crewMembers.add(member);
	}
	
	@Override
	public String getName(){
		return this.name;
	}

	@Override
	public int getCommissionYear() {
		return this.commissionYear;
	}

	@Override
	public float getMaximalSpeed() {
		return this.maximalSpeed;
	}

	@Override
	public int getFirePower() {
		return this.firePower;
	}

	@Override
	public Set<? extends CrewMember> getCrewMembers() {
		return this.crewMembers;
	}

	@Override
	public int getAnnualMaintenanceCost() {
		return this.annualMaintenanceCost;
	}
	
	protected void setAnnualMaintenanceCost(int annualMaintenanceCost){
		this.annualMaintenanceCost = annualMaintenanceCost;
	}
	
	protected void setBattleshipFirePower(int firePower){
		this.firePower = firePower;
	}

	@Override
	public String toString(){
		StringBuilder sb = new StringBuilder();
		sb.append(this.getClass().getSimpleName());
		sb.append(System.lineSeparator()).append("\tName=").append(this.name);
		sb.append(System.lineSeparator()).append("\tCommissionYear=").append(this.commissionYear);
		sb.append(System.lineSeparator()).append("\tMaximalSpeed=").append(this.maximalSpeed);
		sb.append(System.lineSeparator()).append("\tFirePower=").append(this.firePower);
		sb.append(System.lineSeparator()).append("\tCrewMembers=").append(this.crewMembers.size());
		if (this.getClass() != StealthCruiser.class)
			sb.append(System.lineSeparator()).append("\tAnnualMaintenanceCost=").append(this.annualMaintenanceCost);
		else
			sb.append(System.lineSeparator()).append("\tAnnualMaintenanceCost=").append(this.getAnnualMaintenanceCost());
		return sb.toString();
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((name == null) ? 0 : name.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		AbstractSpaceship other = (AbstractSpaceship) obj;
		if (name == null) {
			if (other.name != null)
				return false;
		} else if (!name.equals(other.name))
			return false;
		return true;
	}
}
