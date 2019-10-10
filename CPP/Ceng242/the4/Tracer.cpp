#include "Tracer.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Tracer::Tracer(uint id, int x, int y):Player(id,x,y)
{
	setHP(100);
}

std::vector<Move> Tracer::getPriorityList() const
{
	std::vector<Move> ret;
	ret.push_back(UP);
	ret.push_back(LEFT);
	ret.push_back(DOWN);
	ret.push_back(RIGHT);
	ret.push_back(ATTACK);

	return ret;
}




Armor Tracer::getArmor() const
{
	return BRICK;
}
Weapon Tracer::getWeapon() const
{
	return SHOVEL;
}
const std::string Tracer::getFullName() const
{
		return "Tracer" + this->getBoardID();
}
