#include "Player.h"
#include <iostream>
#include <string>
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Player::Player(uint id, int x, int y):id(id),coordinate(x,y)//Coordinate( x, y))
 {
  /* coordinate.x = x;
   coordinate.y = y; */
 }

 Player::~Player()
 {

 }

 uint Player::getID() const
 {
   return id;
 }


 const Coordinate& Player::getCoord() const
 {
   return coordinate;
 }

 int Player::getHP() const
 {
   return HP;
 }



 void Player::setHP(int hp){HP = hp;}




 std::string Player::getBoardID() const
{
  std::string ret;
   if(id < 10)
     ret = "0" +  std::to_string(id);
   else
    ret =  std::to_string(id);
  return ret;
 }


 bool Player::isDead() const
 {
   if(HP <= 0)
    return true;
  return false;
 }

void Player::executeMove(Move move)
{

  //
  // std::string playername;
  // if(getWeapon() == PISTOL)
  //   playername = "Berserk";
  // else if(getWeapon() == SHOVEL)
  //     playername = "Tracer";
  // else if(getWeapon() == SEMIAUTO)
  //       playername = "Ambusher";
  // else
  // {
  //   if(getArmor() == METAL)
  //     playername = "Pacifist";
  //   else
  //       playername = "Dummy";
  // }
  //





  if(move == Move::UP)
  {
    coordinate.y = coordinate.y - 1;

    std::cout<< getFullName()  <<"("<<HP<<") moved UP.\n";
  }

  else if(move == Move::DOWN)
  {
    coordinate.y = coordinate.y + 1;
    std::cout<< getFullName()  <<"("<<HP<<") moved DOWN.\n";
  }

  else if(move == Move::LEFT)
  {
    coordinate.x = coordinate.x - 1;
    std::cout<< getFullName()  <<"("<<HP<<") moved LEFT.\n";
  }
  else if(move == Move::RIGHT)
  {
    coordinate.x = coordinate.x + 1;
    std::cout<< getFullName()  <<"("<< HP <<") moved RIGHT.\n";
  }
}

bool Player::attackTo(Player *player)
{
  // std::string playername;
  // if(getWeapon() == PISTOL)
  //   playername = "Berserk";
  // else if(getWeapon() == SHOVEL)
  //     playername = "Tracer";
  // else if(getWeapon() == SEMIAUTO)
  //       playername = "Ambusher";
  // else
  // {
  //   if(getArmor() == METAL)
  //     playername = "Pacifist";
  //   else
  //       playername = "Dummy";
  // }
  //
  // std::string playername2;
  // if(player->getWeapon() == PISTOL)
  //   playername2 = "Berserk";
  // else if(player->getWeapon() == SHOVEL)
  //     playername2 = "Tracer";
  // else if(player->getWeapon() == SEMIAUTO)
  //       playername2 = "Ambusher";
  // else
  // {
  //   if(player->getArmor() == METAL)
  //     playername2 = "Pacifist";
  //   else
  //       playername2 = "Dummy";
  // }
  if(this == player)
    return false;
  int oldhp = player->getHP();
  int lhsDamage = Entity::damageForWeapon( getWeapon() );
  int rhsAmor = Entity::damageReductionForArmor(player->getArmor());
  int newhp;
  if((lhsDamage - rhsAmor) > 0)
    player->setHP(oldhp - (lhsDamage - rhsAmor));

  std::cout<<   this->getFullName() <<"("<< getHP() <<") ATTACKED ";
  std::cout<< player->getFullName() <<"("<<oldhp<<")"<<"! (-"<< ( lhsDamage - rhsAmor) <<")\n";


  if(player->isDead())
    return true;
  return false;
}
