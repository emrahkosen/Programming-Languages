#include <iostream>
#include "stdio.h"
#include <thread>
#include <atomic>
#include <chrono>
using namespace std;



#define N 10000000

int nonatomic = 0;
atomic_flag flag(ATOMIC_FLAG_INIT);

void lock()
{
  while(flag.test_and_set())
    ;
}

void unlock()
{
  flag.clear();
}


void increment()
{

  for (size_t i = 0; i < N; i++)
  {
    lock();

      ++nonatomic;

    unlock();
  }

}


int main()
{
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

  auto elapsed = chrono::duration_cast<std::chrono::milliseconds>(chrono::steady_clock::now( ) - start );
  cout << "milliseconds since start: " << elapsed.count( ) << " --> ";
  printf("nonatomic == %d\n",nonatomic );

  return 0;
}
