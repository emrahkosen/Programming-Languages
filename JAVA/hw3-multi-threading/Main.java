package main;



import java.util.ArrayList;
import java.util.Scanner;

public class Main 
{
	
	public static void set(ArrayList<ArrayList<Seat>> s)
	{
		s.get(0).get(0).setisTaken(true);
		s.get(1).get(0).setisTaken(true);
	}

	
	
	public static void main(String[] args) throws InterruptedException
	{
		
		int N,M;
		Scanner scanner = new Scanner(System.in);
		String twoInt = scanner.nextLine();
		String[] TwoInt = twoInt.split(" ");
		N = Integer.parseInt(TwoInt[0]);
		M = Integer.parseInt(TwoInt[1]);
		String ks = scanner.nextLine();
		int k = Integer.parseInt(ks);
		
	
		ArrayList<ArrayList<String>> users = new ArrayList<>(k);;
		for(int i = 0; i < k; i++)
		{
			users.add(new ArrayList<String>());
			
	        String line = scanner.nextLine();
	        String[] list = line.split(" ");

	        for(int s = 0;s < list.length; s++ )
	        {
	        	users.get(i).add(list[s]);
	        }
			/*
			for(int j = 0; j < 4 ; j++)
			{
				list[i][j] = scanner.next();
			}
			*/
			
		}
		scanner.close();
		/*
		System.out.println("N: " + N + ",  M: " + M);
		System.out.println("k is: " + k);
		for(ArrayList<String> i : users)
		{
			for(String j : i)
				System.out.printf(j + " ");
			System.out.println(" ");
		}
		
		*/
		
	

		/*
		String a = "A1B2";
		char character = a.charAt(0);    
		int ascii = (int) character;
		System.out.println(ascii);
		character = a.charAt(2);    
		ascii = (int) character;
		System.out.println(ascii);
		*/
		ArrayList<ArrayList<Seat>> seats = new ArrayList<>(N);
		for(int n = 0; n < N; n++)
		{
			seats.add(new ArrayList<Seat>());
			
			for(int m = 0; m < M ; m++)
			{
				String para = (char)(65 + n) + Integer.toString(m);
				seats.get(n).add(new Seat(para ));
			}
		}
		
		ArrayList<CatchUp> catchup = new ArrayList<>(k);
		Logger.InitLogger();/* time initilize  */
		
		for(int i = 0 ; i< k; i++)
		{
			catchup.add(new CatchUp(seats,users.get(i)));
		}
		ArrayList<Thread> threads = new ArrayList<>(k);
		for(int i = 0 ; i< k; i++)
		{
			threads.add(new Thread(catchup.get(i)));
		}
	
		for(int i = 0 ; i< k; i++)
		{
			threads.get(i).start();
		}
		for(int i = 0 ; i< k; i++)
		{
			threads.get(i).join();
		//	System.out.println(i + "'th thread is joined!");
		}
		
		
		
		
		
		for(int i = 0; i<N; i++)
		{
		    for(int j = 0; j<M; j++)
		    {
		    	if(seats.get(i).get(j).getisTaken())
		    		System.out.printf( "T:%-8s", seats.get(i).get(j).gettakenBy() ) ;
		    	else
		    		System.out.printf("E:%8s"," ");
		    }
		    System.out.println();
		}
		
		
	}


}
