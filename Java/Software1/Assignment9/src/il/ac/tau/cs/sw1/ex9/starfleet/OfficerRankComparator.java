package il.ac.tau.cs.sw1.ex9.starfleet;

import java.util.Comparator;
import java.util.Map.Entry;

public class OfficerRankComparator implements Comparator<Entry<OfficerRank, Integer>>{

	public int compare(Entry<OfficerRank, Integer> entry1, Entry<OfficerRank, Integer> entry2) {
		int i = entry2.getValue().compareTo(entry1.getValue());
		if (i != 0)
			return i;
		return entry2.getKey().compareTo(entry1.getKey());
	}

}
