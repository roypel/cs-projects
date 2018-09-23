package il.ac.tau.cs.software1.predicate;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class Predicates implements PredicatesSet<Person> {

	private List<Person> personList = new ArrayList<Person>();

	public Predicates(List<Person> personList) {
		this.personList = personList;
	}

	@Override
	public void remove(Predictor predictor) {
		for (Iterator<Person> iter = this.personList.iterator(); iter.hasNext();) {
			if (predictor.test(iter.next())) {
				iter.remove();
			}
		}
	}

	@Override
	public void retain(Predictor predictor) {
		for (Iterator<Person> iter = this.personList.iterator(); iter.hasNext();) {
			if (!(predictor.test(iter.next()))) {
				iter.remove();
			}
		}
	}

	@Override
	public List<Person> collect(Predictor predictor) {
		List<Person> truePredictor = new ArrayList<Person>();
		for (Person person : this.personList) {
			if (predictor.test(person))
				truePredictor.add(person);
		}
		return truePredictor;
	}

	@Override
	public int find(Predictor predictor) {
		for (Person person : this.personList)
			if (predictor.test(person))
				return this.personList.indexOf(person);
		return -1;
	}

	public List<Person> getPersonList() {
		return this.personList;
	}

	public void setPersonList(List<Person> personList) {
		this.personList = personList;
	}
}
