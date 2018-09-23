package il.ac.tau.cs.sw1.ex10.bus_tickets;

public class Main {
	
	private final static float BASE_PRICE_PER_DAY = 2.0f;

	public enum BusTicket {
		DAILY(1, 0.0, "24 hours"),
		WEEKLY(7, 0.05, "7 days"),
		MONTHLY(30, 0.10, "30 days"),
		QUARTERLY(90, 0.20, "3 months"),
		YEARLY(365, 0.35, "1 year");
		
		private int duration;
		private double price;
		private String description;
		
		BusTicket(int duration, double discount, String description){
			this.duration = duration;
			this.price = duration * BASE_PRICE_PER_DAY * (1 - discount);
			this.description = "Ticket valid for " + description;
		}
		
		private int duration(){
			return this.duration;
		}
		
		private double price(){
			return this.price;
		}
		
		private String description(){
			return this.description;
		}
	}
	
	public static void main(String [] args) {
		System.out.println("Avialable tickets:");
		for (BusTicket ticket: BusTicket.values()) {
			System.out.println(
					String.format("Name: %10s \t Validity: %3d days "
							+ "\t Price: %3.2f NIS \t Description: %s", 
							ticket, ticket.duration(), ticket.price(), ticket.description()));
		}
	}
}