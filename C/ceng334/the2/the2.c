#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include "writeOutput.c"
#include <time.h>
#include <assert.h>
#include <errno.h>
#include <signal.h>




/*
3
5 4 1 10
5 4 0 10
5 4 2 10
1
5
2
5 4 0
5 4 1
1
5 4
*/



struct MinerInfo *miners;
int *mineractive;
int Quittrans = 0; //eger bu nMines e eşit olursa tranporterler while den çıkar
pthread_t  *MinerThread;
pthread_mutex_t *Minertmutex;
int *isMinertmutexLock;
unsigned int **mProp;
unsigned int **tProp;
unsigned int **siProp;
unsigned int **fProp;
struct TransporterInfo *transporters;

pthread_t  *transThread;


struct SmelterInfo *smelters;
pthread_t  *smelterThread;
pthread_mutex_t *smeltertmutex;
unsigned int *isSmeltertmutexLock;
int *smelteractive;
int ThreadLocked = 0;//thread in lock oldugunu gösteriyor
struct FoundryInfo *foundries;
pthread_t  *foundryThread;
pthread_mutex_t *foundrytmutex;
int reti,i,j= 0,k,boyut = 300,nMines,nTrans,nsimul,nFound;
unsigned int *isFoundrytmutexLock;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int *foundryactive;

int availableSimulterCopper = 0;
int availableCoalFoundry = 0;
int availableIronSmulter = 0;
int availableIRONFoundry = 0;
int totalcoalcapacity = 0;
int ironinminers = 0;
int BreakCoal = 0;
int coaltranswait = 0;


sem_t *minersmutexsem;
sem_t *smeltermutexsem;
sem_t *foundrymutexsem;
sem_t Transportmutex;
sem_t CopperTransmutex;
sem_t IronTransmutex;
sem_t CoalTransmutex;





void *minerFun(void *arg)
{
  int *val_p = (int *) arg; //pthread_create(&threadArray, NULL, minerFun, mProp);
  unsigned int ID = val_p[0];
  OreType oretype;
  unsigned int interval = val_p[1]; //representing the production and wait interval of the miner
  unsigned int totalore = val_p[4];
  unsigned int capacity = val_p[2];
  unsigned int CurrentOreCount = 0;
  if(val_p[3] == 0)
    {
      ironinminers += totalore;
      oretype = IRON;
    }
  else if(val_p[3] == 1)
      oretype = COPPER;
  else
      oretype = COAL;

  mineractive[ID] = 1;   //ID numaralı miner aktif oldu
  isMinertmutexLock[ID] = 0;
  FillMinerInfo(&miners[ID], ID+1 ,oretype,capacity,CurrentOreCount);
  WriteOutput(&miners[ID], NULL, NULL, NULL, MINER_CREATED);


  while( totalore > 0  )
  {







    if(miners[ID].capacity <=  miners[ID].current_count)
        {
          isMinertmutexLock[ID] += 1;
          sem_wait(&minersmutexsem[ID]);//Transporter birtane alan boşaltana kadar bekler ve transporter de release yapacak.
          if(isMinertmutexLock[ID])
            break;
        }


        if(miners[ID].capacity <=  miners[ID].current_count)
          break;



    pthread_mutex_lock(&Minertmutex[ID]);//wait
        WriteOutput(&miners[ID], NULL, NULL, NULL, MINER_STARTED);
        usleep(interval);                                            //sleep Interval

                miners[ID].current_count = miners[ID].current_count + 1;
                totalore--;
                WriteOutput(&miners[ID], NULL, NULL, NULL, MINER_FINISHED);


        usleep(interval); //sleep for next round
    pthread_mutex_unlock(&Minertmutex[ID]);//signal




            sem_post(&Transportmutex);//unlock transporters Transportmutex






  }

  sem_post(&Transportmutex);//unlock transporters Transportmutex
  sem_post(&Transportmutex);//unlock transporters Transportmutex
  mineractive[ID] = 0;   //ID numaralı miner pasif oldu
  FillMinerInfo(&miners[ID], ID + 1,oretype,capacity,miners[ID].current_count);


  WriteOutput(&miners[ID], NULL, NULL, NULL, MINER_STOPPED);

}
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////






void transMiner(int *val_p)
{
//  int *val_p = (int *) arg;
  unsigned int ID = val_p[0];
  unsigned int Interval = val_p[1];
  unsigned int MinerID = val_p[2];
  FillTransporterInfo(&transporters[ID], ID + 1 , &(miners[MinerID].oreType) );

  pthread_mutex_lock(&Minertmutex[MinerID]);//signal
      WriteOutput(&miners[MinerID], &transporters[ID], NULL, NULL,TRANSPORTER_TRAVEL);
      usleep(Interval);




                miners[MinerID].current_count = miners[MinerID].current_count - 1;

                WriteOutput(&miners[MinerID], &transporters[ID], NULL, NULL,TRANSPORTER_TAKE_ORE);

                if( miners[MinerID].oreType == IRON)
                {
                  ironinminers--;
                }



                if(isMinertmutexLock[MinerID])
                  {
                    isMinertmutexLock[MinerID] -= 1;
                    if(isMinertmutexLock[MinerID] <= 0 )
                      sem_post(&minersmutexsem[MinerID]);


                  }



      usleep(Interval);
  pthread_mutex_unlock(&Minertmutex[MinerID]);//signal



}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////






void transSmerter(int *val_p)
{
//  int *val_p = (int *) arg;
  unsigned int ID = val_p[0];
  unsigned int Interval = val_p[1];
  unsigned int SmelterID = val_p[2];
  OreType *CarriedOre = NULL;

  FillTransporterInfo(&transporters[ID], ID + 1 , &(smelters[SmelterID].oreType) );



  pthread_mutex_lock(&smeltertmutex[SmelterID]);//loaded miner if locksmeltertmutex
      WriteOutput(NULL, &transporters[ID], &smelters[SmelterID], NULL,TRANSPORTER_TRAVEL);


        usleep(Interval);
        smelters[SmelterID].waiting_ore_count += 1;

        if(smelters[SmelterID].oreType == COPPER  && smelters[SmelterID].waiting_ore_count >= smelters[SmelterID].loading_capacity)
            {
              availableSimulterCopper--;
            }

        if(smelters[SmelterID].oreType == IRON  &&smelters[SmelterID].waiting_ore_count >= smelters[SmelterID].loading_capacity)
        {
          availableIronSmulter--;
        }



//********************************************************************************************************
      //  FillTransporterInfo(&transporters[ID], ID, CarriedOre);


		WriteOutput(NULL, &transporters[ID], &smelters[SmelterID], NULL,TRANSPORTER_DROP_ORE);




//********************************************************************************************************

      usleep(Interval);

      if(isSmeltertmutexLock[SmelterID] && smelters[SmelterID].waiting_ore_count >= 2) //eger smerter bekliyor ve artık cevheri 2 den fazla ile post et
        {
          sem_post(&smeltermutexsem[SmelterID]);
          isSmeltertmutexLock[SmelterID] = 0;
        }


  pthread_mutex_unlock(&smeltertmutex[SmelterID]);
}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////






void *transFoundry(int *val_p)
{



//  int *val_p = (int *) arg;
  unsigned int ID = val_p[0];
  unsigned int Interval = val_p[1];
  unsigned int FoundryID = val_p[2];
  OreType *CarriedOre = transporters[ID].carry; // hellet


  FillTransporterInfo(&transporters[ID], ID + 1 , CarriedOre);

  pthread_mutex_lock(&foundrytmutex[FoundryID]);



      WriteOutput(NULL, &transporters[ID], NULL, &foundries[FoundryID],TRANSPORTER_TRAVEL);
      usleep(Interval);


      if(*CarriedOre == IRON)
      {
        foundries[FoundryID].waiting_iron += 1;
      }
      else
      {
        foundries[FoundryID].waiting_coal += 1;
      }

   //   FillTransporterInfo(&transporters[ID], ID, NULL);
      WriteOutput(NULL, &transporters[ID], NULL, &foundries[FoundryID],TRANSPORTER_DROP_ORE);
      usleep(Interval);

      if(isFoundrytmutexLock[FoundryID] && foundries[FoundryID].waiting_coal && foundries[FoundryID].waiting_iron )
      {
        isFoundrytmutexLock[FoundryID] = 0;
        sem_post(&foundrymutexsem[FoundryID]);
      }


  pthread_mutex_unlock(&foundrytmutex[FoundryID]);

  //unloaded yapılacak

}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////





void *transFunMain(void *arg)
{ int *val_p = (int *) arg;   //burada variableler işlenecek
  unsigned int i;
  int kthID = -1;
  unsigned int ID = val_p[0];
  unsigned int Interval = val_p[1];
  unsigned int MinerID,SmerterID,FoundryID;
  int GotoNextThread[3];
  int SorF;
  OreType *CarriedOre = NULL;
  FillTransporterInfo(&transporters[ID], ID + 1, CarriedOre);
  WriteOutput(NULL, &transporters[ID], NULL, NULL,TRANSPORTER_CREATED);
  GotoNextThread[1] = Interval;
  GotoNextThread[0] = ID;


  while( 1 )  //there are active miners
  {





    CarriedOre = NULL;
    // pthread_t  TransportMinerThread;
    // pthread_t  TransportSmelterFoundryThread;


    sem_wait(&Transportmutex);//lock transporters Transportmutex



    pthread_mutex_lock(&mutex);



        MinerID = nMines;
        for(i = 0 ;i < nMines;i++)
        {
          kthID = (kthID + i + 1)%nMines;
          if(miners[kthID].current_count > 0 &&   miners[kthID].current_count < 1110)
            {

              if(ironinminers <= 0 && miners[kthID].oreType == COAL)
                {
                  sem_post(&minersmutexsem[kthID]);
                  continue;
                }
              MinerID = kthID;
              break;
            }


        }

        for(i = 0 ;i < nMines;i++)
        {
          kthID = (kthID + i  )%nMines;
          if(miners[kthID].current_count > 0 &&   miners[kthID].current_count < 1110)
            {
              if(ironinminers <= 0 && miners[kthID].oreType == COAL)
                {
                  sem_post(&minersmutexsem[kthID]);
                  continue;
                }
              MinerID = kthID;
              break;
            }
        }


        if(MinerID == nMines)
          {
            pthread_mutex_unlock(&mutex);
            break;
          }


        if(miners[MinerID].current_count == 0 )
        {
          pthread_mutex_unlock(&mutex);
          break;
        }


        ///////////////////////////////////////////////
        GotoNextThread[2] = MinerID;
        transMiner(GotoNextThread);
        // pthread_create(&TransportMinerThread,NULL,transMiner,GotoNextThread);
        // pthread_join(TransportMinerThread,NULL);
        /////////////////////////////////////////////

    pthread_mutex_unlock(&mutex);

							// eger aldıgımız miner copper ise bu işlemi yap



lineSorF:
      SorF = 0;
      if(miners[MinerID].oreType == COPPER)
      {

          sem_wait(&CopperTransmutex);

        SorF = 1;
        for(i = 0; i<nsimul ; i++)
        {
          if( smelters[i].oreType == COPPER && ( smelters[i].loading_capacity > smelters[i].waiting_ore_count )  )
          {
            SmerterID = i;
            if(smelters[i].waiting_ore_count == 1)
              break;
          }
        }


      }





						  // eger aldıgımız miner coal ise bu işlemi yap



      else if(miners[MinerID].oreType == COAL)
      {

        //  printf("453\n" );
            sem_wait(&CoalTransmutex);
            if(Quittrans == 1)
              {
                break;
              }
      //    printf("454\n" );
        SorF = 2;
        for(i = 0; i<nFound ; i++)
        {
          if(foundries[i].loading_capacity > foundries[i].waiting_coal   )
          {
            FoundryID = i;
            if(foundries[i].waiting_iron >= 1)
              break;
          }
        }
      }




      else //miners[MinerID].oreType == IRON
      {

            sem_wait(&IronTransmutex);

              SorF = 2;
              for(i = 0; i<nFound ; i++)
              {
                if(foundries[i].loading_capacity > foundries[i].waiting_iron  )
                {
                  FoundryID = i;
                  if(foundries[i].waiting_coal >= 1)
                    goto breakElse;
                }
              }


              for(i = 0; i<nsimul ; i++)
              {
                if(smelters[i].oreType == IRON && smelters[i].loading_capacity > smelters[i].waiting_ore_count )
                {
                  SorF = 1;
                  SmerterID = i;
                  if(smelters[i].waiting_ore_count == 1)
                    goto breakElse;
                }
              }



      }

breakElse:

    ////////////////////////////////////////////
    if(SorF == 1) //smerter thread
    {
      GotoNextThread[2] = SmerterID;
      transSmerter(GotoNextThread);
      //pthread_create(&TransportSmelterFoundryThread,NULL,transSmerter,GotoNextThread);


    }
    else if(SorF == 2) //foundary thread
    {
      GotoNextThread[2] = FoundryID;
      transFoundry(GotoNextThread);
    //  pthread_create(&TransportSmelterFoundryThread,NULL,transFoundry,GotoNextThread);
    }
    else
    {
      //olur da bişey alamaz diye birdaha bakar
      goto lineSorF;
    }


  //  pthread_join(TransportSmelterFoundryThread,NULL);


  }

  for(i = 0;i<nMines;i++)
    sem_post(&minersmutexsem[i]);

  CarriedOre = NULL;
  FillTransporterInfo(&transporters[ID], ID + 1, CarriedOre);
  WriteOutput(NULL, &transporters[ID], NULL, NULL,TRANSPORTER_STOPPED);


    pthread_exit(NULL);
    return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////




void SmelterStopped(unsigned int id)
{
  smelteractive[id] = 0;//ID numaralı miner durdu artık
}

/////////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************/

static void handler(int sig)
{
    int sav_errno = errno;
    static const char info_msg[] = "sem_post() from handler\n";
    write(STDOUT_FILENO, info_msg, sizeof info_msg - 1);
    errno = sav_errno;
}
//////////////////////////////////////////////////////////////////////////////////////

void *smelterFun(void *arg)
{
  int *val_p = (int *) arg;
  unsigned int ID = val_p[0];
  unsigned int interval = val_p[1];
  unsigned int capacity = val_p[2];
  unsigned int totalproduces = 0;
  OreType oretype;
  int i;


  struct sigaction sa;
  struct timespec ts;
  int s;





  if(val_p[3] == 0)
    {
      smelters[ID].oreType = IRON;
      oretype = IRON;

    }
  else
    {
      smelters[ID].oreType = COPPER;
      oretype = COPPER;
    }


    for(i = 0;i<capacity;i++)
      {
        if(smelters[ID].oreType == IRON)
        {
          sem_post(&IronTransmutex);
        }
        else
        {
          sem_post(&CopperTransmutex);
        }
      }



  smelteractive[ID] = 1;
  FillSmelterInfo(&smelters[ID],ID + 1,oretype,capacity,0,totalproduces);




  WriteOutput(NULL, NULL, &smelters[ID], NULL, SMELTER_CREATED);



  while(1 )
  {




    if(smelters[ID].waiting_ore_count < 2)//transporterde eger waiting ore 2 den büyükse post edecek
      {

        isSmeltertmutexLock[ID] = 1;


        clock_gettime(CLOCK_REALTIME, &ts);

        ts.tv_sec += 5;

        while ((s = sem_timedwait(&smeltermutexsem[ID], &ts)) == -1 && errno == EINTR)
            continue;
            if (s == -1)
            {
                sem_post(&Transportmutex);//unlock transporters Transportmutex
                break;
            }

        //sem_wait(&smeltermutexsem[ID]);//Transporter birtane alan boşaltana kadar bekler ve transporter de release yapacak.

      }




  	pthread_mutex_lock(&smeltertmutex[ID]);





        smelters[ID].waiting_ore_count -= 2;

        WriteOutput(NULL, NULL, &smelters[ID], NULL, SMELTER_STARTED);
        usleep(interval);
        smelters[ID].total_produce += 1;
        WriteOutput(NULL, NULL, &smelters[ID], NULL, SMELTER_FINISHED);


        if(smelters[ID].oreType == COPPER)
          {

                sem_post(&CopperTransmutex);
                sem_post(&CopperTransmutex);
          }
        if(smelters[ID].oreType == IRON )
            {
              sem_post(&IronTransmutex);
              sem_post(&IronTransmutex);
            }



  	pthread_mutex_unlock(&smeltertmutex[ID]);







    }

  SmelterStopped(ID);
  WriteOutput(NULL, NULL,  &smelters[ID], NULL, SMELTER_STOPPED);


  pthread_exit(NULL);
  return NULL;

}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////



void FoundryStopped(unsigned int id)
{
  foundryactive[id] = 0;//ID numaralı miner durdu artık
}


void *foundryFun(void *arg)
{
  int *val_p = (int *) arg;
  unsigned int ID = val_p[0];
  unsigned int interval = val_p[1];
  unsigned int capacity = val_p[2];
  unsigned int totalproduces = 0;
  int i;


  struct sigaction sa;
  struct timespec ts;
  int s;

  totalcoalcapacity += capacity;

  for(i = 0;i<capacity;i++)
    {
      coaltranswait--;
       sem_post(&CoalTransmutex);
       sem_post(&IronTransmutex);
    }



  foundryactive[ID] = 1;
  isFoundrytmutexLock[ID] = 0;
  FillFoundryInfo(&foundries[ID],ID + 1,capacity,0,0,totalproduces);
  WriteOutput(NULL, NULL,  NULL, &foundries[ID] , FOUNDRY_CREATED);



  while(1)
  {


    if(foundries[ID].waiting_iron < 1 || foundries[ID].waiting_coal < 1)
      {
        isFoundrytmutexLock[ID] = 1;

        clock_gettime(CLOCK_REALTIME, &ts);

        ts.tv_sec += 5;

        while ((s = sem_timedwait(&foundrymutexsem[ID], &ts)) == -1 && errno == EINTR)
            continue;
        if (s == -1)
          {
            for(s = 0;s< nTrans;s++)
                sem_post(&CoalTransmutex);
            Quittrans = 1;
            sem_post(&Transportmutex);//unlock transporters Transportmutex
            break;
          }


      //  sem_wait(&foundrymutexsem[ID]);//Transporter birtane alan boşaltana kadar bekler ve transporter de release yapacak.

        if( foundries[ID].waiting_iron < 1 || foundries[ID].waiting_coal < 1 )
        	{
            break;//eger buraya gelmişse transformlar çıkarken bunu post etmiştir
          }
      }
        pthread_mutex_lock(&foundrytmutex[ID]);



                foundries[ID].waiting_iron -= 1;
                foundries[ID].waiting_coal -= 1;
                WriteOutput(NULL, NULL,  NULL, &foundries[ID], FOUNDRY_STARTED);
                usleep(interval);
                foundries[ID].total_produce += 1;
                WriteOutput(NULL, NULL, NULL, &foundries[ID], FOUNDRY_FINISHED);



                sem_post(&IronTransmutex);
                sem_post(&CoalTransmutex);
                totalcoalcapacity += 1;
                coaltranswait--;



        pthread_mutex_unlock(&foundrytmutex[ID]);

  }

  FoundryStopped(ID);
  WriteOutput(NULL, NULL,  NULL, &foundries[ID], FOUNDRY_STOPPED);

  pthread_exit(NULL);
  return NULL;

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////











unsigned int retint(char c)
{
  if(c == '0')
    return 0;
  if(c == '1')
    return 1;
  if(c == '2')
    return 2;
  if(c == '3')
    return 3;
  if(c == '4')
    return 4;
  if(c == '5')
    return 5;
  if(c == '6')
      return 6;
  if(c == '7')
      return 7;
  if(c == '8')
      return 8;
  if(c == '9')
      return 9;
  else return 10;
}



int main()
{

  char  gl[boyut];

//inputs part

  fgets(gl,boyut,stdin); //miners inputs
  nMines = atoi(gl);
  miners = (struct MinerInfo*) malloc(nMines * sizeof(struct MinerInfo));
  mineractive = (int*) malloc(nMines * sizeof(int));
  MinerThread = (pthread_t*) malloc(nMines * sizeof(pthread_t));
  Minertmutex = (pthread_mutex_t*)malloc(nMines * sizeof(pthread_mutex_t));
  mProp = (unsigned int**)malloc(nMines * sizeof(unsigned int *));
  isMinertmutexLock = (int*) malloc(nMines * sizeof(int));



  minersmutexsem = (sem_t*)malloc(nMines*sizeof(sem_t));
  for(i = 0; i< nMines; i++)
  {
    mProp[i] = (unsigned int*)malloc(5 * sizeof(unsigned int));

    fgets(gl,boyut,stdin);

    for(j = 1; j<5 ;j++)
      mProp[i][j] = 0;

    j = 0;
    k = 1;
      mProp[i][0] = i; //id of miner
    while(gl[j] != '\n')
      {
        reti = retint(gl[j++]);
        if(reti > 9)
          {
            k++;
            continue;
          }
        mProp[i][k] = mProp[i][k]*10;
        mProp[i][k] += reti;
      }

      sem_init(&minersmutexsem[i],
               0,
               0);

  }








  fgets(gl,boyut,stdin); // transporter inputs
  nTrans = atoi(gl);
  transporters = (struct TransporterInfo*) malloc(nTrans * sizeof(struct TransporterInfo));
  transThread = (pthread_t*) malloc(nTrans * sizeof(pthread_t));
  tProp = (unsigned int**)malloc(nTrans * sizeof(unsigned int *));
  for(i = 0; i < nTrans; i++)
  {
  //  pthread_mutex_init(&transThread[i], NULL);
    tProp[i] = (unsigned int*)malloc(2 * sizeof(unsigned int));
    fgets(gl,boyut,stdin);
    for(j = 1; j<5 ;j++)
      tProp[i][j] = 0;
    j = 0;
    k = 1;
    tProp[i][0] = i;
    while(gl[j] != '\n')
      {
        reti = retint(gl[j++]);
        if(reti > 9)
          {
            k++;
            continue;
          }
        tProp[i][k] *= 10;
        tProp[i][k] += reti;
      }
  }


  fgets(gl,boyut,stdin); //smelter inputs
  nsimul = atoi(gl);
  smelters = (struct SmelterInfo*) malloc(nsimul * sizeof(struct SmelterInfo));
  isSmeltertmutexLock = (unsigned int*) malloc(nsimul * sizeof(unsigned int));
  smelteractive= (int*) malloc(nsimul * sizeof(int));
  smelterThread = (pthread_t*) malloc(nsimul * sizeof(pthread_t));
  smeltertmutex = (pthread_mutex_t*)malloc(nsimul * sizeof(pthread_mutex_t));
  siProp = (unsigned int**)malloc(nsimul * sizeof(unsigned int *));
  smeltermutexsem = (sem_t*)malloc(nsimul*sizeof(sem_t));
  for(i = 0; i< nsimul; i++)
  {

    siProp[i] = (unsigned int*)malloc(4 * sizeof(unsigned int));
    fgets(gl,boyut,stdin);
    for(j = 1; j<5 ;j++)
      siProp[i][j] = 0;
    j = 0;
    k = 1;
    siProp[i][0] = i;
    while(gl[j] != '\n')
       {
        reti = retint(gl[j++]);
         if(reti > 9)
           {
             k++;
             continue;
           }
         siProp[i][k] *= 10;
         siProp[i][k] += reti;
       }
       if(siProp[i][3] == 0)
          availableIronSmulter++;
       else
          availableSimulterCopper++;


      sem_init(&smeltermutexsem[i],
                   0,
                   0);
   }



   fgets(gl,boyut,stdin); //foundry inputs
   nFound = atoi(gl);
   foundries = (struct FoundryInfo*) malloc(nFound * sizeof(struct FoundryInfo));
   isFoundrytmutexLock = (unsigned int*) malloc(nFound * sizeof(unsigned int));
   foundryactive= (int*) malloc(nFound * sizeof(int));
   foundryThread = (pthread_t*) malloc(nFound * sizeof(pthread_t));
   foundrytmutex = (pthread_mutex_t*)malloc(nFound * sizeof(pthread_mutex_t));
   availableCoalFoundry = nFound;
   availableIRONFoundry = nFound;
   fProp = (unsigned int**)malloc(nFound * sizeof(unsigned int *));
   foundrymutexsem = (sem_t*)malloc(nFound*sizeof(sem_t));

   for(i = 0; i< nFound; i++)
   {
     fProp[i] = (unsigned int*)malloc(4 * sizeof(unsigned int));
     fgets(gl,boyut,stdin);
     for(j = 1; j<5 ;j++)
       fProp[i][j] = 0;
     j = 0;
     k = 1;
     fProp[i][0] = i;
     while(gl[j] != '\n')
       {
         reti = retint(gl[j++]);
         if(reti > 9)
           {
             k++;
             continue;
           }
         fProp[i][k] *= 10;
         fProp[i][k] += reti;
       }

       sem_init(&foundrymutexsem[i],
                0,
                0);
   }



//// init semafore


  sem_init(&Transportmutex,
           0,
           0);

           sem_init(&CopperTransmutex,
                    0,
                    0);

                    sem_init(&IronTransmutex,
                             0,
                             0);



                             sem_init(&CoalTransmutex,
                                      0,
                                      0);




  ////create threads ////

   for(i = 0; i< nMines; i++)
   {
     pthread_mutex_init(&Minertmutex[i], NULL);
     pthread_create(&MinerThread[i],NULL,minerFun,mProp[i]);
   }

   for(i = 0; i< nsimul; i++)
   {
     pthread_mutex_init(&smeltertmutex[i], NULL);
     pthread_create(&smelterThread[i],NULL,smelterFun,siProp[i]);

   }

   for(i = 0; i< nFound; i++)
   {
     pthread_mutex_init(&foundrytmutex[i], NULL);
     pthread_create(&foundryThread[i],NULL,foundryFun,fProp[i]);

   }


   for(i = 0; i< nTrans; i++)
   {
     pthread_create(&transThread[i],NULL,transFunMain,tProp[i]);
   }















  //// dealloc part /////

  for(i = 0; i< nMines; i++) //minerlerin bitmesini bekle
    {
      pthread_join(MinerThread[i],NULL);
      free(mProp[i]);
      sem_destroy(&minersmutexsem[i]);
    //  free(minersmutexsem[i]);
    }






  for(i = 0; i< nsimul; i++) //minerlerin bitmesini bekle
    {
      pthread_join(smelterThread[i],NULL);
      free(siProp[i]);
      sem_destroy(&smeltermutexsem[i]);
    //  free(smeltermutexsem[i]);
    }
    for(i = 0; i< nFound; i++) //minerlerin bitmesini bekle
      {
        pthread_join(foundryThread[i],NULL);
        free(fProp[i]);
        sem_destroy(&foundrymutexsem[i]);
    //    free(foundrymutexsem[i]);
      }




for(i = 0; i < nTrans; i++) //minerlerin bitmesini bekle
  {

    pthread_join(transThread[i],NULL);
  //  free(tProp[i]);

  }



    /// destroy semaphores


    	sem_destroy(&Transportmutex);
      	sem_destroy(&CopperTransmutex);
        	sem_destroy(&IronTransmutex);
          	sem_destroy(&CoalTransmutex);


free(foundryactive);
free(isFoundrytmutexLock);
free(foundrytmutex);
free(foundryThread);
free(smelteractive);
free(isSmeltertmutexLock);
free(smeltertmutex);
free(smelterThread);




  free(foundrymutexsem);



  free(smeltermutexsem);


  free(minersmutexsem);

  free(mProp);




  //free(tProp);


  free(siProp);
  free(fProp);
  free(mineractive);
  free(MinerThread);
  free(Minertmutex);
  free(isMinertmutexLock);




//  free(transThread);








//   free(transporters);





  // free(smelters);

  // free(foundries);







 //  free(miners);



   return 0;
 }
