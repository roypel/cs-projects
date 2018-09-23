package il.ac.tau.cs.software1.predicate;

public class Even implements Predictor {

	@Override
	/*
	 * (non-Javadoc)
	 * Return true iff (Person)o.age %2 == 0
	 */
	public boolean test(Object o) {
		if (o.getClass() == Person.class) {
			Person person = (Person) o;
			if (person.getAge() % 2 == 0)
				return true;
		} else {
			System.out.println("Input is not a Person");
		}
		return false;
	}

}
