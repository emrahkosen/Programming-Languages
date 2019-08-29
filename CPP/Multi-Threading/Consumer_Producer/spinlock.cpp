#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <atomic>
using namespace std;

#define N 2
#define M 1000000
int a = 0,consumercount = 0;



atomic<int> pro(0),cons(1);




void* consumer(void* arg)
{
  int i;
  for(i = 0; i<M +1 ; i++)
    {

      while( cons.load() <= 0 );
      --cons;
        printf("The data is %d Process id is %d\n", a, getpid() );
      pro++;


    }

  sleep(0.4);
  printf("\n\n++++++++++>  Process id of consumer is %d \n",getpid() );
  pthread_exit(NULL);
}






void* producer(void* arg)
{
  int i;


  for(i = 0; i < M ; i++)
    {


      while( pro.load() <= 0 );
      --pro;
        a = 1+a;
        printf("\nData updated!!\n");
      cons++;
    }



  sleep(0.4);
  printf("\n\n---------->  Process id of producer is %d \n",getpid() );
  pthread_exit(NULL);
}


int main()
{
  int i;
  pthread_t tr[N];


  pthread_create(&tr[0],NULL,consumer,NULL);//pta threadınızın attribute'sidir
  pthread_create(&tr[1],NULL,producer,NULL);



  for(i =0; i<N; i++)
    pthread_join(tr[i],NULL);
  printf("\n\n**********>  Process id in main is %d\n",getpid() );

    return 0;
}
