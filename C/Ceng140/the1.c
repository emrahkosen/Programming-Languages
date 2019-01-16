#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>





void changepost(char post[],int i,char tur)
{   int tempi = i;
  tempi--;


  if(tur == '-' || tur == '+' || tur == '*' || tur == '/' || tur == '^')
  {
    
    if(post[tempi] == ')')
    {
      while(post[tempi] != '(')
      {
        tempi--;
      }
      tempi--;
      
      if(post[tempi] == ')')
      {
        while(post[tempi] != '(')
        {
          tempi--;
        }

      }




    }
    else
    {
      tempi--;
      if(post[tempi] == ')')
      {
        while(post[tempi] != '(')
        {
          tempi--;
        }

      }

    }
    
    post[tempi++] = '#';




    if(i > tempi)
    {

      while(post[i] != '\0')
      {
        post[tempi++] = post[++i];
      }
      post[tempi] = '\0';
    }



  }

  
  else
  {


    
    if(post[tempi] == ')')
    {
      while(post[tempi] != '(')
      {

        tempi--;
      }

    }

    else
    {
      ;
    }

    post[tempi++] = '#';




    if(i > tempi)
    {
      while(post[i] != '\0')
      {
        
        post[tempi++] = post[++i];
      }

    
    post[tempi] = '\0';
    }

    else
    {
      while(post[i] != '\0')
      {
        
        post[i] = post[i+1];
        i++;
      }

    }



  }



}


void calhelper(char post[],double numlist[],int boy)
{


                                 
  int a,k=0;
  for(a=0,k=0;post[a] != '\0';a++)
  {
    
    if(post[a] == '(')
    {
      k++;
      while(post[a] != ')')
      {
        a++;
      }
      continue;
    }
    else if( post[a] >= 'A' && post[a] <= 'Z' || post[a] == '#')
    {
      k++;
      continue;
    }





    else
    {
     
        if(post[a] == '+')
        {
          
          double ilk,iki,top;
          ilk = numlist[k-2];
          iki = numlist[k-1];
          top = ilk + iki;

          numlist[k-2] = top;
         
          
          while(k != boy)
          {
            numlist[k-1] = numlist[k];
            k++;
          }
          boy--;



          changepost(post,a,post[a]);

         
          calhelper(post,numlist,boy);
          break;

        }


        else if(post[a] == '-')
        {
          double ilk,iki,top;
          ilk = numlist[k-2];
          iki = numlist[k-1];
          top = ilk - iki;

          numlist[k-2] = top;
          while(k != boy)
          {
            numlist[k-1] = numlist[k];
            k++;
          }
          boy--;
          changepost(post,a,post[a]);
          calhelper(post,numlist,boy);
          break;

        }

        else if(post[a] == '/')
        {
          double ilk,iki,top;
          ilk = numlist[k-2];
          iki = numlist[k-1];
          top = ilk / iki;

          numlist[k-2] = top;
          while(k != boy)
          {
            numlist[k-1] = numlist[k];
            k++;
          }
          boy--;
          changepost(post,a,post[a]);
          calhelper(post,numlist,boy);
          break;

        }

        else if(post[a] == '*')
        {
          double ilk,iki,top;
          ilk = numlist[k-2];
          iki = numlist[k-1];
          top = ilk * iki;

          numlist[k-2] = top;
          while(k != boy)
          {
            numlist[k-1] = numlist[k];
            k++;
          }
          boy--;
          changepost(post,a,post[a]);
          calhelper(post,numlist,boy);
          break;

        }


        else if(post[a] == '^')
        {
          double ilk,iki,top;
          ilk = numlist[k-2];
          iki = numlist[k-1];

          top = pow(ilk,iki);

          numlist[k-2] = top;
          while(k != boy)
          {
            numlist[k-1] = numlist[k];
            k++;
          }
          boy--;
          changepost(post,a,post[a]);
          calhelper(post,numlist,boy);
          break;

        }


                else
        {

          if(post[a] == 'q')
          {
            double ilk,top;
            ilk = numlist[k-1];
            

            top = sqrt(ilk);

            numlist[k-1] = top;
         
            changepost(post,a,post[a]);
            calhelper(post,numlist,boy);
            break;

          }


          else if(post[a] == 'l')
          {
            double ilk,top;
            ilk = numlist[k-1];
            

            top = log(ilk);

            numlist[k-1] = top;
         
            changepost(post,a,post[a]);
            calhelper(post,numlist,boy);
            break;

          }


          else if(post[a] == 'i')
          {
            double ilk,top;
            ilk = numlist[k-1];
            

            top = sin(ilk);

            numlist[k-1] = top;
         
            changepost(post,a,post[a]);
           
            calhelper(post,numlist,boy);
            break;

          }

          else if(post[a] == 'c')
          {
            double ilk,top;
            k--;
            ilk = numlist[k++];
            

            top = cos(ilk);

            numlist[k-1] = top;
         
            changepost(post,a,post[a]);
            calhelper(post,numlist,boy);
            break;

          }







          else if(post[a] == '~')
          {

            double ilk,top;
            k--;
            ilk = numlist[k++];
            

            top = (-1)*(ilk);

            numlist[k-1] = top;

            changepost(post,a,post[a]);
           
            calhelper(post,numlist,boy);
            break;

          }

        }






      


       }


  }



}











double findnum(char followings[],double follownum[],char letter)
{
  double number,numverlist,temp;
  int i=0 ;
  while(followings[i] != '\0')
  {
    if(letter == followings[i])
    {
      return follownum[i];
      break;
    }

    ++i;
  }
}










double calculate(char postorg[],char followings[],double follownum[],int countline)
{
  int i,a,k=0,l=0;
  char post[300];
  double  result, *numlist;



while(postorg[l] != '\0')
{
  post[l] = postorg[l];
  l++;
}
post[l] = '\0';






  numlist = (double *)malloc(sizeof(double)*200);
  for(i=0;post[i] != '\0';i++)  /**bu dongu bize post daki sayilarin double listesini hesapladi**/
  {

    
    if(post[i] == '(')
    {
      int tempi = i++;
      int tempvar =0;
      double left=0,right=0;

                  

      while(post[tempi] != ')')
      {
        if(post[tempi] == '.')
        {
          
          tempvar = 1;
        }
        tempi++;
      }
      --tempi;

      if(tempvar)
      {

        while(post[i] != '.')
        {
          left = left*10 + (post[i++] -48);
        }
        while(post[tempi] != '.' )
        {
          right = (right +(post[tempi]-48))/10;
          tempi--;
        }
        numlist[k++] = left+ right;    
      }

      else
      {

        while(post[i] != ')' )
        {
          left = left*10 + (post[i++] -48);
        }
        numlist[k++] = left;

      }
      while(post[i] != ')')
        i++;
           
      continue;
    }

    else if(post[i] >= 'A' && post[i] <= 90)
    {

      numlist[k++] = findnum(followings,follownum,post[i]);
      
      
    }

    else
      ;

  }



calhelper(post,numlist,k);

return numlist[0];


}





double getrandom(double followingLine[],char following,int n)
{	
	
	int i,konum=0,a,b;
	double rand1;
	double rand2;
	double *newfoll;
	double birim,birim2,retnum;



/*
	  int  stime;
	  long ltime;

	    /* get the current calendar time 
	  ltime = time(NULL);
	  stime = (unsigned) ltime/2;
	     /*srand(stime);
			
*/
                                       

	newfoll = (double*)malloc(sizeof(double)*n);

	for(i=0;i<n;i++)
	{
		if(i == 0)
		{
			newfoll[i] = followingLine[i+2]*1000;
		}
		else
		{
			newfoll[i] = followingLine[i+2]*1000 + newfoll[i-1];
		}
	}



/*

	rand1 = rand()%1000;  */

  rand1 = (1000.0*rand())/RAND_MAX;




	for(i=0;i<n;++i)  /* burfa sıfır olasılıkları da halletmeliyim tami newfoll[i] ile i-1 i aynı seylerı veriyorsa */
	{
		if(i == 0)
		{	
			if(newfoll[i] == 0)
			{
				continue;
			}

		
			else
			{
				if(rand1 <= newfoll[i])
				{
					konum =i;
					break;
				}
			
			}
		}
		else
		{
		
			if(rand1 <= newfoll[i] && rand1 >= newfoll[i-1])
			{
				konum = i;
				break;
			}
		}

		
	}


	birim = (followingLine[1] -followingLine[0])/n;





	rand2 = ((rand())%1000)/1000.0;

	birim2 = birim*rand2;
	retnum = followingLine[0] + birim2 + birim*konum;







return retnum;
}











void sayimi(char pre[],int e ,char post[],int t)
{
  
  post[t++] = '(';
   
    


  while(pre[e] == '.' || pre[e] <= 57 && pre[e] >= 48 )
  { 
    
    
    post[t++] = pre[e++];
    
  
  }
  post[t++] = ')';
  post[t] = '\0';

}











void syard(char pre[],int e,char stak[],int k,char post[] ,int t)
{
  
  if(pre[e] == '\0')
  {
    while(k != 0)
    {
      
      k--;
      post[t] = stak[k];
      stak[k] = '\0';
      t++;
      post[t] = '\0';

    }

  }

  

  else if(pre[e] == ' ')
  {
    
    syard(pre,++e,stak,k,post,t);
  }
  else
  {
    
    if(pre[e] >= 65 && pre[e] <= 90)
    {
      post[t++] = pre[e++];
      syard(pre,e,stak,k,post,t);
    }




    else if(pre[e] >= 48 && pre[e] <= 57  || pre[e] == '.')
    {
      
      
      sayimi(pre,e,post,t);
      while(pre[e] == '.' || pre[e] <= 57 && pre[e] >= 48 )
      {
        e++;
        t++;
      }
      t += 2;

      
      syard(pre,e,stak,k,post,t);

    }






    else
    {
      char tmp = pre[e];
      if(tmp == '+' || tmp == '-' || tmp == '*' || tmp == '/' || tmp == '^')
      {
        if(k == 0)
        {
          stak[k++] = pre[e++];
          syard(pre,e,stak,k,post,t);
        }
        else
        {
          if(tmp == '+' || tmp == '-' ) /**/
          {
            if(stak[k-1] == '*' || stak[k-1] == '/' || stak[k-1] == '^')
            {

              if(stak[k-1] == '^')
              {
                while(stak[k-1] == '^')
                {
                  post[t++] = stak[--k];
                }


              }



              else
              {
                post[t++] = stak[--k];
              }  

                stak[k++] = pre[e++];
                syard(pre,e,stak,k,post,t);
              



            }
            else
            {
              stak[k++] = pre[e++];
              syard(pre,e,stak,k,post,t);
            }
          }
          else if(tmp == '*' || tmp == '/') /**/
          {
            if( stak[k-1] == '/' || stak[k-1] == '*' || stak[k-1] == '^' )
            {


              if(stak[k-1] == '^')
              {
                while(stak[k-1] == '^')
                {
                  post[t++] = stak[--k];
                }


              }



              else
              {
                post[t++] = stak[--k];
              }  

                stak[k++] = pre[e++];
                syard(pre,e,stak,k,post,t);
              



            }
            else                           
            {
              stak[k++] = pre[e++];
              syard(pre,e,stak,k,post,t);
            }

          }

          else if ( tmp == '^')
          {

            /*
            if( stak[k-1] == '^' )
            {
              post[t++] = stak[--k];
              stak[k++] = pre[e++];
              syard(pre,e,stak,k,post,t);
            }

            

            else
            {

              */
              stak[k++] = pre[e++];
              syard(pre,e,stak,k,post,t);
            /*
            } 
            */

          }






          else                        /*^*/
          {
            while(pre[++e] == ' ')
            {
              ;
            }
            if(pre[e] >= 48 && pre[e] <= 57)
            {
              sayimi(pre,e,post,t);
              while(pre[e] == '.' || pre[e] <= 57 && pre[e] >= 48 )
              {
                e++;
                t++;
              }
              t += 2;
            }

            else /* sinus falan olabilir */
            {
            post[t++] = pre[e];
            }
            post[t++] = '^';
            post[t] = '\0';

            syard(pre,e,stak,k,post,t);
          }
        }
      }






      else if(tmp == '(' || tmp == ')') /****/
      {
        if(tmp == '(')
        {
          stak[k++] = pre[e++];
          syard(pre,e,stak,k,post,t);
        }
        else
        {
          
          k = k-1;

          
          for(; stak[k] != '(' ;k--)
          {
            post[t++] = stak[k];
            stak[k] = '\0';
          }
          stak[k] = '\0';
        
            
          if(stak[k-1] == 'i'||stak[k-1] == 'c'|| stak[k-1] == 'q' || stak[k-1] == 'l' || stak[k-1] == '~')
          {
            post[t++] = stak[--k];
            stak[k] = '\0';
          }
          
          syard(pre,++e,stak,k,post,t);

        }
       
      } 

      









      else
      {
        if(tmp == 's' && pre[e+1] == 'i')
        {
          stak[k++] = 'i';
          e += 3;
          syard(pre,e,stak,k,post,t);

        }
        else if(pre[e] == 's' && pre[e+1] == 'q')
        {
          stak[k++] = 'q';
          e += 4;
          syard(pre,e,stak,k,post,t);

        }
        else if(pre[e] == 'c')
        {
          stak[k++] = 'c';
          e += 3;
          syard(pre,e,stak,k,post,t);
        }
        else if(pre[e] == 'l')
        {
          stak[k++] = 'l';
          e += 2;
          syard(pre,e,stak,k,post,t);
        }
        else if(pre[e] == '~')
        {
          stak[k++] = '~';
          syard(pre,++e,stak,k,post,t);
        }

        else
        {
          ;
        }
      }








    }
  }


}










int icindemi(char ABC[],char harf,int i)
{
  if(ABC[i] == '\0')
    return 0;
  else
  {
    if(ABC[i] == harf)
      return 1;
    else
      return icindemi(ABC,harf,++i);
  }
}







int main()
{ char stak[300],post[300];
  int n,z=0,i,j,k,l,countLine=0,ii;
  long int countex;
  char first[200],ABC[40];
  char *followings;
  double  **followingLines;

  double *numlist;
  double result;

  double max,min;

  double *newprob,newprobaralik;

srand(time(0));



  for(i=0;i<40;i++)
    ABC[i] = '\0';


/*

  fgets(first,200,stdin);
*/

    do
  {
        scanf("%c",&first[z]);
  }while(first[z++]  != '\n');
  first[--z] = '\0';




  scanf("%d %ld",&n,&countex);


  for (i = 0; first[i] != '\0'; ++i)
  {
    if (first[i] >= 65 && first[i] <= 90 && !icindemi(ABC,first[i],0))
    {
     ABC[countLine++] = first[i];

    }
  }

  
  
  followings = (char *)malloc(sizeof(char)*(countLine+1));
  followingLines = (double **)malloc(sizeof(double*)*countLine);
  
  numlist = (double *)malloc(sizeof(double)*countLine);

  newprob = (double *)malloc(sizeof(double)*n);





  	for (i = 0; i < countLine; i++)
	  {
	    followingLines[i] = (double *)malloc(sizeof(double)*(n+2));
	  }






 for(k =0;k<countLine;k++)
 {
  

  scanf("\n%c",&followings[k]);
  

  for(l = 0;l< n+2;l++)
	  {
	    
	    scanf("%lf",&followingLines[k][l]);
	  }
 }










  syard(first,0,stak,0,post,0); 
  



  for(i = 0 ; i<countLine ;i++)
  {	
    
  	numlist[i] = getrandom(followingLines[i],followings[i],n);


   
  }


result = calculate(post,followings,numlist,countLine);





max = result;
min = result;

for(i=0;i<countex;i++) 
{	

	  for(j = 0 ; j<countLine ;j++)
	  {		
	  	numlist[j] = getrandom(followingLines[j],followings[j],n);
     
	  }


    

	  
	
	result = calculate(post,followings,numlist,countLine); 


	if(max < result)
	{
		max = result;
    
  }
	if(min > result)
	{
		min = result;

	}
  
  
}



newprobaralik = (max-min)/n;

for (i = 0; i < n; ++i)
{
  newprob[i] = 0;
}










for (i = 0; i < countex; ++i)  
{
  


  for(j = 0 ; j<countLine ;j++)
    {   
      numlist[j] = getrandom(followingLines[j],followings[j],n);
      
    }


    result = calculate(post,followings,numlist,countLine);






    if(result <= max && result >= min)
    {


      for(ii = 0;ii < n;ii++)
      {
        
        if(ii == 0)
        {
          if(result <= min + newprobaralik + ii*newprobaralik)
          {
            newprob[ii] += 1;
            break;
          }
          
        }

        else
        {

          if(result <= min + newprobaralik + ii*newprobaralik && result >=  min + ii*newprobaralik)
          {
            newprob[ii] += 1;
            break;
          }
        }



      }
    }


    else
    {
      i--;
      continue;
    }



    

}







printf("%.3f %.3f ",min ,max );
for (int i = 0; i < n; ++i)
{
  printf("%.3f ",newprob[i]/countex );
}


/*
printf("\n");

*/











  return 0;
}
