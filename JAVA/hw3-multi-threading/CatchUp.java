package main;

import java.util.ArrayList;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class CatchUp implements Runnable
{
	public static Semaphore sem = new Semaphore(1);
	private static Lock lock = new ReentrantLock();
	private int retry;
	ArrayList<ArrayList<Seat>> seats;
	ArrayList<String> person;
	public CatchUp(ArrayList<ArrayList<Seat>> seats , ArrayList<String> person )
	{
		this.seats = seats;
		this.person = person;
		retry = 0;

	}
		
	@Override
	public void run() {
		
		while(true)
		{	retry++;
			boolean breakwhile = false;
			try {
				lock.lock();
				//sem.acquire();
					int len = person.size();
					for(int i= 1; i< len ; i++)
					{
						int row = (int)person.get(i).charAt(0) - 65;
						int col = Integer.parseInt( person.get(i).substring(1) );
						if(seats.get(row).get(col).getisTaken())
						{
							Thread.sleep(50);
							String seatOfUNSuccesfulPerson = "[";
							for(int p = 1; p < len ; p++ )
							{
								seatOfUNSuccesfulPerson = seatOfUNSuccesfulPerson + person.get(p) ;
								if(p != len - 1)
									seatOfUNSuccesfulPerson = seatOfUNSuccesfulPerson + ", ";
							}
							seatOfUNSuccesfulPerson = seatOfUNSuccesfulPerson + "]";
							Logger.LogFailedReservation(person.get(0), seatOfUNSuccesfulPerson , System.nanoTime() , "Seats are not available");
							
							/*Failed reservation*/
							breakwhile = true;
							break;
						}
						
					}
					
					
					if(breakwhile == false)
					{
						double random = Math.random()*100;
						if(random < 10)
						{
							//System.out.println("database failure for " + person.get(0));
							String seatOfUNSuccesfulPerson = "[";
							for(int p = 1; p < len  ; p++ )
							{
								seatOfUNSuccesfulPerson = seatOfUNSuccesfulPerson + person.get(p) ;
								if(p != len - 1)
									seatOfUNSuccesfulPerson = seatOfUNSuccesfulPerson + ", ";
							}
							seatOfUNSuccesfulPerson = seatOfUNSuccesfulPerson +  "]";
							
							Logger.LogDatabaseFailiure(person.get(0), seatOfUNSuccesfulPerson, System.nanoTime() ,"Failed, trying again.");
							Thread.sleep(100);
							
						}
						else
						{
							
							for(int i = 1 ; i < len; i++)
							{
								int row = (int)person.get(i).charAt(0) - 65;
								int col = Integer.parseInt( person.get(i).substring(1) );
								seats.get(row).get(col).settakenBy(person.get(0));
								seats.get(row).get(col).setisTaken(true);
								
								
							}
							String seatOfSuccesfulPerson = "[";
							for(int p = 1; p < len ; p++ )
							{
								seatOfSuccesfulPerson = seatOfSuccesfulPerson + person.get(p) ;
								if(p != len - 1)
									seatOfSuccesfulPerson = seatOfSuccesfulPerson + ", ";
							}
							seatOfSuccesfulPerson = seatOfSuccesfulPerson  + "]";
							Logger.LogSuccessfulReservation(person.get(0), seatOfSuccesfulPerson , System.nanoTime()  , "Retry No: " + retry);
							breakwhile = true;
						}
					}
				
				
				
			} catch (InterruptedException e) { e.printStackTrace(); sem.release();}
			finally {
		        lock.unlock(); // Release the lock
		      }
			//sem.release();
			if(breakwhile == true)
				break;
		}
		
	}

}
