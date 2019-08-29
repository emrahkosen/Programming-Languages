#include <iostream>
#include <thread>
#include <mutex>
#include "stdio.h"
using namespace std;

std::mutex m1;
int buffer = 0;


void incr(int num)
{
  for (size_t i = 0; i < 1000000; i++)
  {
    lock_guard<mutex> lock(m1);
    buffer += 1;

  }
  printf("%d is finished\n",num );
}



int main()
{
  std::thread t1(incr,1);
  std::thread t2(incr,2);

  t2.join();
  t1.join();


  printf("buffer is %d\n",buffer );

  return 0;
}
