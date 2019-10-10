#include "Board.h"
#include <iostream>
#include <string>
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/


Board::Board(uint boardSize, std::vector<Player *> *players):boardSize(boardSize),players(players)
{
}
Board::~Board()
{
  // if(players != nullptr)
  // {
  //    for(auto pl :*players)
  //        delete pl;
  //    players->clear();
  // }
       // delete players;}
}
uint Board::getSize() const
{
  return boardSize;
}
bool Board::isCoordInBoard(const Coordinate& coord) const
{
  if(coord.x < 0 || coord.y < 0 || coord.x >= boardSize  || coord.y >= boardSize )
    return false;
  return true;
}





bool Board::isStormInCoord(const Coordinate &coord) const
{
  if(isCoordInBoard(coord))
  {
    if(coord.x >= curstorm && coord.y >= curstorm &&  coord.x < boardSize-curstorm && coord.y < boardSize - curstorm  )
      return false;
    return true;
  }

  // if(coord.x < 0 || coord.y < 0 || coord.x > boardSize - curstorm || coord.y > boardSize - curstorm)
  // {
  //   return false;
  // }
  //
  // else if(coord.x < curstorm || coord.y < curstorm || coord.x >= boardSize - curstorm|| coord.y >= boardSize -curstorm)
  // {
  //    return true;
  // }

  return false;
}





bool Board::isCoordHill(const Coordinate& coord) const
{
  int hill = boardSize/2;
  if(coord.x == hill && coord.y == hill)
    return true;
  return false;
}




Player* Board::operator[](const Coordinate& coord) const
{
  //for( vector< Player * >::iterator it = players->begin(); it != players->end(); it++)
  for(auto it: *players)
  {
    if(it->getCoord() == coord)
      return it;
  }

  return nullptr;
}
Coordinate Board::calculateCoordWithMove(Move move, const Coordinate &coord) const
{
  Coordinate ret = Coordinate(coord.x,coord.y);

  if(move == 1)
    {
      if(coord.y != 0)
        ret.y = ret.y -1;

    }
    else if(move == 2)
      {
        if(coord.y != boardSize-1)
          ret.y = ret.y + 1;
      }
      else if(move == 3)
        {
          if(coord.x != 0)
            ret.x = ret.x - 1;
        }
        else if(move == 4)
          {
            if(coord.x != boardSize-1)
              ret.x = ret.x + 1;
          }
        else
            ;
      for(auto it: *players)
        {
          if(it->getCoord() == ret)
          return coord;
        }
      return ret;
}



std::vector<Coordinate> Board::visibleCoordsFromCoord(const Coordinate &coord) const
{
  std::vector<Coordinate> ret;

  if(coord.x < 0 || coord.y < 0 || coord.x >= boardSize || coord.y >= boardSize)
    ;

   else
   {
     Coordinate cor1 = Coordinate(coord.x-1,coord.y);
     Coordinate cor2 = Coordinate(coord.x+1,coord.y);
     Coordinate cor3 = Coordinate(coord.x,coord.y-1);
     Coordinate cor4 = Coordinate(coord.x,coord.y+1);

     if(isCoordInBoard(cor1))
        ret.push_back(cor1);
     if(isCoordInBoard(cor2))
        ret.push_back(cor2);
     if(isCoordInBoard(cor3))
        ret.push_back(cor3);
     if(isCoordInBoard(cor4))
        ret.push_back(cor4);
   }
   return ret;
}


void Board::updateStorm(uint currentRound)
{
  if( currentRound> 5 && (currentRound-1)% 5 == 0)
    {
      if(curstorm < boardSize/2)
      {
        curstorm++;
      }
    }
}


std::vector<Player *> & Board::returnPlayers() const
{
  return *this->players;
}

std::vector<Player *> & Board::returnPlayers()
{
  return *this->players;
}




















































/**/
