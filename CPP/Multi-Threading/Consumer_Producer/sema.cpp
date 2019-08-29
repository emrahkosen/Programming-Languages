#include <iostream>
#include <cstdio>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
using namespace std;





#define N 2
#define M 1000000
int a = 0,consumercount = 0;

sem_t pr,cs;




void* consumer(void* arg)
{
  int i;
  for(i = 0; i<M +1 ; i++)
    {
      sem_wait(&cs);

        printf("The data is %d Process id is %d\n", a, getpid() );

      sem_post(&pr);


    }

  sleep(0.4);
  cout<<"\n++++++++++>  Process id of consumer is " << getpid() ;
  pthread_exit(NULL);
}






void* producer(void* arg)
{
  int i;


  for(i = 0; i < M ; i++)
    {


      sem_wait(&pr);

        a = 1+a;
        printf("\nData updated!!\n");
      sem_post(&cs);
    }



  sleep(0.4);
  printf("\n\n---------->  Process id of producer is %d \n",getpid() );
  pthread_exit(NULL);
}


int main()
{
  int i;
  pthread_t tr[N];

  sem_init(&cs,0,1);
  sem_init(&pr,0,0);

  pthread_create(&tr[0],NULL,consumer,NULL);//pta threadınızın attribute'sidir
  pthread_create(&tr[1],NULL,producer,NULL);



  for(i =0; i<N; i++)
    pthread_join(tr[i],NULL);
  printf("\n\n**********>  Process id in main is %d\n",getpid() );

    return 0;
}
