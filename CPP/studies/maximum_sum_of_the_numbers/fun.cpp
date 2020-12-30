#include <iostream>
#include <string>
#include <vector>
#include<algorithm>
#include <cstdio>
using namespace std;


struct Elem
{
  int value;
  int maxVal;
  int depth;
  int nextstep;
};



vector< vector<Elem> > triangle;
int numberOfLine;

void getTriangle()
{
 cin >> numberOfLine;

 for(int i = 0; i < numberOfLine; i++)
 {
     vector<Elem> ithLine;
     Elem elem;
     for(int j = 0; j <= i; j++)
     {
        cin >> elem.value;
        elem.maxVal = -1;
        elem.depth = -1;
        elem.nextstep = -1;
        ithLine.push_back(elem);
     }
    triangle.push_back(ithLine);
  }

}

void printTriangle()
{
    int ipath = 0;
    int jpath = 0;
    for(int i = 0; i < numberOfLine; i++)
    {
        for(int j = 0; j <=  i; j++)
        {
          if(i == ipath && j == jpath)
          {
            ipath++;
            jpath = j + triangle[i][j].nextstep;
            cout<< "\t"<< "*" << triangle[i][j].value <<" ";
          }
          else
            cout<< "\t"<< triangle[i][j].value <<" ";
        }
        cout<<endl;
    }



    ipath = 0;
    jpath = 0;
    for(int i = 0; i < numberOfLine; i++)
    {
        for(int j = 0; j <=  i; j++)
        {
            if(i == ipath && j == jpath)
            {
              ipath++;
              jpath = j + triangle[i][j].nextstep;
              cout<< "\t"<< "*" << triangle[i][j].maxVal <<" ";
            }
            else
              cout<< "\t"<< triangle[i][j].maxVal <<" ";
        }

        cout<<endl;
    }


}
bool isPrime(int num)
{
    if(num < 2)
        return false;
    for(int i = 2; i <= num/2; i++)
        if(num%i == 0)
            return false;
    return true;
}

void maxSumBelowAdjacent(int i, int j) //sum from ith line jth element to last line
{
    if( j > i || isPrime(triangle[i][j].value) )
    {
      triangle[i][j].maxVal = 0;
      triangle[i][j].depth = i-1;
    }

    else if (i == numberOfLine - 1)
    {
      triangle[i][j].maxVal = triangle[i][j].value;
      triangle[i][j].depth = i;
    }


    else
    {
      if(triangle[i+1][j].maxVal == -1)
        maxSumBelowAdjacent(i+1, j);
      if(triangle[i+1][j+1].maxVal == -1)
        maxSumBelowAdjacent(i+1, j+1);

      if(triangle[i+1][j].depth == triangle[i+1][j+1].depth)
      {
        if(triangle[i+1][j].maxVal >= triangle[i+1][j+1].maxVal)
        {
          triangle[i][j].nextstep = 0;
          triangle[i][j].depth = triangle[i+1][j].depth;
          triangle[i][j].maxVal = triangle[i+1][j].maxVal + triangle[i][j].value;
        }
        else
        {
          triangle[i][j].nextstep = 1;
          triangle[i][j].depth = triangle[i+1][j+1].depth;
          triangle[i][j].maxVal = triangle[i+1][j+1].maxVal + triangle[i][j].value;
        }
      }
      else if(triangle[i+1][j].depth > triangle[i+1][j+1].depth)
      {
        triangle[i][j].nextstep = 0;
        triangle[i][j].depth = triangle[i+1][j].depth;
        triangle[i][j].maxVal = triangle[i+1][j].maxVal + triangle[i][j].value;
      }
      else
      {
        triangle[i][j].nextstep = 1;
        triangle[i][j].depth = triangle[i+1][j+1].depth;
        triangle[i][j].maxVal = triangle[i+1][j+1].maxVal + triangle[i][j].value;
      }
    }
}

int main()
{
   getTriangle();
   maxSumBelowAdjacent(0,0);
   printTriangle();
   cout<<"maximim value is " << triangle[0][0].maxVal << endl;
   cout<<"Depth is " << triangle[0][0].depth << endl;
}
