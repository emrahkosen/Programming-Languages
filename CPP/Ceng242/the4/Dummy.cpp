#include "Dummy.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Dummy::Dummy(uint id, int x, int y):Player(id,x,y)
{
	setHP(1000);
}

std::vector<Move> Dummy::getPriorityList() const
{
	std::vector<Move> ret;
	ret.push_back(NOOP); /*NOoP nedemek yok mu demek dan bi move ye*/

	return ret;
}




Armor Dummy::getArmor() const
{
	return NOARMOR;
}
Weapon Dummy::getWeapon() const
{
	return NOWEAPON;
}
const std::string Dummy::getFullName() const
{
	return "Dummy" + this->getBoardID();
}
