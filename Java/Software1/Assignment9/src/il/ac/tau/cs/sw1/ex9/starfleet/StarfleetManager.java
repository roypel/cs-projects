package il.ac.tau.cs.sw1.ex9.starfleet;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class StarfleetManager {

	/**
	 * Returns a list containing string representation of all fleet ships, sorted in descending order by
	 * fire power, and then in ascending order by commission year
	 */
	public static List<String> getShipDescriptionsSortedByFirePowerAndCommissionYear (Collection<Spaceship> fleet) {
		List<Spaceship> fleetList = new ArrayList<>(fleet);
		Collections.sort(fleetList, new SpaceshipComparator());
		List<String> fleetString = new ArrayList<>();
		for (Spaceship ship : fleetList){
			fleetString.add(ship.toString());
		}
		return fleetString;
	}

	/**
	 * Returns a map containing ship type names as keys (the class name) and the number of instances created for each type as values
	 */
	public static Map<String, Integer> getInstanceNumberPerClass(Collection<Spaceship> fleet) {
		HashMap<String, Integer> shipTypeMap = new HashMap<>();
		String shipClass;
		for (Spaceship ship : fleet){
			shipClass = ship.getClass().getSimpleName();
			if (shipTypeMap.containsKey(shipClass))
				shipTypeMap.put(shipClass, shipTypeMap.get(shipClass) + 1);
			else
				shipTypeMap.put(shipClass, 1);
		}
		return shipTypeMap;
	}


	/**
	 * Returns the total annual maintenance cost of the fleet (which is the sum of maintenance costs of all the fleet's ships)
	 */
	public static int getTotalMaintenanceCost (Collection<Spaceship> fleet) {
		int totalMaintenanceCost = 0;
		for (Spaceship ship : fleet){
			totalMaintenanceCost += ship.getAnnualMaintenanceCost();
		}
		return totalMaintenanceCost;

	}


	/**
	 * Returns a set containing the names of all the fleet's weapons installed on any ship
	 */
	public static Set<String> getFleetWeaponNames(Collection<Spaceship> fleet) {
		Set<String> weaponSet = new HashSet<>();
		AbsstractBattleship battleShip;
		for (Spaceship ship : fleet){
			if (!ship.getClass().equals(TransportShip.class)){
				battleShip = (AbsstractBattleship)ship;
				for (Weapon weapon : battleShip.getWeapon()){
					if (!weaponSet.contains(weapon.getName()))
						weaponSet.add(weapon.getName());
				}
			}
		}
		return weaponSet;

	}

	/*
	 * Returns the total number of crew-members serving on board of the given fleet's ships.
	 */
	public static int getTotalNumberOfFleetCrewMembers(Collection<Spaceship> fleet) {
		int totalCrewMembers = 0;
		for (Spaceship ship : fleet){
			totalCrewMembers += ship.getCrewMembers().size();
		}
		return totalCrewMembers;
	}

	/*
	 * Returns the average age of all officers serving on board of the given fleet's ships. 
	 */
	public static float getAverageAgeOfFleetOfficers(Collection<Spaceship> fleet) {
		float averageOfficerAge = 0;
		int numberOfOfficers = 0;
		for (Spaceship ship : fleet){
			for (CrewMember member : ship.getCrewMembers()){
				if (member.getClass().equals(Officer.class)){
					averageOfficerAge += member.getAge();
					numberOfOfficers++;
				}
			}
		}
		return averageOfficerAge/numberOfOfficers;
	}

	/*
	 * Returns a map mapping the highest ranking officer on each ship (as keys), to his ship (as values).
	 */
	public static Map<Officer, Spaceship> getHighestRankingOfficerPerShip(Collection<Spaceship> fleet) {
		HashMap<Officer, Spaceship> officerToShip = new HashMap<>();
		OfficerRank maxRank;
		Officer currOfficer;
		Officer maxOfficer;
		for (Spaceship ship : fleet){
			maxRank = OfficerRank.Ensign;
			maxOfficer = null;
			for (CrewMember member : ship.getCrewMembers()){
				if (member.getClass().equals(Officer.class)){
					currOfficer = (Officer)member;
					if (currOfficer.getRank().compareTo(maxRank) >= 0){
						maxOfficer = currOfficer;
						maxRank = maxOfficer.getRank();
					}
				}
			}
			if (maxOfficer != null)
				officerToShip.put(maxOfficer, ship);
		}
		return officerToShip;

	}

	/*
	 * Returns a List of entries representing ranks and their occurrences.
	 * Each entry represents a pair composed of an officer rank, and the number of its occurrences among starfleet personnel.
	 * The returned list is sorted descendingly based on the number of occurrences.
	 */
	public static List<Map.Entry<OfficerRank, Integer>> getOfficerRanksSortedByPopularity(Collection<Spaceship> fleet) {
		List<Map.Entry<OfficerRank, Integer>> rankList = new ArrayList<>();
		Map<OfficerRank, Integer> rankToAppearance = new HashMap<>();
		Officer currOfficer;
		for (Spaceship ship : fleet){
			for (CrewMember member : ship.getCrewMembers()){
				if (member.getClass().equals(Officer.class)){
					currOfficer = (Officer)member;
					if (rankToAppearance.containsKey(currOfficer.getRank()))
						rankToAppearance.put(currOfficer.getRank(), rankToAppearance.get(currOfficer.getRank()) + 1);
					else
						rankToAppearance.put(currOfficer.getRank(), 1);
				}
			}
		}
		rankList.addAll(rankToAppearance.entrySet());
		Collections.sort(rankList, new OfficerRankComparator());
		return rankList;
	}

}
