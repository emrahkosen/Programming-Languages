package thread;

import java.util.concurrent.Semaphore;

public class Producer implements Runnable{
	Data d;
	Semaphore sem;
	public Producer(Data d, Semaphore sem)
	{
		this.d = d;
		this.sem = sem;
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
			d.data++;
			//System.out.println("Producer increment data value: " + d.data);
			sem.release();
		}
		
	}

}
