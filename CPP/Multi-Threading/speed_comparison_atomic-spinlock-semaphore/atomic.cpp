#include <iostream>
#include "stdio.h"
#include <thread>
#include <atomic>
#include <chrono>
using namespace std;



#define N 10000000

atomic<int> atomi(0);



void increment()
{

  for (size_t i = 0; i < N; i++)
  {
    ++atomi;
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
  cout << "milliseconds since start: " << elapsed.count( ) <<  " --> ";
  printf("atomic == %d\n",atomi.load() );

  return 0;
}
