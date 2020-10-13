#include "WarHead.h"

void WarHead::setWarhead(int t_warhead)
{
	switch (t_warhead)
	{
	case 1:
		damage = 20;
		break;
	case 2:
		damage = 50;
		break;
	case 3:
		damage = 100;
		break;
	default:
		std::cout << "Warhead code broke.";
		break;
	}
}

void WarHead::setPosition(Coordinates t_coord)
{
	position = t_coord;
}

Coordinates WarHead::getPosition()
{
	return position;
}
