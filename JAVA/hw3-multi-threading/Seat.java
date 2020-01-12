package main;

public class Seat {
	private String NameOfSeat;
	private boolean isTaken;
	private String takenBy;
	
	public Seat(String NameOfSeat)
	{
		this.NameOfSeat = NameOfSeat;
		isTaken = false;
		takenBy = "NULL";
		takenBy = "E";
		
	}
	
	public void setisTaken(boolean bool)
	{
		isTaken = bool;
	}
	public boolean getisTaken()
	{
		return isTaken;
	}
	
	public void settakenBy(String person)
	{
		takenBy = person;
	}
	public String gettakenBy()
	{
		return takenBy;
	}
	public String getNameOfSeat()
	{
		return NameOfSeat;
	}
	
	
}
