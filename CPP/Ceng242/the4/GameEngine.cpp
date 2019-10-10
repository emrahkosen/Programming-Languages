#include "GameEngine.h"
#include <iostream>
#include <list>
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/


GameEngine::GameEngine(uint boardSize, std::vector<Player *> *players):board(boardSize,players)
{
  currentRound = 1;

}
GameEngine::~GameEngine()
{
}

const Board& GameEngine::getBoard() const
{
    return board;
}
Player* GameEngine::operator[](uint id) const
{
  std::vector<Player *> &refBoard = board.returnPlayers();

  for(auto it:refBoard)
  {
    if(it->getID() == id)
      return it;
  }

  return nullptr;

}


bool GameEngine::isFinished() const
{
	std::vector<Player *> &refBoard = board.returnPlayers();
	int size = 0;
	for(auto it:refBoard)
		size++;


  if(size == 0)
    return true;
  if(size == 1 && board.isCoordHill( board.returnPlayers()[0]->getCoord() ) )
  {
    return true;
  }
  return false;

}






void GameEngine::takeTurn()
{
  std::cout<< "-- START ROUND " <<currentRound<< " --\n";

  board.updateStorm(currentRound);

  std::vector<Player *> &refBoard = board.returnPlayers();

currounddam = Entity::stormDamageForRound(currentRound);
  if(refBoard.size())
  {
  	int i = 0;
  	while(i < refBoard.size())
  	{
  	  int id = refBoard[i]->getID();
  	  takeTurnForPlayer(refBoard[i]->getID());
  	  if(id == refBoard[i]->getID())
  	  	i++;
  	}
  }




/*  for(auto it:refBoard)
  {
 //   if(it->getID() > 0)

      takeTurnForPlayer(it->getID());
  }
*/
  std::cout<<"-- END ROUND "<<currentRound<< " --\n";

  currentRound = currentRound + 1;
}






Move GameEngine::takeTurnForPlayer(uint playerID)
{
  std::vector<Player *> &refBoard = board.returnPlayers();
  int i = 0;
  for(auto it:refBoard)
  {

    if(it->getID() == playerID)
    {
      std::vector<Move> priorities = it->getPriorityList();
      std::vector<Coordinate> visiblecoordinate =  board.visibleCoordsFromCoord(it->getCoord());

     // std::cout<<it->getFullName()<<"-------------***************---------------1\n";

      if( board.isStormInCoord(it->getCoord()) )
      {
        std::cout<< it->getFullName() <<  "("<< it->getHP() <<") is STORMED! (-" <<currounddam<< ")\n";
        it->setHP(it->getHP() - currounddam);
      }
      if(it->isDead())
      {
        std::cout<< it->getFullName()<< "("<< it->getHP() <<") DIED.\n";

        /*remove player*/
        delete it;
        it == nullptr;
        refBoard.erase(refBoard.begin() +i);


        return NOOP;
      }



      for(auto prior:priorities)
      {
      //	std::cout<<it->getFullName()<<"-------------***************---------------2\n";
        if(prior == NOOP)
          return NOOP;



        else if (prior == ATTACK)
        {
 // std::cout<<it->getFullName()<<"-------------***************---------------atack\n";

          /*buraya attack edebilecegi en uygun oyuncuya atak edecegiz varsa tabi visibilityCoords icinde ise*/
          Player *lowestPlayer = nullptr;
          int j = 0 , k = 0;
          for(auto lp:refBoard)
          {

            for(auto cor:visiblecoordinate)
            {
              // if( lp != it  && cor == lp->getCoord() && (lowestPlayer == nullptr || lowestPlayer->getID() >  lp->getID() ) )
              //   {
              //     lowestPlayer = lp;
              //     k = j;
              //   }
              if(lp != it  && cor == lp->getCoord()&&  lowestPlayer == nullptr  )
              {
                  lowestPlayer = lp;
                  k = j;
              }
              if(lp != it  && cor == lp->getCoord()&&  lowestPlayer->getID() >  lp->getID()  )
              {
                lowestPlayer = lp;
                k = j;
              }
            }
            j++;
          }

          if(lowestPlayer)
          {
            bool isPlayerDead = it->attackTo(lowestPlayer);
            if(isPlayerDead)
            {
              std::cout<< lowestPlayer->getFullName()<< "("<< lowestPlayer->getHP() <<") DIED.\n";

            /*remove player*/
              delete lowestPlayer;
              lowestPlayer == nullptr;
              refBoard.erase(refBoard.begin() + k);
            }
            return ATTACK;
          }

        }
        else
        {
          Coordinate next = board.calculateCoordWithMove(prior,it->getCoord());
  //  std::cout<<it->getFullName()<<"-------------*******"<<next.x<<"   "<<next.y<<"********---------------10\n";

          if(next != it->getCoord())
          {
  //std::cout<<it->getFullName()<<"    hp::"<<it->getHP()<<"-------------*******"<<next.x<<"   "<<next.y<<"********---------------11\n";

            int h = board.getSize()/2;
            int displayertohill = (h-it->getCoord().x)*(h-it->getCoord().x) + (h-it->getCoord().y)*(h-it->getCoord().y);
            int disnexttohill = (h-next.x)*(h-next.x) + (h-next.y)*(h-next.y);
            if(displayertohill > disnexttohill)
            {
              it->executeMove(prior);
              return prior;
            }
          //  std::cout<<it->getFullName()<<"-------------***************---------------11\n";
          }
         // std::cout<<it->getFullName()<<"-------------***************---------------22\n";
        }
       // std::cout<<it->getFullName()<<"-------------***************---------------33\n";
      }
      break;
    }
    i++;
  }
  return NOOP;
}





Player * GameEngine::getWinnerPlayer() const
{

  if(board.returnPlayers().size() == 0 || isFinished() == false)
    {
    	return nullptr;
    }
  else
  {
  //	std::cout<<"-------------***************---------------11000000000000\n";
    return board.returnPlayers()[0];
  }
}






































/**/
