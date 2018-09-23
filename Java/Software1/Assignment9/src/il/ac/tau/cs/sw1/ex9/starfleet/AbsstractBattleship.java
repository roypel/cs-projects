package il.ac.tau.cs.sw1.ex9.starfleet;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;

public abstract class AbsstractBattleship extends AbstractSpaceship{
	
	private List<Weapon> weaponList;
	
	public AbsstractBattleship(String name, int commissionYear, float maximalSpeed, Set<? extends CrewMember> crewMembers, List<Weapon> weaponList){
		super(name, commissionYear, maximalSpeed, crewMembers);
		this.weaponList = new ArrayList<>();
		this.weaponList.addAll(weaponList);
		setFirePower();
	}

	private void setFirePower(){
		int firePower = this.getFirePower();
		for (Weapon weapon : this.weaponList){
			firePower += weapon.getFirePower();
		}
		setBattleshipFirePower(firePower);
	}
	
	protected int getAnnualWeaponCost(){
		int cost = 0;
		for (Weapon weapon : this.weaponList)
			cost += weapon.getAnnualMaintenanceCost();
		return cost;
	}
	
	public List<Weapon> getWeapon(){
		return this.weaponList;
	}
	
	@Override
	public String toString(){
		return super.toString() + System.lineSeparator() + "\tWeaponArray=" +  this.weaponList.toString();
	}
}
