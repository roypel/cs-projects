package il.ac.tau.cs.software1.predicate;

public class Big implements Predictor {

	private int value;

	public Big(int value) {
		this.value = value;
	}

	@Override
	/**
	 * Return true iff (Person)o.age > value
	 */
	public boolean test(Object o) {
		if (o.getClass() == Person.class) {
			Person person = (Person) o;
			if (person.getAge() > this.value)
				return true;
		} else {
			System.out.println("Input is not a Person");
		}
		return false;
	}

	public int getValue() {
		return this.value;
	}

	public void setValue(int value) {
		this.value = value;
	}

}
