#include <iostream>
#include <string>
#include <vector>
#include<algorithm>
using namespace std;

vector< vector<int> > triangle;
int numberOfLine;

void getTriangle()
{
 cin >> numberOfLine;

 for(int i = 0; i < numberOfLine; i++)
 {
     vector<int> ithLine;
     int elem;
     for(int j = 0; j <= i; j++)
     {
        cin >> elem;
        ithLine.push_back(elem);
     }
    triangle.push_back(ithLine);
  }
}

void printTriangle()
{
    for(int i = 0; i < numberOfLine; i++)
    {
        for(int j = 0; j <=  i; j++)
        {
            cout<<triangle[i][j] <<" ";
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

int maxSumBelowAdjacent(int i, int j) //sum from ith line jth element to last line
{
    if(i >= numberOfLine || j > i || isPrime(triangle[i][j]) )
        return 0;

    return triangle[i][j] + max(maxSumBelowAdjacent(i+1, j), maxSumBelowAdjacent(i+1, j+1));
}

int main()
{

   getTriangle();
   printTriangle();
   cout<< maxSumBelowAdjacent(0,0) << endl;

}
