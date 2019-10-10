#include "Ambusher.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Ambusher::Ambusher(uint id, int x, int y):Player(id,x,y)
{
	setHP(100);
}

std::vector<Move> Ambusher::getPriorityList() const
{
	std::vector<Move> ret;
	ret.push_back(ATTACK);

	return ret;
}




Armor Ambusher::getArmor() const
{
	return NOARMOR;
}
Weapon Ambusher::getWeapon() const
{
	return SEMIAUTO;
}
const std::string Ambusher::getFullName() const
{
		return "Ambusher" + this->getBoardID();
}
