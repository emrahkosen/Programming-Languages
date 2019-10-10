#include "Berserk.h"
#include <iostream>
/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/


Berserk::Berserk(uint id, int x, int y):Player(id,x,y)
{
	setHP(100);
}

std::vector<Move> Berserk::getPriorityList() const
{
	std::vector<Move> ret;
	ret.push_back(ATTACK);
	ret.push_back(UP);
	ret.push_back(LEFT);
	ret.push_back(DOWN);
	ret.push_back(RIGHT);

	return ret;
}




Armor Berserk::getArmor() const
{
	return WOODEN;
}
Weapon Berserk::getWeapon() const
{
	return PISTOL;
}


const std::string Berserk::getFullName() const
{
	return "Berserk" + this->getBoardID();
}
