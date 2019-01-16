#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;


vector<int> odd;
vector<int> even;
int key;
int scientist;
int bunny;
int ammo;


void givepath(vector<int> path)
{
  for (size_t i = 0; i < path.size(); i++) {
    cout<<path[i]<<" ";
  }
  cout<<endl;
}


bool isinpath(vector<int> path,int x)
{
  int period = path.size();
  for (size_t i = 0; i < period; i++) {
    if(path[i] == x)
      return true;
  }
  return false;
}


bool isodd(int room)
{
  int period = odd.size();
  for (size_t i = 0; i < period; i++) {
    if(odd[i] == room)
      return true;
  }
  return false;
}
bool iseven(int room)
{
  int period = even.size();
  for (size_t i = 0; i < period; i++) {
    if(even[i] == room)
      return true;
  }
  return false;
}


struct room
{
  int cost;
  int level;
  vector<int> path;
};


room getpath(vector<vector<int>> roomvector,int roomnumber,int start,int end, room rstart ) //path'ın başında toplam ammo harcama miktarı verilecek
{
  vector<room> list;
  vector<room> ends;


  if(start == end)
  {
    ends.push_back(rstart);
  }
  for (size_t i = 0; i <= roomnumber; i++)
  {
       room tmp;
       tmp.cost = INT_MAX;
       tmp.level = -1;
       tmp.path.push_back(0);
       list.push_back(tmp);
  }
  list[start].cost = rstart.cost;
  list[start].level= rstart.level;
  for (size_t i = 1; i < rstart.path.size()-1; i++) // -1 yaptım cunku rstart i iki defa cagırıyordu.
  {
    list[start].path.push_back(rstart.path[i]);
  }

  for (size_t i = rstart.level; i <= 2*roomnumber+rstart.level; i++)
  {
    vector<room> list2;
    room tmp;
    tmp.cost = INT_MAX;
    tmp.level = -1;
    tmp.path.push_back(0);
    list2.push_back(tmp);


    for (size_t j = 1; j <= roomnumber; j++)
    {
      room listj;
      listj.cost = INT_MAX;
      listj.level= -1;
      listj.path.push_back(0);


      if((isodd(j) && i%2 == 0) || (iseven(j) && i%2 == 1))
        goto here;

      if((start == 1 && (j == scientist || j == bunny))||(start == key && j == bunny))
          goto here;

      for (size_t k = 1; k <= roomnumber; k++)
      {


        if(j != k)
        {
          if(list[k].level == i && roomvector[k][j] > 0 && list[k].cost < INT_MAX &&
            ( ( (!roomvector[j][j])&&(roomvector[k][j] + list[k].cost < listj.cost) )
                ||
                ( roomvector[j][j] && !isinpath(list[k].path,j)  && (roomvector[k][j] + list[k].cost-roomvector[j][j] < listj.cost))
            ))
          {
            listj.cost = roomvector[k][j] + list[k].cost;
            listj.level = list[k].level + 1;
            listj.path.clear(); //clear previous path of j
            for (size_t l = 0; l < list[k].path.size(); l++)
            {
              int psh = list[k].path[l];
                listj.path.push_back(psh);
            }
            listj.path.push_back(k);

            if(roomvector[j][j]>0 && !isinpath(listj.path,j))
              {
                listj.cost -= roomvector[j][j];
              }
            //  givepath(listj.path);
              if(j == end and listj.cost < INT_MAX)
              {
                // cout<<listj.cost<<endl;
                // cout<<"           ";
                // givepath(listj.path);

                ends.push_back(listj);
              }
          }
        }

      }
here:
      list2.push_back(listj);
    }

    for (size_t j = 1; j <= roomnumber; j++)
    {


      list[j].cost = list2[j].cost;
      list[j].level = list2[j].level;
      for (size_t l = 0; l < list2[j].path.size(); l++) {
        int psh = list2[j].path[l];
        if(list[j].path.size()>l)
          list[j].path[l] = psh;
        else
          list[j].path.push_back(psh);
      }
    }
  }

  room ret;
  ret.cost = INT_MAX;
  ret.level = 0;
  ret.path.push_back(0);
  if(ends.size())
  {
    ret.cost = ends[0].cost;
    ret.level = ends[0].level;
    ret.path = ends[0].path;
    for (size_t i = 1; i < ends.size(); i++)
    {
      if(ends[i].cost< ret.cost )
      {
        ret.cost = ends[i].cost;
        ret.level = ends[i].level;
        ret.path = ends[i].path;
      }
    }
    return ret;
  }

}








int main () {


  int roomnumber=0;
  vector<vector<int>> roomvector;
  int numberodd;
  int numbereven;
  int  numbercorridors;
  int numofammoroom;
  int x;

  string line;
  ifstream infile("the3.inp");
  if (infile.is_open())
  {
    infile>>ammo;
    infile>>roomnumber;
    for (size_t i = 0; i < roomnumber+1; i++)
    { vector<int> vec;
      for (size_t j = 0; j < roomnumber+1; j++)
      {
        if(i == 0)
          vec.push_back(j);
        else if(j == 0)
          vec.push_back(i);
        else
            vec.push_back(0);
      }
      roomvector.push_back(vec);
    }
    infile>>bunny;
    infile>>key;
    infile>>scientist;
    infile>>numberodd;
    if(numbereven == 1)
    {
       infile>>x;
       odd.push_back(x);
    }
    else
      for (size_t i = 0; i < numberodd; i++)
      {
        infile>>x;
        odd.push_back(x);
      }
    infile>>numbereven;

    if(numbereven == 1)
      {infile>>x;
        even.push_back(x);
      }
    else
      for (size_t i = 0; i < numberodd; i++)
      {
         infile>>x;
         even.push_back(x);
      }
    infile>>numbercorridors;

    for (size_t i = 0; i < numbercorridors; i++)
    {
      int x,y,z;
      infile>>x;
      infile>>y;
      infile>>z;
      roomvector[x][y] = z;
      roomvector[y][x] = z;

    }
    infile>>numofammoroom;

    for (size_t i = 0; i < numofammoroom; i++) {
      int x,z;
      infile>>x;
      infile>>z;
      roomvector[x][x] = z;

    }



    infile.close();
  }

  else cout << "Unable to open file";




  //get(roomvector,roomnumber);
  //cout<<isinpath(roomvector[1],2,8)<<endl;
//   cout<<roomvector[7].front()<<endl;
//   cout<<roomvector[7].back()<<endl;
// cout<<roomvector[7].back()<<endl;
// cout<<roomvector[7].size()<<endl;

//       cout<<"ammo = "<< ammo << endl;
//       cout<<"roomnumber = "<< roomnumber << endl;
//       cout<<"bunny = "<< bunny << endl;
//       cout<<"key = "<< key << endl;
//       cout<<"scientist = "<< scientist << endl;
//       cout<<"numberodd = "<< numberodd << endl;
//       cout << "oddroom(s) = ";
//       for (size_t i = 0; i < numberodd; i++) {
//         cout<<odd[i]<<" ";
//       }
//       cout<< endl;
//       cout<<"numbereven = "<< numbereven << endl;
//       cout << "evenroom(s) = ";
//       for (size_t i = 0; i < numbereven; i++) {
//         cout<<even[i]<<" ";
//       }
// cout<<endl;
// for (size_t i = 0; i <= roomnumber; i++) {
//   for (size_t j = 0; j <= roomnumber; j++) {
//     cout<<roomvector[i][j]<<"  ";
//   }
//   cout<<endl;
// }
// cout<<iseven(2)<<endl;
// cout<<isodd(2)<<endl;
// cout<<iseven(7)<<endl;
// cout<<isodd(7)<<endl;





     room start;
     start.cost = 0;
     start.level = 1;
     start.path.push_back(0);
     room keyroom =  getpath(roomvector,roomnumber,1,key,start);
     keyroom.path.push_back(key);
     room scientistroom = getpath(roomvector,roomnumber,key,scientist,keyroom);
     scientistroom.path.push_back(scientist);
     room bunnyroom = getpath(roomvector,roomnumber,scientist,bunny,scientistroom);
     bunnyroom.path.push_back(bunny);


     // cout<<"ammo "<<ammo<<endl;
      // cout<<endl;
      // cout<<ammo- keyroom.cost<<endl;
      // cout<<keyroom.level<<endl;
      // for (size_t i = 1; i < keyroom.path.size(); i++) {
      //   cout<<keyroom.path[i]<<" -> ";
      // }
      // cout<<endl;
      //
      // cout<<endl;
      // cout<<ammo - scientistroom.cost<<endl;
      // cout<<scientistroom.level<<endl;
      // for (size_t i = 1; i < scientistroom.path.size(); i++) {
      //   cout<<scientistroom.path[i]<<" -> ";
      // }
      // cout<<endl;
      //
      //
      // cout<<endl;
      // cout<<ammo - bunnyroom.cost<<endl;
      // cout<<bunnyroom.level<<endl;
      // for (size_t i = 1; i < bunnyroom.path.size(); i++) {
      //   cout<<bunnyroom.path[i]<<" -> ";
      // }
      // cout<<endl;

ammo -= bunnyroom.cost;

      ofstream outfile;
      outfile.open ("the3.out");
      if(outfile.is_open())
      {
        outfile << ammo;
        outfile << "\n";
        outfile << bunnyroom.level;
        outfile << "\n";
        for (size_t i = 1; i < bunnyroom.path.size(); i++)
        {
          outfile<<bunnyroom.path[i];
          if(i+1 <bunnyroom.path.size())
            outfile<<" ";
        }
      }


  return 0;
}
