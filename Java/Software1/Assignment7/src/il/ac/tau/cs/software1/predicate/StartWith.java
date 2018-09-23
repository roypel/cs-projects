package il.ac.tau.cs.software1.predicate;

public class StartWith implements Predictor {

	private char c;

	public StartWith(char c) {
		this.c = c;
	}

	@Override
	/*
	 * (non-Javadoc)
	 * Return true iff (Person)O.name.charAt(0) == c
	 */
	public boolean test(Object o) {
		if (o.getClass() == Person.class) {
			Person person = (Person) o;
			if (person.getName().charAt(0) == this.c)
				return true;
		} else {
			System.out.println("Input is not a Person");
		}
		return false;
	}

	public char getC() {
		return this.c;
	}

	public void setC(char c) {
		this.c = c;
	}
}
