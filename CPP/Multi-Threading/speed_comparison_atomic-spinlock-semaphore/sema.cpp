#include <iostream>
#include "stdio.h"
#include <thread>
#include <semaphore.h>
#include <atomic>
#include <chrono>
using namespace std;



#define N 10000000
sem_t sem;

int nonatomic = 0;
atomic<bool> mutex(true);


void lock()
{
  while(mutex.load() == false)
    ;
  mutex = false;
}

void unlock()
{
  mutex = true;
}


void increment()
{

  for (size_t i = 0; i < N; i++)
  {
    sem_wait(&sem);
  //    std::cout << "\n/* message */" << '\n';
      ++nonatomic;
    sem_post(&sem);
    unlock();
  }

}


int main()
{
  sem_init(&sem,0,1);
  auto start = chrono::steady_clock::now( );

  thread t1(increment);
  thread t2(increment);
  thread t3(increment);
  thread t4(increment);
  thread t5(increment);
  thread t6(increment);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  sem_destroy(&sem);

  auto elapsed = chrono::duration_cast<std::chrono::milliseconds>(chrono::steady_clock::now( ) - start );
  cout << "milliseconds since start: " << elapsed.count( ) <<  " --> ";
  printf("nonatomic == %d\n",nonatomic );

  return 0;
}
