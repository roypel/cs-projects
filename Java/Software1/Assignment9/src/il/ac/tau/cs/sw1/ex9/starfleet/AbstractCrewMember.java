package il.ac.tau.cs.sw1.ex9.starfleet;

public abstract class AbstractCrewMember implements CrewMember, Comparable<AbstractCrewMember>{
	
	private String name;
	private int age;
	private int yearsInService;

	public AbstractCrewMember(String name, int age, int yearsInService){
		this.name = name;
		this.age = age;
		this.yearsInService = yearsInService;
	}
	
	@Override
	public String getName(){
		return this.name;
	}
	
	@Override
	public int getAge(){
		return this.age;
	}
	
	@Override
	public int getYearsInService(){
		return this.yearsInService;
	}
	
	@Override
	public String toString(){
		StringBuilder sb = new StringBuilder();
		sb.append(this.getClass().getSimpleName());
		sb.append(System.lineSeparator()).append("\tName=").append(this.name);
		sb.append(System.lineSeparator()).append("\tAge=").append(this.age);
		sb.append(System.lineSeparator()).append("\tYearsInService=").append(this.yearsInService);
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
		AbstractCrewMember other = (AbstractCrewMember) obj;
		if (name == null) {
			if (other.name != null)
				return false;
		} else if (!name.equals(other.name))
			return false;
		return true;
	}
	
	@Override
	public int compareTo(AbstractCrewMember other){
		int i = Integer.compare(this.age, other.age);
		if (i != 0)
			return i;
		i = Integer.compare(this.yearsInService, other.yearsInService);
		if (i != 0)
			return i;
		return this.name.compareTo(other.name);
	}
}
