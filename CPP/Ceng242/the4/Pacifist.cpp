#include "Pacifist.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Pacifist::Pacifist(uint id, int x, int y):Player(id,x,y)
{
	setHP(100);
}

std::vector<Move> Pacifist::getPriorityList() const
{
	std::vector<Move> ret;
	ret.push_back(UP);
	ret.push_back(LEFT);
	ret.push_back(DOWN);
	ret.push_back(RIGHT);

	return ret;
}




Armor Pacifist::getArmor() const
{
	return METAL;
}
Weapon Pacifist::getWeapon() const
{
	return NOWEAPON;
}
const std::string Pacifist::getFullName() const
{
		return "Pacifist" + this->getBoardID();
}
