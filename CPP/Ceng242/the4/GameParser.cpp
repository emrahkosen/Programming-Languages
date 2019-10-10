#include "GameParser.h"
#include <iostream>
#include <fstream>
#include <sstream>
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/


//static
std::pair<int, std::vector<Player *> *> GameParser::parseFileWithName(const std::string& filename)
{
  int bsize;
  int pcount = -1,ii = 0;
  std::vector<Player *> *pls;

  std::pair<int, std::vector<Player *> *> ret;
  ret.second = new std::vector<Player *>();
  pls = ret.second;


  std::ifstream file;//file(filename.c_str());
  file.open(filename.c_str());
  if(file.fail())
    ;
  else
  {
    std::string line;

    while(ii != pcount && std::getline(file,line) )
        {


          if(line[0] == 'B')
          {
            std::string bs(line,12);
            ret.first = stoi(bs);
          }

          else if(line[0] == 'P')/*bu ne ise yarıyor??*/
          {
            std::string pc(line,14);
          //  std::cout<<pc<<"***************************\n";
            pcount = stoi(pc);
          }

          else
          {
            std::string id,playername,x,y;
            Player *player;
            int i = 0;
            while(line[i] != ':')
              id += line[i++];
            (++i)++;

            while(line[i] != ':')
                playername += line[i++];
            (++i)++;

            while(line[i] != ':')
                x += line[i++];

            (++i)++;
            y = line.substr(i);

            uint intid = stoi(id);
            int intx = stoi(x);
            int inty = stoi(y);


            if(playername == "Berserk")
            {
              player = new Berserk(intid,intx,inty);
            }
            if(playername == "Tracer")
            {
              player = new Tracer(intid,intx,inty);
            }
            if(playername == "Ambusher")
            {
              player = new Ambusher(intid,intx,inty);
            }
            if(playername == "Pacifist")
            {
              player = new Pacifist(intid,intx,inty);
            }
            if(playername == "Dummy")
            {
              player = new Dummy(intid,intx,inty);
            }
            else
              ;
            pls->push_back(player);
            ++ii;
          }
        }
  file.close();

  }

  return ret;

}





























/**/
