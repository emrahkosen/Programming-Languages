package thread;

import java.util.concurrent.Semaphore;



public class Consumer implements Runnable{
	Data d;
	Semaphore sem;
	public Consumer(Data d, Semaphore sem)
	{	this.sem = sem;
		this.d = d;
	}
	@Override
	public void run() {
		for(int i = 0; i < 1000000; i++)
		{
			try {
				sem.acquire();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
			d.data--;
			//System.out.println(d.data);
		
			sem.release();
		}
		
	}

}
