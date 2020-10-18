#include "WarHead.h"


WarHead::WarHead()
{
	position.x = 0;
	position.y = 0;
	speed.x = 1;
	speed.y = 1;
}

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

void WarHead::moveWarhead()
{
	position.x += speed.x;
	position.y += speed.y;
}
