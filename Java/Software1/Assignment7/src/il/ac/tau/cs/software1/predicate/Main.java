package il.ac.tau.cs.software1.predicate;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Scanner;

public class Main {

	private static Scanner scanner;

	public static List<Person> getPersonFromUser() {
		List<Person> personList = new ArrayList<Person>();
		numberOfPersons();
		int personsNum = 0;
		int age;
		String name;
		boolean validInput = false;
		String input = scanner.nextLine();
		// Check if the input is a valid Integer
		while (!validInput) {
			if (input.charAt(0) == 'X')
				return null;
			validInput = true;
			if (isInputValid(input, 'd')) {
				personsNum = Integer.parseInt(input);
				if (personsNum <= 0) {
					validInput = false;
					input = newInput('n');
				}
			} else {
				validInput = false;
				input = newInput('n');
			}
		}
		// Read user input for Persons
		for (int i = 0; i < personsNum; i++) {
			enterAge();
			age = Integer.parseInt(scanner.nextLine());
			enterName();
			name = scanner.nextLine();
			personList.add(new Person(age, name));
		}
		printList(personList);
		return personList;
	}

	public static Predictor getPredictorFromUsers() {
		boolean validInput = false;
		printPredictorList();
		String input = scanner.nextLine();
		char predictor = '0';
		while (!validInput) {
			validInput = true;
			if (isInputValid(input, 'p')) {
				predictor = input.charAt(0);
			} else {
				validInput = false;
				input = newInput('p');
			}
		}
		if (predictor == 'E')
			return new Even();
		if (predictor == 'S') {
			inputChar();
			input = scanner.nextLine();
			return new StartWith(input.charAt(0));
		}
		inputNumber();
		input = scanner.nextLine();
		return new Big(Integer.parseInt(input));
	}

	public static List<Person> apply(List<Person> lst, Predictor p) {
		String input = "";
		Predicates predicate = new Predicates(lst);
		while (!(input.equals("N"))) {
			printApplyList();
			input = scanner.nextLine();
			while (input.length() != 1) {//Ensure input is only one character
				input = newInput('a');
			}
			switch (input.charAt(0)) {//Check which action to perform
			case 'R':
				predicate.remove(p);
				printResult(lst);
				break;
			case 'E':
				predicate.retain(p);
				printResult(lst);
				break;
			case 'C':
				lst = predicate.collect(p);
				predicate = new Predicates(lst);
				printResult(lst);
				break;
			case 'F':
				System.out.println("The result is: " + predicate.find(p));
				break;
			case 'N':
				break;
			default://If not a recognized action
				unknownCommand();
				break;
			}
		}
		return getPersonFromUser();
	}

	public static void run() {
		scanner = new Scanner(System.in);
		List<Person> personList = getPersonFromUser();
		Predictor predictor;
		while (personList != null) {
			predictor = getPredictorFromUsers();
			personList = apply(personList, predictor);
		}
		scanner.close();
		return;
	}

	public static void main(String[] args) {
		run();
	}

	private static boolean isInputValid(String input, char type) {
		if (type == 'd') {// Checks if the string is only digits
			for (char c : input.toCharArray()) {
				if ((c < '0') || (c > '9'))
					return false;
			}
		}
		if (type == 'c') {// Checks if the string is only letters
			for (char c : input.toCharArray()) {
				if (((c < 'a') && (c > 'z')) || ((c < 'A') && (c > 'Z')))
					return false;
			}
		}
		if (type == 'p') {// Checks if the string is a recognized predictor
			if (input.length() != 1)
				return false;
			char c = input.charAt(0);
			if ((c != 'E') && (c != 'B') && (c != 'S'))
				return false;
		}
		return true;
	}

	private static String newInput(char type) {
		unknownCommand();
		if (type == 'n')
			numberOfPersons();
		if (type == 'p')
			printPredictorList();
		if (type == 'a')
			printApplyList();
		return scanner.nextLine();
	}

	/*************************************************************/
	/********************** Messages Block **********************/
	/*************************************************************/

	public static void numberOfPersons() {
		System.out.println("Please choose number of persons (or X for exit):");
	}

	public static void unknownCommand() {
		System.out.println("Unknown command. Please try again.");
	}

	public static void enterAge() {
		System.out.print("Please enter age: ");
	}

	public static void enterName() {
		System.out.print("Please enter name: ");
	}

	public static void printList(List<Person> personList) {
		System.out.println("Your list is: " + printPersonList(personList));
	}

	public static void printPredictorList() {
		System.out.println("Please choose Predictor:");
		System.out.println("E - Even");
		System.out.println("B - Big");
		System.out.println("S - StartWith");
	}

	public static void inputNumber() {
		System.out.println("Please enter a number to compare with:");
	}

	public static void inputChar() {
		System.out.println("Please enter a char to compare:");
	}

	public static void printApplyList() {
		System.out.println("What would you like to do:");
		System.out.println("R - Remove");
		System.out.println("E - Retain");
		System.out.println("C - Collect");
		System.out.println("F - Find");
		System.out.println("N - Insert a new list");
	}

	public static void printResult(List<Person> personList) {
		System.out.println("The result is: " + printPersonList(personList));
	}

	public static String printPersonList(List<Person> personList) {
		StringBuilder sb = new StringBuilder();
		sb.append('[');
		for (Iterator<Person> iter = personList.iterator(); iter.hasNext();) {
			sb.append(iter.next().toString());
			if (iter.hasNext())
				sb.append(',');
		}
		sb.append(']');
		return sb.toString();
	}
}
