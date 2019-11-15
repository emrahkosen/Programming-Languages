package thread;

import java.util.concurrent.Semaphore;

public class Threads {
	public static void main(String[] args) throws InterruptedException
	{
		Data d = new Data(10);
		Semaphore sem = new Semaphore(1);
		Consumer c = new Consumer(d , sem); // d objesini herkes paylasıyor yanı referansını tutuyor p ve c
		Producer p = new Producer(d, sem);
		Thread tc = new Thread(c);
		Thread tp = new Thread(p);
		tc.start();
		tp.start();
		
		tc.join();
		tp.join();
		System.out.println(d.data);
	}

}
